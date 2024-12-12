#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iso646.h>
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

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

typedef enum obj_enum { empty = 0, wall = 2, gold = 3 } obj_enum;
// TODO: do something with "empty" object
#define INVENTORY_SIZE 4
int inventory[INVENTORY_SIZE] = { 0, 0, 15, 0 };
obj_enum selected_element = gold;

typedef enum enum_ways { left, right, up, down } enum_ways;
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
		/*GuiMessageBox((Rectangle) { N * WIDTH / 2 - 50 , M*HEIGHT - 50, N * WIDTH / 2 + 50 , M*HEIGHT + 50,},
			"Ошибка сохранения",
			"Невозможно создать файл",
			"Ок;Выйти");*/
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

void load() {
	FILE* fin = fopen("savefile.txt", "r");
	if (fin == NULL) {
		printf("1) load error\n");
		/*GuiMessageBox((Rectangle) { N* WIDTH / 2 - 50, M* HEIGHT - 50, N* WIDTH / 2 + 50, M* HEIGHT + 50, },
			"Ошибка загрузки",
			"Файл не найден\nПопробуйте сначала сохранить игру",
			"Ок;Выйти");*/
		return;
	}
	int m, n;
	fscanf_s(fin, "%d%d", &m, &n);
	if (m != M || n != N) {
		printf("2) load error\n");
		/*GuiMessageBox((Rectangle) { N* WIDTH / 2 - 50, M* HEIGHT - 50, N* WIDTH / 2 + 50, M* HEIGHT + 50, },
			"Ошибка загрузки",
			"Неправильный размер карты!\nПроверьте целостность сохранения",
			"Ок;Выйти");*/
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

#define CPSIZE 213
int main() {
	//SetConfigFlags(FLAG_WINDOW_HIGHDPI);

	InitWindow(N * WIDTH, M * HEIGHT + VOFFSET, "lab16 with raylib");

	SetTargetFPS(60);

	SearchAndSetResourceDir("resources");

	int codepoints[CPSIZE] = { 0 };
	for (int i = 0; i < 127 - 32; i++) codepoints[i] = 32 + i;   // Basic ASCII characters
	for (int i = 0; i < 118; i++) codepoints[95 + i] = 1024 + i;   // Cyrillic characters

	//Font InconsolataRegular = LoadFontEx("Inconsolata-Regular.ttf", 24, NULL, 0);
	//Font InconsolataSemiBold = LoadFontEx("Inconsolata-SemiBold.ttf", 48, codepoints, 512);
	Font InconsolataBold = LoadFontEx("Inconsolata-LGC-Bold.ttf", 48, codepoints, CPSIZE);
	SetTextureFilter(InconsolataBold.texture, TEXTURE_FILTER_BILINEAR);

	//GuiSetFont(InconsolataBold);
	
	Vector2 mousePos = { 0 };
	int mouseCellX = 0;
	int mouseCellY = 0;

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		//------------------------------------------------------------------
		// Update
		//------------------------------------------------------------------
		handleKeys();
		mousePos = GetMousePosition();

		if (editMap) {
			mouseCellX = (int)(Clamp(mousePos.x, 0, FWIDTH * N - 1) / WIDTH);
			mouseCellY = (int)(Clamp(mousePos.y, 0, FHEIGHT * M - 1) / HEIGHT);

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) and not(mouseCellX == player_x and mouseCellY == player_y)) {
				map[mouseCellY][mouseCellX] = selected_element;
			}
			else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
				map[mouseCellY][mouseCellX] = empty;
			}

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
	//UnloadFont(InconsolataBold);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}