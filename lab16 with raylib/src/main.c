#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include "windows_functions.h"
#include "tinyfiledialogs.h"

#define RAYGUI_IMPLEMENTATION
//#define RAYGUI_PANEL_BORDER_WIDTH 2
#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 32
#define RAYGUI_MESSAGEBOX_BUTTON_HEIGHT 36
#include "raygui.h"

#define RAYLIB_NUKLEAR_IMPLEMENTATION
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
//#define RAYLIB_NUKLEAR_DEFAULT_ARC_SEGMENTS 1
#pragma warning(disable: 4116)
#include "raylib-nuklear.h"

Vector2 scaleDPI = { 1.0f, 1.0f };
#define M 10
#define N 15
//#define WIDTH (int)(50 * scaleDPI.x)
//#define HEIGHT (int)(50 * scaleDPI.y)
//#define VOFFSET (int)(52 * scaleDPI.y)

//#define FWIDTH (float)WIDTH
//#define FHEIGHT (float)HEIGHT

#define PUREBLUE (Color) { 0, 0, 255, 255 }
#define BLACKGRAY (Color) {30, 30, 30, 255}
#define VSGREEN (Color) {78, 201, 176, 255}
#define WATERBLUE CLITERAL(Color){200, 240, 255, 255}

int HEIGHT = 50;
int WIDTH = 50;
int VOFFSET = 52;
float FWIDTH;
float FHEIGHT;

// Коды ячеек:
// 0 - свободна
// 1 - 
// 2 - препятствие
// 3 - золото
int map[M][N] = {
	{0, 0, 0, 0, 0,   0, 0, 0, 0, 0,   0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,   0, 0, 0, 0, 3,   0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,   0, 0, 0, 0, 3,   0, 0, 0, 0, 0},
	{0, 0, 0, 3, 3,   3, 3, 0, 0, 0,   3, 3, 0, 0, 0},
	{0, 0, 0, 0, 0,   0, 3, 0, 0, 0,   3, 3, 0, 0, 0},

	{0, 0, 0, 0, 0,   0, 3, 3, 3, 0,   0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,   0, 0, 0, 3, 0,   2, 0, 0, 2, 0},
	{0, 0, 0, 0, 0,   0, 0, 2, 0, 0,   2, 0, 0, 2, 0},
	{0, 0, 0, 0, 0,   0, 2, 2, 2, 2,   2, 2, 2, 2, 0},
	{0, 0, 0, 0, 0,   0, 0, 0, 0, 0,   0, 0, 0, 0, 0}
};

int player_x = 1;
int player_y = 1;

typedef enum obj_enum { empty = 0, wall = 2, gold = 3 } obj_enum;
// TODO: do something with "empty" object
#define INVENTORY_SIZE 4
int inventory[INVENTORY_SIZE] = { 0, 0, 15, 0 };
obj_enum selected_element = gold;

typedef enum { left, right, up, down } enum_ways;
void movePlayer(enum_ways move) {
	switch (move) {
	case left:
		if (player_x > 0) {
			if (map[player_y][player_x - 1] != wall) {
				player_x -= 1;
			}
		}
		else {
			if (map[player_y][N - 1] != wall) {
				player_x = N - 1;
			}
		}
		break;
	case right:
		if (player_x < N - 1) {
			if (map[player_y][player_x + 1] != wall) {
				player_x += 1;
			}
		}
		else {
			if (map[player_y][0] != wall) {
				player_x = 0;
			}
		}
		break;
	case up:
		if (player_y > 0) {
			if (map[player_y - 1][player_x] != wall) {
				player_y -= 1;
			}
		}
		else {
			if (map[M - 1][player_x] != wall) {
				player_y = M - 1;
			}
		}
		break;
	case down:
		if (player_y < M - 1) {
			if (map[player_y + 1][player_x] != wall) {
				player_y += 1;
			}
		}
		else {
			if (map[0][player_x] != wall) {
				player_y = 0;
			}
		}
		break;
	}
	if (map[player_y][player_x] == gold) {
		map[player_y][player_x] = empty;
		inventory[gold]++;
	}
}

