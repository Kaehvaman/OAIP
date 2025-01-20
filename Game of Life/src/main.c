#define _CRT_SECURE_NO_WARNINGS

#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"

#include <stdbool.h>
#include <iso646.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

#include "dynamic_memory.h"
#include "memory_arena.h"

#define MAP_X 100
#define MAP_Y 100
#define CELL_SIZE 10
#define FCELL_SIZE (float)CELL_SIZE
#define BOTTOM_BAR_HEIGHT 60

#define PUREBLUE CLITERAL(Color){ 0, 0, 255, 255 }
#define BLACKGRAY CLITERAL(Color){30, 30, 30, 255}
#define VSGREEN CLITERAL(Color){78, 201, 176, 255}
#define WATERBLUE CLITERAL(Color){200, 240, 255, 255}

bool** map;
bool** tempMap;

typedef struct {
	bool** map;
	bool** tempMap;
	int startX;
	int endX;
	int startY;
	int endY;
} golArgs;

thrd_t threads[32];
golArgs thread_args[32];
int numThreads = 5;

static inline int checkCell(int x, int y)
{
	if (x < 0 or y < 0 or x > MAP_X - 1 or y > MAP_Y - 1) {
		return 0;
	}
	else {
		return map[x][y];
	}
}

static inline single_gol(int x, int y)
{
	int neighbours = 0;

	neighbours += checkCell(x - 1, y);
	neighbours += checkCell(x - 1, y + 1);
	neighbours += checkCell(x - 1, y - 1);
	neighbours += checkCell(x + 1, y);
	neighbours += checkCell(x + 1, y + 1);
	neighbours += checkCell(x + 1, y - 1);
	neighbours += checkCell(x, y + 1);
	neighbours += checkCell(x, y - 1);

	if (neighbours == 2) {
		tempMap[x][y] = map[x][y];
	}
	else if (neighbours == 3) {
		tempMap[x][y] = true;
	}
	else {
		tempMap[x][y] = false;
	}
}



int gol_thread(void* arg_ptr)
{
	golArgs args = *(golArgs*)(arg_ptr);

	for (int x = args.startX + 1; x < args.endX - 1; x++) {
		for (int y = args.startY + 1; y < args.endY - 1; y++) {
			int neighbours = 0;

			neighbours += map[x - 1][y];
			neighbours += map[x - 1][y + 1];
			neighbours += map[x - 1][y - 1];
			neighbours += map[x + 1][y];
			neighbours += map[x + 1][y + 1];
			neighbours += map[x + 1][y - 1];
			neighbours += map[x][y + 1];
			neighbours += map[x][y - 1];

			if (neighbours == 2) {
				tempMap[x][y] = map[x][y];
			}
			else if (neighbours == 3) {
				tempMap[x][y] = true;
			}
			else {
				tempMap[x][y] = false;
			}

		}
	}

	for (int x = args.startX; x < args.endX; x++) {
		int neighbours = 0;

		neighbours += map[x - 1][y];
		neighbours += map[x - 1][y + 1];
		neighbours += map[x - 1][y - 1];
		neighbours += map[x + 1][y];
		neighbours += map[x + 1][y + 1];
		neighbours += map[x + 1][y - 1];
		neighbours += map[x][y + 1];
		neighbours += map[x][y - 1];

		if (neighbours == 2) {
			tempMap[x][y] = map[x][y];
		}
		else if (neighbours == 3) {
			tempMap[x][y] = true;
		}
		else {
			tempMap[x][y] = false;
		}
	}
	for (int x = args.startX; x < args.endX; x++) {

	}
	for (int y = args.startY; y < args.endY; y++) {

	}
	for (int y = args.startY; y < args.endY; y++) {

	}
	

	return 0;
}

void gol_thread_init() {
	int deltaX = MAP_X / numThreads;
	int remainder = MAP_X % numThreads;

	for (int i = 0; i < numThreads - 1; i++) {
		thread_args[i] = (golArgs){
			.startX = deltaX * i,
			.endX = deltaX * (i + 1),
			.startY = 0,
			.endY = MAP_Y
		};
	}
	thread_args[numThreads - 1] = (golArgs){
		.startX = deltaX * (numThreads - 1),
		.endX = MAP_X,
		.startY = 0,
		.endY = MAP_Y
	};
}

