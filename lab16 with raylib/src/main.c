#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include "windows_functions.h"

#define RAYGUI_IMPLEMENTATION
//#define RAYGUI_PANEL_BORDER_WIDTH 2
#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 32
#define RAYGUI_MESSAGEBOX_BUTTON_HEIGHT 36
#include "raygui.h"

#define RAYLIB_NUKLEAR_IMPLEMENTATION
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#pragma warning(disable: 4116)
#include "raylib-nuklear.h"

#define M 10
#define N 15
#define HEIGHT 50
#define WIDTH 50
#define VOFFSET 50

#define FWIDTH (float)WIDTH
#define FHEIGHT (float)HEIGHT

#define PUREBLUE (Color) { 0, 0, 255, 255 }
#define BLACKGRAY (Color) {30, 30, 30, 255}
#define VSGRAY (Color) {78, 201, 176, 255}

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

typedef enum { empty = 0, wall = 2, gold = 3 } obj_enum;
// TODO: do something with "empty" object
#define INVENTORY_SIZE 4
int inventory[INVENTORY_SIZE] = { 0, 0, 15, 0 };
obj_enum selected_element = gold;

typedef enum { left, right, up, down } enum_ways;
void movePlayer(enum_ways move) {
	switch (move) {
	case left:
		if ((player_x > 0) and map[player_y][player_x - 1] != wall) player_x -= 1;
		break;
	case right:
		if ((player_x < N - 1) and map[player_y][player_x + 1] != wall) player_x += 1;
		break;
	case up:
		if ((player_y > 0) and map[player_y - 1][player_x] != wall) player_y -= 1;
		break;
	case down:
		if ((player_y < M - 1) and map[player_y + 1][player_x] != wall) player_y += 1;
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

	Vector2 goldpos = { WIDTH / 4, HEIGHT * M };
	Vector2 wallpos = { WIDTH / 4, HEIGHT * M + fontSize };
	Vector2 helppos = { WIDTH * N - 550 , HEIGHT * M };

	DrawTextEx(font, gold_string, goldpos, fontSize, 0, VSGRAY);
	DrawTextEx(font, wall_string, wallpos, fontSize, 0, VSGRAY);
	DrawTextEx(font, help_string, helppos, fontSize, 0, VSGRAY);
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
		errorCode = loadError1;
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
	const Rectangle errorBoxRect = { N * WIDTH / 2 - 200, M * HEIGHT / 2 - 75, 400, 150 };
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
		nk_rect(N * WIDTH / 2 - 200, M * HEIGHT / 2 - 72, 400, 144),
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
			u8"Проверьте целостность сохранения");
		break;
	case loadError2:
		btn = nk_error_box(ctx,
			u8"Ошибка загрузки",
			u8"Неправильный размер карты!",
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
	SetConfigFlags(FLAG_WINDOW_HIGHDPI);
	//SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(N * WIDTH, M * HEIGHT + VOFFSET, "lab16 with raylib");

	SetTargetFPS(20);

	SearchAndSetResourceDir("resources");

	int codepoints[CPSIZE] = { 0 };
	for (int i = 0; i < 127 - 32; i++) codepoints[i] = 32 + i;   // Basic ASCII characters
	for (int i = 0; i < 118; i++) codepoints[95 + i] = 1024 + i;   // Cyrillic characters

	//Font InconsolataRegular = LoadFontEx("Inconsolata-Regular.ttf", 24, NULL, 0);
	//Font InconsolataSemiBold = LoadFontEx("Inconsolata-SemiBold.ttf", 48, codepoints, 512);
	Font InconsolataBold = LoadFontEx("Inconsolata-LGC-Bold.ttf", 36, codepoints, CPSIZE);
	SetTextureFilter(InconsolataBold.texture, TEXTURE_FILTER_BILINEAR);
	//Font Arial = LoadFontEx("arial.ttf", 36, codepoints, CPSIZE);
	//SetTextureFilter(Arial.texture, TEXTURE_FILTER_BILINEAR);

	GuiSetFont(InconsolataBold);
	GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
	GuiSetStyle(DEFAULT, TEXT_SPACING, 0);
	GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, 24);
	GuiSetStyle(STATUSBAR, BORDER_WIDTH, 2);

	// Create the Nuklear Context
	struct nk_context* ctx = InitNuklearEx(InconsolataBold, 24);
	
	Vector2 mousePos = { 0 };
	int mouseCellX = 0;
	int mouseCellY = 0;

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		//------------------------------------------------------------------
		// Update game logic
		//------------------------------------------------------------------
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
			UpdateNuklear(ctx);

			callNKErrorBoxes(ctx);

			nk_end(ctx);
		}
		
		//------------------------------------------------------------------
		// Draw
		//------------------------------------------------------------------
		BeginDrawing();
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);

		drawMap();
		drawPlayer();
		drawBottomBar(InconsolataBold, 24);

		const Rectangle RoundRect = { 100, 250, 185, 36 };
		DrawRectangleRoundedLinesEx(RoundRect, 0.3f, 20, 1, BLACK);

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
			DrawNuklear(ctx);

			//drawRayguiErrorBoxes();
		}

		//DrawTextEx(InconsolataBold, u8"Файл не найден\nПопробуйте сначала сохранить игру", (Vector2) { 100, 100 }, 24, 0, BLACK);

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
	//UnloadFont(Arial);
	//UnloadFont(InconsolataBold);

	// De-initialize the Nuklear GUI
	UnloadNuklear(ctx);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}