void putElement(enum_ways way, obj_enum element) {
	if (element != empty && inventory[element] == 0) return;

	switch (way) {
	case left:
		if ((player_x > 0) and map[player_y][player_x - 1] == 0) {
			map[player_y][player_x - 1] = element;
			inventory[element]--;
		}
		break;
	case right:
		if ((player_x < N - 1) and map[player_y][player_x + 1] == 0) {
			map[player_y][player_x + 1] = element;
			inventory[element]--;
		}
		break;
	case up:
		if ((player_y > 0) and map[player_y - 1][player_x] == 0) {
			map[player_y - 1][player_x] = element;
			inventory[element]--;
		}
		break;
	case down:
		if ((player_y < M - 1) and map[player_y + 1][player_x] == 0) {
			map[player_y + 1][player_x] = element;
			inventory[element]--;
		}
		break;
	}
}

void deathbeam(enum_ways way) {
	for (int i = player_x + 1; i < N; i++) {
		if (map[player_y][i] != empty) inventory[map[player_y][i]] += 1;
		map[player_y][i] = 0;
	}
}

void stomp(int r) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if ((player_y - r <= i) && (i <= player_y + r) && (player_x - r <= j) && (j <= player_x + r) && map[i][j] == wall) {
				inventory[wall] += 1;
				map[i][j] = empty;
			}
		}
	}
}

void midasHand(int m, int n) {
	if (map[m][n] == wall) {
		map[m][n] = gold;
		if (m > 0) midasHand(m - 1, n);
		if (n > 0) midasHand(m, n - 1);
		if (m < M - 1) midasHand(m + 1, n);
		if (n < N - 1) midasHand(m, n + 1);
	}
}

void doMidashand() {
	if ((player_y < M - 1) and map[player_y + 1][player_x] == wall) midasHand(player_y + 1, player_x);
	if ((player_x < N - 1) and map[player_y][player_x + 1] == wall) midasHand(player_y, player_x + 1);
	if ((player_y > 0) and map[player_y - 1][player_x] == wall) midasHand(player_y - 1, player_x);
	if ((player_x > 0) and map[player_y][player_x - 1] == wall) midasHand(player_y, player_x - 1);
}

bool netToggle = false;
void drawNet() {
	for (int i = 0; i <= N * WIDTH; i += WIDTH) {
		DrawLine(i, 0, i, M * HEIGHT, BLACK);
	}

	for (int i = 0; i <= M * HEIGHT; i += HEIGHT) {
		DrawLine(0, i, N * WIDTH, i, BLACK);
	}
}

void drawMap() {
	// Коды ячеек:
	// 0 - свободна
	// 1 - 
	// 2 - препятствие
	// 3 - золото
	Color colors[4] = { LIGHTGRAY, PUREBLUE, BLACK, YELLOW };

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			int x1 = j * WIDTH;
			int y1 = i * HEIGHT;
			DrawRectangle(x1, y1, WIDTH, HEIGHT, colors[map[i][j]]);
		}
	}
}

void drawPlayer() {
	int x1 = player_x * WIDTH;
	int y1 = player_y * HEIGHT;;
	DrawRectangle(x1, y1, WIDTH, HEIGHT, PUREBLUE);
}

void drawBottomBar(Font font, float fontSize) {
	DrawRectangle(0, HEIGHT * M, WIDTH * N, VOFFSET, BLACKGRAY);

	static char gold_string[50];
	static char wall_string[50];

	static char help_string[] = "wasd - move player   G - change item   F5 - save\narrows - place item   M - Midas hand   F9 - load";

	sprintf(gold_string, " gold = %d", inventory[gold]);
	sprintf(wall_string, " wall = %d", inventory[wall]);

	if (selected_element == gold) gold_string[0] = '>';
	else if (selected_element == wall) wall_string[0] = '>';

	Vector2 goldpos = { FWIDTH / 4, FHEIGHT * M };
	Vector2 wallpos = { FWIDTH / 4, FHEIGHT * M + fontSize };
	Vector2 helppos = { FWIDTH * N - MeasureTextEx(font, help_string, fontSize, 0).x - 20 * scaleDPI.x, FHEIGHT * M};

	DrawTextEx(font, gold_string, goldpos, fontSize, 0, VSGREEN);
	DrawTextEx(font, wall_string, wallpos, fontSize, 0, VSGREEN);
	DrawTextEx(font, help_string, helppos, fontSize, 0, VSGREEN);
}

