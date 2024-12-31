#define _CRT_SECURE_NO_WARNINGS

#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include <stdbool.h>
#include <iso646.h>
#include <stdlib.h>
#include <string.h>

#include "parallel_for.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define MAP_X 400
#define MAP_Y 200
#define CELL_SIZE 6
#define FCELL_SIZE (float)CELL_SIZE

#define BOTTOM_BAR_HEIGHT 60

#define PUREBLUE CLITERAL(Color){ 0, 0, 255, 255 }
#define BLACKGRAY CLITERAL(Color){30, 30, 30, 255}
#define VSGREEN CLITERAL(Color){78, 201, 176, 255}
#define WATERBLUE CLITERAL(Color){200, 240, 255, 255}

//static bool map[MAP_X][MAP_Y] = { 0 };
//static bool tempMap[MAP_X][MAP_Y] = { 0 };

bool** map;
bool** tempMap;

void* SafeMalloc(size_t size)
{
    void* buffer = malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "Error in SafeMalloc: failed to allocate %zu bytes.\n", size);
        abort();
    }
    return buffer;
}

void* SafeCalloc(size_t count, size_t size)
{
    void* buffer = calloc(count, size);
    if (buffer == NULL) {
        fprintf(stderr, "Error in SafeCalloc: failed to allocate %zu bytes.\n", count * size);
        abort();
    }
    return buffer;
}

static inline int checkCell(int x, int y) {
    if (x < 0 or y < 0 or x > MAP_X - 1 or y > MAP_Y - 1) {
        return 0;
    }
    else {
        return map[x][y];
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

//int compute_cell(int x) {
//    int neighbours = 0;
//
//    neighbours += checkCell(x - 1, y);
//    neighbours += checkCell(x - 1, y + 1);
//    neighbours += checkCell(x - 1, y - 1);
//    neighbours += checkCell(x + 1, y);
//    neighbours += checkCell(x + 1, y + 1);
//    neighbours += checkCell(x + 1, y - 1);
//    neighbours += checkCell(x, y + 1);
//    neighbours += checkCell(x, y - 1);
//
//    if (neighbours == 3) {
//        tempMap[x][y] = true;
//    }
//    else if (neighbours == 2) {
//        tempMap[x][y] = map[x][y];
//    }
//    else {
//        tempMap[x][y] = false;
//    }
//}
//
//void* compute_cell_forp(void* arg)
//{
//    int* pa = (int*)arg;
//    int* result = malloc(sizeof(*result));
//    *result = mult2(*pa);
//    return result;
//}

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

    const int screenWidth = MAP_X * CELL_SIZE;
    const int screenHeight = MAP_Y * CELL_SIZE + BOTTOM_BAR_HEIGHT;

    InitWindow(screenWidth, screenHeight, "Game of Life");

    SearchAndSetResourceDir("resources");

    int codepoints[CPSIZE] = { 0 };
    for (int i = 0; i < 127 - 32; i++) codepoints[i] = 32 + i;   // Basic ASCII characters
    for (int i = 0; i < 118; i++) codepoints[95 + i] = 1024 + i;   // Cyrillic characters

    Font InconsolataBold = LoadFontEx("Inconsolata-LGC-Bold.ttf", 36, codepoints, CPSIZE);
    SetTextureFilter(InconsolataBold.texture, TEXTURE_FILTER_BILINEAR);

    GuiSetFont(InconsolataBold);
    GuiSetStyle(DEFAULT, TEXT_SIZE, (int)(24));
    GuiSetStyle(DEFAULT, TEXT_SPACING, 0);
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, (int)(24));
    GuiSetStyle(STATUSBAR, BORDER_WIDTH, 2);

    int monitor = GetCurrentMonitor();
    int monitorFPS = GetMonitorRefreshRate(monitor);

    SetTargetFPS(monitorFPS);

    Vector2 mousePos = { 0 };
    int mouseCellX = 0;
    int mouseCellY = 0;

    bool editMap = true;
    bool netToggle = false;

    float simSpeed = 1.0f;
    int frameCounter = 0;

    int guyScreenWidth = 720;

    while (!WindowShouldClose())
    {
        frameCounter++;

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
            mouseCellX = (int)(Clamp(mousePos.x, 0, (float)(MAP_X * CELL_SIZE - 1)) / CELL_SIZE);
            mouseCellY = (int)(Clamp(mousePos.y, 0, (float)(MAP_Y * CELL_SIZE - 1)) / CELL_SIZE);

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                map[mouseCellX][mouseCellY] = true;
            }
            else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                map[mouseCellX][mouseCellY] = false;
            }
        }
        else if (FloatEquals(simSpeed, 1.0f)) {
            celluralAutomata();
        }
        else if (simSpeed < 1.0f and frameCounter >= 1 / simSpeed) {
            celluralAutomata();
            //printf("%d %d\n", frameCounter, (int)(1 / simSpeed));
            frameCounter = 0;
        }
        else if (simSpeed > 1.0f) {
            for (int i = 0; i < (int)simSpeed; i++) {
                celluralAutomata();
            }
            //printf("%f speed\n", simSpeed);
        }

        BeginDrawing();
            ClearBackground(WHITE);

            drawMap();
            drawBottomBar();

            if (netToggle) drawNet();

            if (editMap)
            {
                Rectangle rec = { mouseCellX * FCELL_SIZE, mouseCellY * FCELL_SIZE, FCELL_SIZE, FCELL_SIZE };
                DrawRectangleLinesEx(rec, 2, GREEN);
            }

            //Rectangle settingsBox = { 400, 400, 400, 200 };
            //GuiGroupBox(settingsBox, u8"Init game");
            //Rectangle valueBox1 = { 620, 420, 100, 40 };
            //GuiValueBox(valueBox1, u8"screen Width ", &guyScreenWidth, 120, 2560, true);

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

    UnloadFont(InconsolataBold);

    CloseWindow();

    return 0;
}

int WinMain() {
    return main();
}