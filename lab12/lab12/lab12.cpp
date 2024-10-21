// lab12.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab12.h"

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
    LoadStringW(hInstance, IDC_LAB12, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB12));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB12));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB12);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void drawNet(HDC hdc, int width, int height, int step) {
    for (int i = 0; i <= width; i = i + step) {
        MoveToEx(hdc, i, 0, NULL);
        LineTo(hdc, i, height);
    }

    for (int i = 0; i <= height; i = i + step) {
        MoveToEx(hdc, 0, i, NULL);
        LineTo(hdc, width, i);
    }
}

void drawImage1(HDC hdc, int cx, int cy, COLORREF color) {
    HPEN hPen = CreatePen(PS_SOLID, 4, color);
    SelectObject(hdc, hPen);

    POINT p[4] = {
        cx,        	cy - 20,
        cx + 20,		cy + 20,
        cx - 20,    	cy + 20,
        cx,        	cy - 20
    };
    Polyline(hdc, p, 4);

    DeleteObject(hPen);
}

void drawImage2(HDC hdc, int cx, int cy, COLORREF color) {
    HPEN hPen = CreatePen(PS_SOLID, 4, color);
    SelectObject(hdc, hPen);

    POINT p[5] = {
        cx,        	cy - 20,
        cx + 20,	cy,
        cx,         cy + 20,
        cx - 20,    cy,
        cx,        	cy - 20
    };
    Polyline(hdc, p, 5);

    DeleteObject(hPen);
}

void drawImage3(HDC hdc, int cx, int cy, COLORREF color) {
    HPEN hPen = CreatePen(PS_SOLID, 1, color);
    SelectObject(hdc, hPen);

    POINT p[5] = {
        cx,        	cy,
        cx + 20,	cy - 20,
        cx,         cy + 20,
        cx - 20,    cy - 20,
        cx,        	cy
    };
    Polyline(hdc, p, 5);

    DeleteObject(hPen);
}

struct Image {
    int x;
    int y;
    int vx;
    int vy;
    COLORREF color;
};
struct Image im1 = { 100, 100, 10, 10, RGB(200, 100, 128) };
struct Image im2 = { 400, 100, -10, -10, RGB(100, 200, 128) };

#define IMG3NUM 8
struct Image im3[IMG3NUM] = {
    { 300, 100, 8, 10, RGB(150, 150, 220) },
    { 300, 100, -4, 7, RGB(150, 150, 220) },
    { 300, 100, -4, -11, RGB(150, 150, 220) },
    { 300, 100, 3, 15, RGB(150, 150, 220) },
    { 300, 100, 14, 7, RGB(150, 150, 220) },
    { 300, 100, -10, 10, RGB(150, 150, 220) },
    { 300, 100, 5, -10, RGB(150, 150, 220) },
    { 300, 100, -10, -7, RGB(150, 150, 220) },
};

void bounce(RECT rect, struct Image* pim) {
    if ((*pim).y >= rect.bottom and (*pim).vy > 0) {
        (*pim).vy = -(*pim).vy;
        (*pim).y = rect.bottom;
    }
    if ((*pim).y < rect.top + 1) {
        (*pim).vy = -(*pim).vy;
        (*pim).y = rect.top;
    }
    if ((*pim).x > rect.right - 1) {
        (*pim).vx = -(*pim).vx;
        (*pim).x = rect.right;
    }
    if ((*pim).x < rect.left + 1) {
        (*pim).vx = -(*pim).vx;
        (*pim).x = rect.left;
    }
}

//void bounce(RECT rect, struct Image* pim) {
//    if ((*pim).y > rect.bottom - 1) {
//        (*pim).vy = -(*pim).vy;
//        (*pim).y = rect.bottom;
//    }
//    if ((*pim).y < rect.top + 1) {
//        (*pim).vy = -(*pim).vy;
//        (*pim).y = rect.top;
//    }
//    if ((*pim).x > rect.right - 1) {
//        (*pim).vx = -(*pim).vx;
//        (*pim).x = rect.right;
//    }
//    if ((*pim).x < rect.left + 1) {
//        (*pim).vx = -(*pim).vx;
//        (*pim).x = rect.left;
//    }
//}

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
    case WM_CREATE:
        {
            SetTimer(hWnd, 1, 100, 0);
        }
        break;
    case WM_TIMER:
        {
            im1.x += im1.vx; im1.y += im1.vy;
            im2.x += im2.vx; im2.y += im2.vy;
            for (int i = 0; i < IMG3NUM; i++) {
                im3[i].x += im3[i].vx; im3[i].y += im3[i].vy;
            }
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...

            RECT rect;
            GetClientRect(hWnd, &rect);
            drawNet(hdc, rect.right, rect.bottom, 50);

            bounce(rect, &im1);
            bounce(rect, &im2);
            for (int i = 0; i < IMG3NUM; i++) {
                bounce(rect, &im3[i]);
            }

            drawImage1(hdc, im1.x, im1.y, im1.color);
            drawImage2(hdc, im2.x, im2.y, im2.color);
            for (int i = 0; i < IMG3NUM; i++) {
                drawImage3(hdc, im3[i].x, im3[i].y, im3[i].color);
            }

            EndPaint(hWnd, &ps);
        }
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