void save() {
	FILE* fout = fopen("savefile.txt", "w");
	if (fout == NULL) {
		printf("save error");
		return;
	}

	fprintf(fout, "%d %d\n", M, N);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			fprintf(fout, "%d ", map[i][j]);
		}
		fprintf(fout, "\n");
	}

	for (int i = 0; i < INVENTORY_SIZE; i++) {
		fprintf(fout, "%d ", inventory[i]);
	}
	fprintf(fout, "\n");

	fprintf(fout, "%d %d %d\n", player_x, player_y, selected_element);

	fclose(fout);
}

typedef enum { OK = 0, saveError, loadError1, loadError2 } ErrorCodes;
ErrorCodes errorCode = OK;
void load() {
	FILE* fin = fopen("savefile.txt", "r");
	if (fin == NULL) {
		printf("1) load error\n");
		/*MessageBoxA(
			GetActiveWindow(),
			"Файл не найден\nПопробуйте сначала сохранить игру",
			"Ошибка загрузки",
			MB_ICONERROR
		);*/

		tinyfd_messageBox(
			u8"Ошибка сохранения",
			u8"Невозможно создать файл\nПроверьте целостность сохранения",
			u8"ok",
			"error", 1);
		//errorCode = loadError1;
		return;
	}
	int m, n;
	fscanf_s(fin, "%d%d", &m, &n);
	if (m != M || n != N) {
		printf("2) load error\n");
		/*MessageBoxW(
			NULL,
			L"Неправильный размер карты!\nПроверьте целостность сохранения",
			L"Ошибка загрузки",
			MB_ICONERROR
		);*/
		errorCode = loadError2;
		return;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			fscanf_s(fin, "%d", &map[i][j]);
		}
	}

	for (int i = 0; i < INVENTORY_SIZE; i++) {
		fscanf_s(fin, "%d", &inventory[i]);
	}

	fscanf_s(fin, "%d%d%d", &player_x, &player_y, &selected_element);

	fclose(fin);
}

bool editMap = 0;
void handleKeys() {

	/*if (IsKeyPressedRepeat(KEY_W)) movePlayer(up);
	if (IsKeyPressedRepeat(KEY_S)) movePlayer(down);
	if (IsKeyPressedRepeat(KEY_D)) movePlayer(right);
	if (IsKeyPressedRepeat(KEY_A)) movePlayer(left);*/

	int key;
	while (key = GetKeyPressed()) {
		if (not editMap) {
			switch (key)
			{
			case KEY_W:
				movePlayer(up);
				break;
			case KEY_S:
				movePlayer(down);
				break;
			case KEY_D:
				movePlayer(right);
				break;
			case KEY_A:
				movePlayer(left);
				break;
			case KEY_ONE:
				stomp(1);
				break;
			case KEY_TWO:
				stomp(2);
				break;
			case KEY_Z:
				deathbeam(right);
				break;
			case KEY_M:
				doMidashand();
				break;
			case KEY_LEFT:
				putElement(left, selected_element);
				break;
			case KEY_RIGHT:
				putElement(right, selected_element);
				break;
			case KEY_UP:
				putElement(up, selected_element);
				break;
			case KEY_DOWN:
				putElement(down, selected_element);
				break;
			}
		}
		
		switch (key)
		{
		case KEY_F5:
			save();
			break;
		case KEY_F9:
			load();
			break;
		case KEY_SPACE:
			netToggle = !netToggle;
			break;
		case KEY_ENTER:
			editMap = !editMap;
			break;
		case KEY_G:
			if (selected_element == gold) selected_element = wall;
			else selected_element = gold;
			break;
		}
	}
}

void drawRayguiErrorBoxes() {
	const Rectangle errorBoxRect = { N * FWIDTH / 2 - 200, M * FHEIGHT / 2 - 75, 400, 150 };
	int btn = -1;

	switch (errorCode)
	{
	case OK:
		break;
	case saveError:
		btn = GuiMessageBox(errorBoxRect,
			u8"Ошибка сохранения",
			u8"Невозможно создать файл",
			u8"Ок;Выйти");
		break;
	case loadError1:
		btn = GuiMessageBox(errorBoxRect,
			u8"Ошибка загрузки",
			u8"Файл не найден\nПопробуйте сначала сохранить игру",
			u8"Игнорировать;Выйти из игры");
		break;
	case loadError2:
		btn = GuiMessageBox(errorBoxRect,
			u8"Ошибка загрузки",
			u8"Неправильный размер карты!\nПроверьте целостность сохранения",
			u8"Игнорировать;Выйти из игры");
		break;
	}

	switch (btn)
	{
	case 0:
		errorCode = OK;
		break;
	case 1:
		errorCode = OK;
		break;
	case 2:
		exit(0);
		break;
	}
}

