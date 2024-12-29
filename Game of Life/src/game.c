//#include "raylib.h"
//#include <iso646.h>
//
//#include "game.h"
//
//#define PUREBLUE CLITERAL(Color){ 0, 0, 255, 255 }
//#define BLACKGRAY CLITERAL(Color){30, 30, 30, 255}
//#define VSGREEN CLITERAL(Color){78, 201, 176, 255}
//#define WATERBLUE CLITERAL(Color){200, 240, 255, 255}
//
//
//static float simSpeed = 1.0f;
//static frameCounter = 0;
//
//static Vector2 mousePos = { 0 };
//static int mouseCellX = 0;
//static int mouseCellY = 0;
//
//static bool editMap = true;
//static bool netToggle = true;
//
//static inline int CheckCell(int x, int y) {
//    if (x < 0 or y < 0 or x > MAP_X - 1 or y > MAP_Y - 1) {
//        return 0;
//    }
//    else {
//        return map[x][y];
//    }
//}
//
//static void GameOfLife()
//{
//    for (int x = 0; x < MAP_X; x++) {
//        for (int y = 0; y < MAP_Y; y++) {
//            int neighbours = 0;
//
//            neighbours += CheckCell(x - 1, y);
//            neighbours += CheckCell(x - 1, y + 1);
//            neighbours += CheckCell(x - 1, y - 1);
//            neighbours += CheckCell(x + 1, y);
//            neighbours += CheckCell(x + 1, y + 1);
//            neighbours += CheckCell(x + 1, y - 1);
//            neighbours += CheckCell(x, y + 1);
//            neighbours += CheckCell(x, y - 1);
//
//            if (neighbours == 3) {
//                tempMap[x][y] = true;
//            }
//            else if (neighbours == 2) {
//                tempMap[x][y] = map[x][y];
//            }
//            else {
//                tempMap[x][y] = false;
//            }
//
//        }
//    }
//    memcpy(map, tempMap, MAP_X * MAP_Y * sizeof(bool));
//}
//
//static void DrawMap()
//{
//    for (int x = 0; x < MAP_X; x++) {
//        for (int y = 0; y < MAP_Y; y++) {
//            if (map[x][y]) {
//                int posX = x * CELL_SIZE;
//                int posY = y * CELL_SIZE;
//                DrawRectangle(posX, posY, CELL_SIZE, CELL_SIZE, BLACK);
//            }
//        }
//    }
//}
//
//static void DrawNet() {
//    for (int i = 0; i <= MAP_X * CELL_SIZE; i += CELL_SIZE) {
//        DrawLine(i, 0, i, MAP_Y * CELL_SIZE, GRAY);
//        DrawLine(i + 1, 0, i + 1, MAP_Y * CELL_SIZE, GRAY);
//    }
//
//    for (int i = 0; i <= MAP_Y * CELL_SIZE; i += CELL_SIZE) {
//        DrawLine(0, i, MAP_X * CELL_SIZE, i, GRAY);
//        DrawLine(0, i - 1, MAP_X * CELL_SIZE, i - 1, GRAY);
//    }
//}
//
//void UpdateGame() {
//    frameCounter++;
//
//    if (IsKeyPressed(KEY_SPACE)) {
//        editMap = !editMap;
//    }
//    if (IsKeyPressed(KEY_N)) {
//        netToggle = !netToggle;
//    }
//    if (IsKeyPressed(KEY_EQUAL)) {
//        simSpeed *= 2.0f;
//    }
//    if (IsKeyPressed(KEY_MINUS)) {
//        simSpeed *= 0.5f;
//    }
//
//    if (editMap)
//    {
//        mousePos = GetMousePosition();
//        mouseCellX = (int)(Clamp(mousePos.x, 0, (float)(MAP_X * CELL_SIZE - 1)) / CELL_SIZE);
//        mouseCellY = (int)(Clamp(mousePos.y, 0, (float)(MAP_Y * CELL_SIZE - 1)) / CELL_SIZE);
//
//        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
//            map[mouseCellX][mouseCellY] = true;
//        }
//        else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
//            map[mouseCellX][mouseCellY] = false;
//        }
//    }
//    else if (FloatEquals(simSpeed, 1.0f)) {
//        celluralAutomata();
//    }
//    else if (simSpeed < 1.0f and frameCounter >= 1 / simSpeed) {
//        celluralAutomata();
//        //printf("%d %d\n", frameCounter, (int)(1 / simSpeed));
//        frameCounter = 0;
//    }
//    else if (simSpeed > 1.0f) {
//        for (int i = 0; i < (int)simSpeed; i++) {
//            celluralAutomata();
//        }
//        //printf("%f speed\n", simSpeed);
//    }
//}
//
//void DrawGame() {
//    DrawMap();
//
//    if (netToggle) DrawNet();
//
//    if (editMap)
//    {
//        Rectangle rec = { mouseCellX * FCELL_SIZE, mouseCellY * FCELL_SIZE, FCELL_SIZE, FCELL_SIZE };
//        DrawRectangleLinesEx(rec, 2, GREEN);
//    }
//}