void gol_thread_start()
{
	for (int i = 0; i < numThreads; i++) {
		thrd_create(&threads[i], gol_thread, &thread_args[i]);
	}
	for (int i = 0; i < numThreads; i++) {
		thrd_join(threads[i], NULL);
	}
	for (int x = 0; x < MAP_X; x++) {
		memcpy(map[x], tempMap[x], MAP_Y * sizeof(bool));
	}
}

void celluralAutomata()
{
	for (int x = 0; x < MAP_X; x++) {
		for (int y = 0; y < MAP_Y; y++) {
			int neighbours = 0;

			neighbours += checkCell(x - 1, y);
			neighbours += checkCell(x - 1, y + 1);
			neighbours += checkCell(x - 1, y - 1);
			neighbours += checkCell(x + 1, y);
			neighbours += checkCell(x + 1, y + 1);
			neighbours += checkCell(x + 1, y - 1);
			neighbours += checkCell(x, y + 1);
			neighbours += checkCell(x, y - 1);

			if (neighbours == 3) {
				tempMap[x][y] = true;
			}
			else if (neighbours == 2) {
				tempMap[x][y] = map[x][y];
			}
			else {
				tempMap[x][y] = false;
			}

		}
	}
	for (int x = 0; x < MAP_X; x++) {
		memcpy(map[x], tempMap[x], MAP_Y * sizeof(bool));
	}
}

void ClearMap() {
	for (int x = 0; x < MAP_X; x++) {
		memset(map[x], 0, MAP_Y * sizeof(bool));
	}
}

void drawMap()
{
	for (int x = 0; x < MAP_X; x++) {
		for (int y = 0; y < MAP_Y; y++) {
			if (map[x][y]) {
				int posX = x * CELL_SIZE;
				int posY = y * CELL_SIZE;
				DrawRectangle(posX, posY, CELL_SIZE, CELL_SIZE, BLACK);
			}
		}
	}
}

void drawNet() {
	for (int i = 0; i <= MAP_X * CELL_SIZE; i += CELL_SIZE) {
		DrawLine(i, 0, i, MAP_Y * CELL_SIZE, GRAY);
		DrawLine(i+1, 0, i+1, MAP_Y * CELL_SIZE, GRAY);
	}

	for (int i = 0; i <= MAP_Y * CELL_SIZE; i += CELL_SIZE) {
		DrawLine(0, i, MAP_X * CELL_SIZE, i, GRAY);
		DrawLine(0, i-1, MAP_X * CELL_SIZE, i-1, GRAY);
	}
}

void drawBottomBar()
{
	DrawRectangle(0, MAP_Y * CELL_SIZE, MAP_X * CELL_SIZE, BOTTOM_BAR_HEIGHT, BLACKGRAY);
}