int nk_error_box(struct nk_context* ctx, const char* title, const char* error, const char* description)
{
	int result = -1;
	if (nk_begin(ctx, title,
		nk_rect(N * FWIDTH / 2 - 200, M * FHEIGHT / 2 - 72, 400, 144),
		NK_WINDOW_TITLE | NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))
	{
		nk_layout_row_dynamic(ctx, 24, 1);
		nk_label(ctx, error, NK_TEXT_CENTERED);
		nk_layout_row_dynamic(ctx, 24, 1);
		nk_label(ctx, description, NK_TEXT_CENTERED);
		nk_layout_row_dynamic(ctx, 36, 2);
		if (nk_button_label(ctx, u8"Игнорировать")) {
			result = 1;
		}
		if (nk_button_label(ctx, u8"Выйти из игры")) {
			result = 2;
		}
	}
	else {
		result = 0;
	}
	return result;
}

void callNKErrorBoxes(struct nk_context* ctx) {
	int btn = -1;

	switch (errorCode)
	{
	case OK:
		break;
	case saveError:
		btn = nk_error_box(ctx,
			u8"Ошибка сохранения",
			u8"Невозможно создать файл",
			u8"Проверьте целостность сохранения");
		break;
	case loadError1:
		btn = nk_error_box(ctx,
			u8"Ошибка загрузки",
			u8"Файл не найден",
			u8"Попробуйте сначала сохранить игру");
		break;
	case loadError2:
		btn = nk_error_box(ctx,
			u8"Ошибка загрузки",
			u8"Неправильный размер карты",
			u8"Проверьте целостность сохранения");
		break;
	}

	switch (btn)
	{
	case 0:
		errorCode = OK;
		break;
	case 1:
		errorCode = OK;
		break;
	case 2:
		exit(0);
		break;
	}
}

