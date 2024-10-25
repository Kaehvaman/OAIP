// lab16.cpp : Определяет точку входа для приложения.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "lab16.h"
#include "stdio.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB16, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB16));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB16));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB16);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

#define M 10
#define N 15
#define WIDTH 50
#define HEIGHT 50

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   // стиль окна без кнопки разворачивания на весь экран и без возможности измения размера
   int wstyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);

   RECT wnd = { 0, 0, N * WIDTH, M * HEIGHT }; // желаемый размер клиентской области окна
   AdjustWindowRectEx(&wnd, wstyle, 1, WS_EX_COMPOSITED);

   int width = wnd.right - wnd.left;
   int height = wnd.bottom - wnd.top;

   RECT workarea;
   SystemParametersInfoW(SPI_GETWORKAREA, 0, &workarea, 0); // get size of primary desktop without taskbar

   int cx = ((workarea.right - workarea.left) / 2) - (width / 2);
   int cy = ((workarea.bottom - workarea.top) / 2) - (height / 2);

   HWND hWnd = CreateWindowExW(WS_EX_COMPOSITED, szWindowClass, szTitle, wstyle,
      cx, cy, width, height, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

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

enum obj_enum {empty = 0, wall = 2, gold = 3};
// TODO: do something with "empty" object
#define INVENTORY_SIZE 4
int inventory[INVENTORY_SIZE] = { 0, 0, 15, 0 };
obj_enum selected_element = gold;

enum enum_ways { left, right, up, down };
void movePlayer(enum_ways move) {
    switch (move) {
    case left:
        if ((player_x > 0) and map[player_y][player_x - 1] != 2) player_x -= 1;
        break;
    case right:
        if ((player_x < N - 1) and map[player_y][player_x + 1] != 2) player_x += 1;
        break;
    case up:
        if ((player_y > 0) and map[player_y - 1][player_x] != 2) player_y -= 1;
        break;
    case down:
        if ((player_y < M - 1) and map[player_y + 1][player_x] != 2) player_y += 1;
        break;
    }
    if (map[player_y][player_x] == gold) {
        map[player_y][player_x] = 0;
        inventory[gold]++;
    }
}

void putElement(enum_ways way, obj_enum element) {
    if (element != empty && inventory[element] == 0) return;

    switch (way) {
    case left:
        if ((player_x > 0) and map[player_y][player_x - 1] == 0){
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

void drawNet(HDC hdc) {
    for (int i = 0; i <= N * WIDTH; i = i + WIDTH) {
        MoveToEx(hdc, i, 0, NULL);
        LineTo(hdc, i, M*HEIGHT);
    }

    for (int i = 0; i <= M * HEIGHT; i = i + HEIGHT) {
        MoveToEx(hdc, 0, i, NULL);
        LineTo(hdc, N * WIDTH, i);
    }
}

void drawMap(HDC hdc) {
    // кисть для пустого поля
    HBRUSH hBrushEmptyCell = CreateSolidBrush(RGB(200, 200, 200)); // серый
    // кисть для поля с золотом
    HBRUSH hBrushGold = CreateSolidBrush(RGB(255, 255, 0)); // желтый
    // кисть для стены
    HBRUSH hBrushWall = CreateSolidBrush(RGB(0, 0, 0)); // черный
    // кисть для игрока
    HBRUSH hBrushMan = CreateSolidBrush(RGB(0, 0, 255)); // синий

    // Коды ячеек:
    // 0 - свободна
    // 1 - 
    // 2 - препятствие
    // 3 - золото
    HBRUSH brush[4] = { hBrushEmptyCell, hBrushMan, hBrushWall, hBrushGold };

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {

            int x1 = j * WIDTH;
            int x2 = (j + 1) * WIDTH;
            int y1 = i * HEIGHT;
            int y2 = (i + 1) * HEIGHT;

            RECT r = { x1, y1, x2, y2 };
            FillRect(hdc, &r, brush[map[i][j]]);
        }
    }
    // Все кисти удаляем!!!
    for (int i = 0; i < 4; i++) {
        DeleteObject(brush[i]);
    }
}

void drawPlayer(HDC hdc) {
    HBRUSH hBrushMan = CreateSolidBrush(RGB(0, 0, 255)); // синий
    int x1 = player_x * WIDTH;
    int x2 = (player_x + 1) * WIDTH;
    int y1 = player_y * HEIGHT;
    int y2 = (player_y + 1) * HEIGHT;
    RECT r = { x1, y1, x2, y2 };
    FillRect(hdc, &r, hBrushMan);
}

void save() {
    FILE* fout = fopen("savefile.txt", "w");
    if (fout == NULL) {
        puts("Невозможно создать файл");
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
        puts("Файл не найден");
        return;
    }
    int m, n;
    fscanf_s(fin, "%d%d", &m, &n);
    if (m != M || n != N) {
        printf("Неправильный размер карты!");
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

int clip(int n, int lower, int upper) {
    return max(lower, min(n, upper));
}

char count_string[30];

bool netToggle = false;

enum keyboard {
    VK_0 = 48, VK_1, VK_2, VK_3, VK_4, VK_5, VK_6, VK_7, VK_8, VK_9,
    VK_A = 65, VK_B, VK_C, VK_D, VK_E, VK_F, VK_G, VK_H,
    VK_I, VK_J, VK_K, VK_L, VK_M, VK_N, VK_O, VK_P, VK_Q,
    VK_R, VK_S, VK_T, VK_U, VK_V, VK_W, VK_X, VK_Y, VK_Z
};

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...

            /*RECT textrect = {
                (player_x - 1) * WIDTH, (player_y + 1) * HEIGHT,
                (player_x + 2) * WIDTH, (player_y + 2) * HEIGHT
            };*/

            RECT textrect = { 0, 0, 100, 50 };

            drawMap(hdc);
            drawPlayer(hdc);
            if (netToggle) drawNet(hdc);
            
            if (selected_element == gold) sprintf(count_string, "gold = %d", inventory[gold]);
            else sprintf(count_string, "wall = %d", inventory[wall]);
            
            //SetBkMode(hdc, TRANSPARENT);
            DrawTextA(hdc, count_string, -1, &textrect, (DT_SINGLELINE | DT_TOP | DT_CENTER));

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_F5:
            save();
            break;
        case VK_F6:
            load();
            break;
        case VK_SPACE:
            netToggle = !netToggle;
            break;
        case VK_W:
            movePlayer(up);
            break;
        case VK_S:
            movePlayer(down);
            break;
        case VK_D:
            movePlayer(right);
            break;
        case VK_A:
            movePlayer(left);
            break;
        case VK_1:
            stomp(1);
            break;
        case VK_2:
            stomp(2);
            break;
        case VK_Z:
            deathbeam(right);
            break;
        case VK_G:
            if (selected_element == gold) selected_element = wall;
            else selected_element = gold;
            break;
        case VK_LEFT:
            putElement(left, selected_element);
            break;
        case VK_RIGHT:
            putElement(right, selected_element);
            break;
        case VK_UP:
            putElement(up, selected_element);
            break;
        case VK_DOWN:
            putElement(down, selected_element);
            break;
        }
        InvalidateRect(hWnd, NULL, FALSE);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
