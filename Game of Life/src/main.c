#include "raylib.h"
#include "raymath.h"
#include <stdbool.h>
#include <iso646.h>

#define MAP_X 20
#define MAP_Y 20
#define CELL_SIZE 20
#define FCELL_SIZE (float)CELL_SIZE

#define BOTTOM_BAR_HEIGHT 60

#define PUREBLUE CLITERAL(Color){ 0, 0, 255, 255 }
#define BLACKGRAY CLITERAL(Color){30, 30, 30, 255}
#define VSGREEN CLITERAL(Color){78, 201, 176, 255}
#define WATERBLUE CLITERAL(Color){200, 240, 255, 255}

static bool map[MAP_X][MAP_Y] = { 0 };
static bool tempMap[MAP_X][MAP_Y] = { 0 };

static inline int checkCell(int x, int y) {
    if (x > 0 and y > 0 and x < MAP_X - 1 and y < MAP_Y - 1) {
        return map[x][y];
    }
    else {
        return 0;
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
            else if (neighbours < 2 or neighbours > 3) {
                tempMap[x][y] = false;
            }
            else {
                tempMap[x][y] = map[x][y];
            }

        }
    }
    for (int x = 0; x < MAP_X; x++) {
        for (int y = 0; y < MAP_Y; y++) {
            map[x][y] = tempMap[x][y];
        }
    }
}

void drawMap()
{
    for (int x = 0; x < MAP_X; x++) {
        for (int y = 0; y < MAP_Y; y++) {
            int posX = x * CELL_SIZE;
            int posY = y * CELL_SIZE;

            Color color;
            if (map[x][y]) {
                color = BLACK;
            }
            else {
                color = RAYWHITE;
            }

            DrawRectangle(posX, posY, CELL_SIZE, CELL_SIZE, color);
        }
    }
}

void drawBottomBar()
{
    DrawRectangle(0, MAP_Y * CELL_SIZE, MAP_X * CELL_SIZE, BOTTOM_BAR_HEIGHT, BLACKGRAY);
}

int main()
{
    const int screenWidth = MAP_X * CELL_SIZE;
    const int screenHeight = MAP_Y * CELL_SIZE + BOTTOM_BAR_HEIGHT;

    InitWindow(screenWidth, screenHeight, "Game of Life");

    SetTargetFPS(15);

    Vector2 mousePos = { 0 };
    int mouseCellX = 0;
    int mouseCellY = 0;

    bool editMap = true;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE)) {
            editMap = !editMap;
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
        else {
            celluralAutomata();
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            drawMap();
            drawBottomBar();

            if (editMap)
            {
                Rectangle rec = {
                mouseCellX * CELL_SIZE,
                mouseCellY * CELL_SIZE,
                FCELL_SIZE, FCELL_SIZE
                };

                DrawRectangleLinesEx(rec, 2, GREEN);
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}