#define CPSIZE 213
int main()
{
	//SetConfigFlags(FLAG_WINDOW_HIGHDPI);
	
	InitWindow(N * WIDTH, M * HEIGHT + VOFFSET, "lab16 with raylib");

	int monitor = GetCurrentMonitor();
	int monitorCenterX = GetMonitorWidth(monitor) / 2;
	int monitorCenterY = GetMonitorHeight(monitor) / 2;

	scaleDPI = GetWindowScaleDPI();
	WIDTH = (int)(WIDTH * scaleDPI.x);
	HEIGHT = (int)(HEIGHT * scaleDPI.y);
	VOFFSET = (int)(VOFFSET * scaleDPI.y);
	FWIDTH = (float)WIDTH;
	FHEIGHT = (float)HEIGHT;

	int screenWidth = N * WIDTH;
	int screenHeight = M * HEIGHT + VOFFSET;
	float screenWidthF = (float)screenWidth;
	float screenHeightF = (float)screenHeight;
	Vector2 resolution = { screenWidthF, screenHeightF };

	SetWindowSize(screenWidth, screenHeight);
	SetWindowPosition(monitorCenterX - screenWidth/2, monitorCenterY - screenHeight/2);

	SetTargetFPS(60);

	SearchAndSetResourceDir("resources");

	int codepoints[CPSIZE] = { 0 };
	for (int i = 0; i < 127 - 32; i++) codepoints[i] = 32 + i;   // Basic ASCII characters
	for (int i = 0; i < 118; i++) codepoints[95 + i] = 1024 + i;   // Cyrillic characters

	//Font InconsolataRegular = LoadFontEx("Inconsolata-Regular.ttf", 24, NULL, 0);
	//Font InconsolataSemiBold = LoadFontEx("Inconsolata-SemiBold.ttf", 48, codepoints, 512);
	Font InconsolataBold = LoadFontEx("Inconsolata-LGC-Bold.ttf", 36, codepoints, CPSIZE);
	SetTextureFilter(InconsolataBold.texture, TEXTURE_FILTER_BILINEAR);
	//Font Consolas = LoadFontEx("consola.ttf", 24, codepoints, CPSIZE);
	//SetTextureFilter(Consolas.texture, TEXTURE_FILTER_BILINEAR);
	//Font Arial = LoadFontEx("arial.ttf", 36, codepoints, CPSIZE);
	//SetTextureFilter(Arial.texture, TEXTURE_FILTER_BILINEAR);

	RenderTexture2D canvas = LoadRenderTexture(screenWidth, screenHeight);
	SetTextureFilter(canvas.texture, TEXTURE_FILTER_BILINEAR);
	SetTextureWrap(canvas.texture, TEXTURE_WRAP_CLAMP);

	RenderTexture2D canvasBlurX = LoadRenderTexture(screenWidth, screenHeight);
	SetTextureFilter(canvasBlurX.texture, TEXTURE_FILTER_BILINEAR);
	SetTextureWrap(canvasBlurX.texture, TEXTURE_WRAP_CLAMP);

	Shader blur = LoadShader(0, "blur.frag");
	int blurRenderWidthLoc = GetShaderLocation(blur, "renderWidth");
	int blurRenderHeightLoc = GetShaderLocation(blur, "renderHeight");
	int blurSecondsLoc = GetShaderLocation(blur, "seconds");
	SetShaderValue(blur, blurRenderWidthLoc, &screenWidthF, SHADER_UNIFORM_FLOAT);
	SetShaderValue(blur, blurRenderHeightLoc, &screenHeightF, SHADER_UNIFORM_FLOAT);

	Shader watershader = LoadShader(0, "watershader.frag");
	int waterBumpMapLoc = GetShaderLocation(watershader, "waterBumpMap");
	int watershaderSecondsLoc = GetShaderLocation(watershader, "seconds");
	int watershaderResolutionLoc = GetShaderLocation(watershader, "resolution");
	SetShaderValue(watershader, watershaderResolutionLoc, &resolution, SHADER_UNIFORM_VEC2);

	Texture waterBump = LoadTexture("waterbump_denoise_blur1.png");
	SetTextureFilter(waterBump, TEXTURE_FILTER_BILINEAR);

	Shader blur13 = LoadShader(0, "blur13.frag");
	int blur13resolution = GetShaderLocation(blur13, "resolution");
	int blur13direction = GetShaderLocation(blur13, "direction");
	SetShaderValue(blur13, blur13resolution, &resolution, SHADER_UNIFORM_VEC2);

	Image baroImage = LoadImage("screenshot1.jpg");
	ImageResize(&baroImage, screenWidth, screenHeight);
	Texture baroTextrue = LoadTextureFromImage(baroImage);
	SetTextureFilter(baroTextrue, TEXTURE_FILTER_BILINEAR);

	GuiSetFont(InconsolataBold);
	GuiSetStyle(DEFAULT, TEXT_SIZE, (int)(24 * scaleDPI.x));
	GuiSetStyle(DEFAULT, TEXT_SPACING, 0);
	GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, (int)(24 * scaleDPI.x));
	GuiSetStyle(STATUSBAR, BORDER_WIDTH, 2);

	// Create the Nuklear Context
	struct nk_context* ctx = InitNuklearEx(InconsolataBold, 24 * scaleDPI.x);
	
	Vector2 mousePos = { 0 };
	int mouseCellX = 0;
	int mouseCellY = 0;

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		//------------------------------------------------------------------
		// Update game logic
		//------------------------------------------------------------------
		float frametime = GetFrameTime();

		if (errorCode == OK)
		{
			handleKeys();

			if (editMap) {
				mousePos = GetMousePosition();
				mouseCellX = (int)(Clamp(mousePos.x, 0, FWIDTH * N - 1) / WIDTH);
				mouseCellY = (int)(Clamp(mousePos.y, 0, FHEIGHT * M - 1) / HEIGHT);

				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) and not(mouseCellX == player_x and mouseCellY == player_y)) {
					map[mouseCellY][mouseCellX] = selected_element;
				}
				else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
					map[mouseCellY][mouseCellX] = empty;
				}

			}
		}
		else {
			//------------------------------------------------------------------
			// Update Nuklear context
			//------------------------------------------------------------------
			/*UpdateNuklear(ctx);

			callNKErrorBoxes(ctx);

			nk_end(ctx);*/
		}
		
		//------------------------------------------------------------------
		// Draw
		//------------------------------------------------------------------
		BeginDrawing();
		
		BeginTextureMode(canvas);

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(MAGENTA);

		drawMap();
		drawPlayer();
		drawBottomBar(InconsolataBold, 24 * scaleDPI.y);

		if (editMap) {
			Rectangle rec = {
			mouseCellX * FWIDTH,
			mouseCellY * FHEIGHT,
			FWIDTH, FHEIGHT
			};
			
			Color color = { 0, 0, 0, 255 };
			if (mouseCellX == player_x and mouseCellY == player_y) {
				color.r = 255;
			}
			else {
				color.g = 255;
			}

			DrawRectangleLinesEx(rec, 2, color);
		}

		if (netToggle) {
			drawNet();
		}

		if (errorCode > OK) {
			// Render the Nuklear GUI
			//DrawNuklear(ctx);

			//drawRayguiErrorBoxes();
		}

		//BeginTextureMode(canvas);
		{
			//ClearBackground((Color) { 255, 255, 255, 0 });
			//ClearBackground(BLANK);
			Rectangle roundRect = { 100 * scaleDPI.x, 260 * scaleDPI.y, 185 * scaleDPI.x, 36 * scaleDPI.y };
			DrawRectangleRounded(roundRect, 0.5f, 6, BLACK);
			DrawRectangleRoundedLines(roundRect, 0.5f, 6, ORANGE);
		}
		EndTextureMode();

		float timeF = (float)GetTime();
		SetShaderValue(blur, blurSecondsLoc, &timeF, SHADER_UNIFORM_FLOAT);
		SetShaderValue(watershader, watershaderSecondsLoc, &timeF, SHADER_UNIFORM_FLOAT);

		Rectangle rec = { 0, 0, (float)canvas.texture.width, (float)(-canvas.texture.height) };
		Rectangle rec1 = { 0, 0, screenWidthF, screenHeightF };
		BeginShaderMode(watershader);
		{
			SetShaderValueTexture(watershader, waterBumpMapLoc, waterBump);
			DrawTextureRec(canvas.texture, rec, (Vector2) { 0.0f, 0.0f }, WHITE);
			//DrawTextureRec(baroTextrue, rec1, (Vector2) { 0.0f, 0.0f }, WHITE);
		}
		EndShaderMode();
		
		//BeginTextureMode(canvasBlurX);
		//{
		//	BeginShaderMode(blur13);
		//	{
		//		BeginShaderMode(watershader);
		//		{
		//			Vector2 dir = { 0.25f, 0.0f };
		//			SetShaderValue(blur13, blur13direction, &dir, SHADER_UNIFORM_VEC2);
		//			SetShaderValueTexture(watershader, waterBumpMapLoc, waterBump);
		//			DrawTextureRec(canvas.texture, rec, (Vector2) { 0.0f, 0.0f }, WATERBLUE);
		//		}
		//		EndShaderMode();
		//	}
		//	EndShaderMode();
		//}
		//EndTextureMode();


		//BeginShaderMode(blur13);
		//{
		//	Vector2 dir = { 0.0f, 0.25f };
		//	SetShaderValue(blur13, blur13direction, &dir, SHADER_UNIFORM_VEC2);
		//	DrawTextureRec(canvasBlurX.texture, rec, (Vector2) { 0.0f, 0.0f }, WHITE);
		//}
		//EndShaderMode();


		//drawBottomBar(InconsolataBold, 24);

		//DrawTextureRec(canvas.texture, rec, (Vector2) { 0.0f, 0.0f }, SKYBLUE);

		//DrawTextEx(Consolas, u8"Файл не найден\nПопробуйте сначала сохранить игру", (Vector2) { 100, 100 }, 24, 0, BLACK);

		// show mouse position
		//DrawText(TextFormat("%.1f %.1f", mousePos.x, mousePos.y), 5, M * HEIGHT - 30, 30, ORANGE);

		// show FPS and frametime
		//DrawText(TextFormat("%2d FPS", GetFPS()), 0, 0, 34, ORANGE);
		//DrawText(TextFormat("%4f ms", GetFrameTime()), 0, 34, 34, BEIGE);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	//UnloadFont(InconsolataRegular);
	UnloadFont(InconsolataBold);
	//UnloadFont(Consolas);
	//UnloadFont(Arial);
	//UnloadFont(InconsolataBold);

	UnloadRenderTexture(canvas);
	UnloadRenderTexture(canvasBlurX);

	UnloadShader(blur);
	UnloadShader(blur13);
	UnloadShader(watershader);
	UnloadTexture(waterBump);

	UnloadImage(baroImage);
	UnloadTexture(baroTextrue);
	
	// De-initialize the Nuklear GUI
	UnloadNuklear(ctx);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}