#define CPSIZE 213
int main()
{
	map = (bool**)SafeMalloc(MAP_X * sizeof(bool*));
	tempMap = (bool**)SafeMalloc(MAP_X * sizeof(bool*));
	for (int x = 0; x < MAP_X; x++) {
		map[x] = (bool*)SafeCalloc(MAP_Y, sizeof(bool));
		tempMap[x] = (bool*)SafeCalloc(MAP_Y, sizeof(bool));
	}

	gol_thread_init();

	/*Arena arena = ArenaCreate(SafeCalloc(1024 * 1024, 1), 1024 * 1024);
	map = (bool**)ArenaAlloc(&arena, MAP_X * sizeof(bool*));
	tempMap = (bool**)ArenaAlloc(&arena, MAP_X * sizeof(bool*));
	for (int x = 0; x < MAP_X; x++) {
		map[x] = (bool*)ArenaAlloc(&arena, MAP_Y * sizeof(bool));
		tempMap[x] = (bool*)ArenaAlloc(&arena, MAP_Y * sizeof(bool));
	}*/

	const int screenWidth = MAP_X * CELL_SIZE;
	const int screenHeight = MAP_Y * CELL_SIZE + BOTTOM_BAR_HEIGHT;

	SetConfigFlags(FLAG_VSYNC_HINT);

	InitWindow(screenWidth, screenHeight, "Game of Life");

	int monitor = GetCurrentMonitor();
	int monitorFPS = GetMonitorRefreshRate(monitor);

	SetTargetFPS(monitorFPS);

	SearchAndSetResourceDir("resources");

	int codepoints[CPSIZE] = { 0 };
	for (int i = 0; i < 127 - 32; i++) codepoints[i] = 32 + i;   // Basic ASCII characters
	for (int i = 0; i < 118; i++) codepoints[95 + i] = 1024 + i;   // Cyrillic characters

	Font InconsolataBold = LoadFontEx("Inconsolata-LGC-Bold.ttf", 36, codepoints, CPSIZE);
	SetTextureFilter(InconsolataBold.texture, TEXTURE_FILTER_BILINEAR);

	Vector2 mousePos = { 0 };
	Vector2 mouseWorldPos = { 0 };
	int mouseWorldCellX = 0;
	int mouseWorldCellY = 0;

	bool editMap = true;
	bool netToggle = false;

	float simSpeed = 1.0f;
	int frameCounter = 0;

	int guiScreenWidth = 720;

	Camera2D camera = {
		.target = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f },
		.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f },
		.rotation = 0.0f,
		.zoom = 1.0f
	};
	int cameraSpeed;
	float frametime;
	//float mouseWheel;

	while (!WindowShouldClose())
	{
		frameCounter++;
		frametime = GetFrameTime();

		if (IsKeyPressed(KEY_SPACE)) {
			editMap = !editMap;
		}
		if (IsKeyPressed(KEY_N)) {
			netToggle = !netToggle;
		}
		if (IsKeyPressed(KEY_EQUAL)) {
			simSpeed *= 2.0f;
		}
		if (IsKeyPressed(KEY_MINUS)) {
			simSpeed *= 0.5f;
		}
		if (IsKeyPressed(KEY_C)) {
			ClearMap();
		}

		if (editMap)
		{
			mousePos = GetMousePosition();
			mouseWorldPos = GetScreenToWorld2D(mousePos, camera);
			mouseWorldCellX = (int)(Clamp(mouseWorldPos.x, 0, (float)(MAP_X * CELL_SIZE - 1)) / CELL_SIZE);
			mouseWorldCellY = (int)(Clamp(mouseWorldPos.y, 0, (float)(MAP_Y * CELL_SIZE - 1)) / CELL_SIZE);

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
				map[mouseWorldCellX][mouseWorldCellY] = true;
			}
			else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
				map[mouseWorldCellX][mouseWorldCellY] = false;
			}
		}
		else if (FloatEquals(simSpeed, 1.0f)) {
			//celluralAutomata();
			gol_thread_start();
		}
		else if (simSpeed < 1.0f and frameCounter >= 1 / simSpeed) {
			//celluralAutomata();
			gol_thread_start();
			frameCounter = 0;
		}
		else if (simSpeed > 1.0f) {
			for (int i = 0; i < (int)simSpeed; i++) {
				//celluralAutomata();
				gol_thread_start();
			}
			//printf("%f speed\n", simSpeed);
		}



		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			cameraSpeed = 1000;
		}
		else {
			cameraSpeed = 200;
		}

		if (IsKeyDown(KEY_W)) {
			camera.target.y -= cameraSpeed * frametime;
		}
		if (IsKeyDown(KEY_S)) {
			camera.target.y += cameraSpeed * frametime;
		}
		if (IsKeyDown(KEY_A)) {
			camera.target.x -= cameraSpeed * frametime;
		}
		if (IsKeyDown(KEY_D)) {
			camera.target.x += cameraSpeed * frametime;
		}

		BeginDrawing();

			ClearBackground(WHITE);

			BeginMode2D(camera);

				drawMap();
				Rectangle rec = { -2, -2, MAP_X * CELL_SIZE + 4, MAP_Y * CELL_SIZE + 4 };

				DrawRectangleLinesEx(rec, 2.0f, RED);

				if (netToggle) drawNet();

				if (editMap)
				{
					Rectangle rec = { mouseWorldCellX * FCELL_SIZE, mouseWorldCellY * FCELL_SIZE, FCELL_SIZE, FCELL_SIZE };
					DrawRectangleLinesEx(rec, 2, GREEN);
				}

			EndMode2D();

			drawBottomBar();

			DrawFPS(0, MAP_Y * CELL_SIZE);
			DrawText(TextFormat("%.4fx", simSpeed), 0, MAP_Y * CELL_SIZE + 20, 20, ORANGE);
			DrawText(TextFormat("%.1f TPS", GetFPS() * simSpeed), 0, MAP_Y * CELL_SIZE + 40, 20, BLUE);

		EndDrawing();
	}

	for (int x = 0; x < MAP_X; x++) {
		free(map[x]);
		free(tempMap[x]);
	}
	free(map);
	free(tempMap);

	//ArenaDestroy(&arena);

	UnloadFont(InconsolataBold);

	CloseWindow();

	return 0;
}

int WinMain() {
	return main();
}