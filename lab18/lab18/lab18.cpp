// lab18.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab18.h"
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
    LoadStringW(hInstance, IDC_LAB18, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB18));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB18));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB18);
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

   HWND hWnd = CreateWindowExW(WS_EX_COMPOSITED, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

bool netToggle = true;

void drawNet(HDC hdc, int width, int height, int hstep, int vstep) {
    for (int i = 0; i <= width; i = i + hstep) {
        MoveToEx(hdc, i, 0, NULL);
        LineTo(hdc, i, height);
    }

    for (int i = 0; i <= height; i = i + vstep) {
        MoveToEx(hdc, 0, i, NULL);
        LineTo(hdc, width, i);
    }
}

void drawTriangle(HDC hdc, int cx, int cy, int size) {
    HPEN hPen = CreatePen(PS_SOLID, 3, RGB(78, 201, 176));
    SelectObject(hdc, hPen);

    POINT p[4] = {
        cx,        	cy - size,
        cx + size,	cy + size,
        cx - size,  cy + size,
        cx,        	cy - size
    };
    Polyline(hdc, p, 4);

    DeleteObject(hPen);
}

void drawHourglass(HDC hdc, int cx, int cy, int size) {
    HPEN hPen = CreatePen(PS_SOLID, 3, RGB(78, 180, 200));
    SelectObject(hdc, hPen);

    POINT p[5] = {
        cx - size / 2,  cy - size,
        cx + size / 2,	cy - size,
        cx - size,      cy + size,
        cx + size,      cy + size,
        cx - size / 2,  cy - size
    };
    Polyline(hdc, p, 5);

    DeleteObject(hPen);
}

void drawRomb(HDC hdc, int cx, int cy, int size) {
    HPEN hPen = CreatePen(PS_SOLID, 3, RGB(78, 201, 176));
    SelectObject(hdc, hPen);

    POINT p[5] = {
        cx,         cy - size,
        cx + size,	cy,
        cx,         cy + size,
        cx - size,  cy,
        cx,         cy - size,
    };
    Polyline(hdc, p, 5);

    DeleteObject(hPen);
}

void drawStar(HDC hdc, int cx, int cy, int size) {
    HPEN hPen = CreatePen(PS_SOLID, 3, RGB(78, 180, 255));
    SelectObject(hdc, hPen);

    POINT p[9] = {
        cx,             cy - size,
        cx + size / 4,	cy - size / 4,
        cx + size,      cy,
        cx + size / 4,  cy + size / 4,
        cx,             cy + size,
        cx - size / 4,  cy + size / 4,
        cx - size,      cy,
        cx - size / 4,  cy - size / 4,
        cx,             cy - size
    };
    Polyline(hdc, p, 9);

    DeleteObject(hPen);
}

void drawCirle(HDC hdc, int cx, int cy, int size) {
    HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 255));
    SelectObject(hdc, hPen);

    Ellipse(hdc, cx - size, cy - size, cx + size, cy + size);

    DeleteObject(hPen);
}

void drawRecursiveTriangle(HDC hdc, int cx, int cy, int size, int mode) {
    drawTriangle(hdc, cx, cy, size);

    if (size < 20) {
        return;
    }

    if (mode > 0 && mode != 3) drawRecursiveTriangle(hdc, cx, cy - size, size / 2, mode);
    if (mode > 1 && mode != 4) drawRecursiveTriangle(hdc, cx + size, cy + size, size / 2, mode);
    if (mode > 2) drawRecursiveTriangle(hdc, cx - size, cy + size, size / 2, mode);
}

void drawRecursiveHourglass(HDC hdc, int cx, int cy, int size, int mode) {
    drawHourglass(hdc, cx, cy, size);
    if (size < 20) {
        return;
    }

    if (mode >= 1 && mode < 4) drawRecursiveHourglass(hdc, cx - size / 2, cy - size, size / 2, mode);
    if (mode >= 2 && mode < 4) drawRecursiveHourglass(hdc, cx + size / 2, cy - size, size / 2, mode);
    if (mode >= 3 && mode < 5) {
        drawRecursiveHourglass(hdc, cx - size, cy + size, size / 2, mode);
        drawRecursiveHourglass(hdc, cx + size, cy + size, size / 2, mode);
    }
    if (mode == 5 || mode == 7) drawRecursiveHourglass(hdc, cx - size, cy, size / 2, mode);
    if (mode == 6 || mode == 7) drawRecursiveHourglass(hdc, cx + size, cy, size / 2, mode);

}

void drawRecursiveRomb(HDC hdc, int cx, int cy, int size, int mode) {
    drawRomb(hdc, cx, cy, size);
    if (size < 20) {
        return;
    }
    drawRecursiveRomb(hdc, cx - size, cy, size / 2, mode);
    drawRecursiveRomb(hdc, cx + size, cy, size / 2, mode);
    if (mode == 1 || mode == 3) drawRecursiveRomb(hdc, cx, cy + size, size / 2, mode);
    if (mode == 2 || mode == 3) drawRecursiveRomb(hdc, cx, cy - size, size / 2, mode);
}

void drawRecursiveStar(HDC hdc, int cx, int cy, int size, int mode) {
    drawStar(hdc, cx, cy, size);
    if (size < 20) {
        return;
    }
    if (mode == 0 || mode == 2) drawRecursiveStar(hdc, cx - size, cy, size / 2, mode);
    if (mode == 0) drawRecursiveStar(hdc, cx + size, cy, size / 2, mode);
    if (mode == 1 || mode == 2) drawRecursiveStar(hdc, cx, cy + size, size / 2, mode);
    if (mode == 1 || mode == 2) drawRecursiveStar(hdc, cx, cy - size, size / 2, mode);
}

int circlecount = 0;
void drawRecursiveCircle(HDC hdc, int cx, int cy, int size, int i) {
    drawCirle(hdc, cx, cy, size);
    i--;
    circlecount++;

    static HFONT hFont = CreateFontW(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

    SelectObject(hdc, hFont);
    SetTextColor(hdc, RGB(0, 0, 0));
    SetBkMode(hdc, TRANSPARENT);

    static char circle_string[10];
    sprintf_s(circle_string, "%d", circlecount);
    RECT circlerect = { cx - size, cy - size, cx + size, cy + size };

    DrawTextA(hdc, circle_string, -1, &circlerect, (DT_SINGLELINE | DT_VCENTER | DT_CENTER));

    if (i == 0) {
        return;
    }

    drawRecursiveCircle(hdc, cx, cy - size, size / 2, i);
    drawRecursiveCircle(hdc, cx + size, cy, size / 2, i);
}

int trmode = 0;
int hgmode = 0;
int rbmode = 0;
int imageVar = 0;

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

            RECT rect;
            GetClientRect(hWnd, &rect);

            if (netToggle) drawNet(hdc, rect.right, rect.bottom, 50, 50);

            drawRecursiveTriangle(hdc, 300, 300, 100, trmode);            
            drawRecursiveHourglass(hdc, 700, 300, 100, hgmode);

            drawRecursiveRomb(hdc, 300, 700, 100, rbmode);
            drawRecursiveStar(hdc, 1100, 300, 100, rbmode);

            drawRecursiveCircle(hdc, 1300, 700, 200, 5);
            circlecount = 0;

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_SPACE:
            netToggle = !netToggle;
            break;
        default:
            trmode++;
            hgmode++;
            rbmode++;
            if (trmode > 5) trmode = 0;
            if (hgmode > 7) hgmode = 0;
            if (rbmode > 3) rbmode = 0;
            break;
        }
        InvalidateRect(hWnd, NULL, TRUE);
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
