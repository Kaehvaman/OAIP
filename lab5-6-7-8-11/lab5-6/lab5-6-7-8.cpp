// lab5-6.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab5-6.h"
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
    LoadStringW(hInstance, IDC_LAB56, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB56));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB56));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB56);
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

//Рисует квадратную сетку с шагом в 50 пикселей от нуля до указанных координат
void drawNet(HDC hdc, int width, int height) {
    for (int i = 0; i <= width; i = i + 50) {
        MoveToEx(hdc, i, 0, NULL);
        LineTo(hdc, i, height);
    }

    for (int i = 0; i <= height; i = i + 50) {
        MoveToEx(hdc, 0, i, NULL);
        LineTo(hdc, width, i);
    }
}

void drawTractor(HDC hdc, int cx, int cy) {
    HBRUSH hBrush;
    HPEN hPen;
    hBrush = CreateSolidBrush(RGB(0, 0, 150));
    SelectObject(hdc, hBrush);
    hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 100));
    SelectObject(hdc, hPen);
    Rectangle(hdc, cx-150, cy-50, cx+150, cy+50);
    MoveToEx(hdc, cx + 150, cy - 50, NULL);
    LineTo(hdc, cx + 150, cy - 150);
    LineTo(hdc, cx + 50, cy - 150);
    hPen = CreatePen(PS_SOLID, 5, RGB(153, 217, 234));
    SelectObject(hdc, hPen);
    LineTo(hdc, cx, cy - 50);
    hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    SelectObject(hdc, hPen);
    hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(20, 20, 20));
    SelectObject(hdc, hBrush);
    Ellipse(hdc, cx-175, cy+25, cx-75, cy+125);
    Ellipse(hdc, cx + 25, cy - 25, cx + 175, cy + 125);
    DeleteObject(hPen);
    DeleteObject(hBrush);
}

void drawHouse(HDC hdc){
    HPEN hPen;
    hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
    SelectObject(hdc, hPen);

    //крыша и стены
    MoveToEx(hdc, 150, 250, NULL);
    LineTo(hdc, 300, 50);
    LineTo(hdc, 450, 250);
    LineTo(hdc, 150, 250);
    LineTo(hdc, 150, 500);
    LineTo(hdc, 450, 500);
    LineTo(hdc, 450, 250);
    //окно
    MoveToEx(hdc, 200, 300, NULL);
    LineTo(hdc, 200, 400);
    LineTo(hdc, 300, 400);
    LineTo(hdc, 300, 300);
    LineTo(hdc, 200, 300);
    MoveToEx(hdc, 250, 300, NULL);
    LineTo(hdc, 250, 400);
    DeleteObject(hPen);
}

void drawSpruce(HDC hdc) {
    HPEN hPen;
    hPen = CreatePen(PS_SOLID, 5, RGB(30, 200, 80));
    SelectObject(hdc, hPen);
    //ёлка
    MoveToEx(hdc, 0, 600, NULL);
    LineTo(hdc, 150, 600);
    LineTo(hdc, 75, 500);
    LineTo(hdc, 0, 600);
    MoveToEx(hdc, 25, 500, NULL);
    LineTo(hdc, 125, 500);
    LineTo(hdc, 75, 400);
    LineTo(hdc, 25, 500);
    MoveToEx(hdc, 50, 400, NULL);
    LineTo(hdc, 100, 400);
    LineTo(hdc, 75, 300);
    LineTo(hdc, 50, 400);
    DeleteObject(hPen);
}

void drawCar(HDC hdc) {
    HPEN hPen;
    HBRUSH hBrush;
    //корпус авто
    hBrush = CreateSolidBrush(RGB(100, 100, 100));
    SelectObject(hdc, hBrush);
    hPen = CreatePen(PS_SOLID, 5, RGB(50, 50, 50));
    SelectObject(hdc, hPen);
    Rectangle(hdc, 550, 350, 850, 450);
    //крыша авто
    hPen = CreatePen(PS_SOLID, 5, RGB(0, 162, 232));
    SelectObject(hdc, hPen);
    MoveToEx(hdc, 550, 350, NULL);
    LineTo(hdc, 650, 250);
    LineTo(hdc, 800, 250);
    LineTo(hdc, 850, 350);
    //колёса
    hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    SelectObject(hdc, hPen);
    hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(20, 20, 20));
    SelectObject(hdc, hBrush);
    Ellipse(hdc, 560, 410, 640, 490);
    Ellipse(hdc, 560 + 200, 410, 640 + 200, 490);
    DeleteObject(hPen);
    DeleteObject(hBrush);
}

void drawTree(HDC hdc) {
    HPEN hPen;
    HBRUSH hBrush;
    //ствол дерева
    hPen = CreatePen(PS_SOLID, 25, RGB(114, 78, 54));
    SelectObject(hdc, hPen);
    MoveToEx(hdc, 950, 500, NULL);
    LineTo(hdc, 950, 200);
    //листва дерева
    hPen = CreatePen(PS_SOLID, 5, RGB(30, 150, 80));
    SelectObject(hdc, hPen);
    hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(30, 210, 80));
    SelectObject(hdc, hBrush);
    Ellipse(hdc, 850, 50, 1050, 350);
    DeleteObject(hPen);
    DeleteObject(hBrush);
}

//Рисует логотип Шевроле
void drawLogo(HDC hdc, int cx, int cy) {
    POINT pt[12];
    pt[0].x = cx + 50; pt[0].y = cy + 50;
    pt[1].x = cx - 50; pt[1].y = cy + 50;
    pt[2].x = cx - 50; pt[2].y = cy + 25;
    pt[3].x = cx - 150; pt[3].y = cy + 25;
    pt[4].x = cx - 125; pt[4].y = cy - 25;
    pt[5].x = cx - 50; pt[5].y = cy - 25;
    pt[6].x = cx - 50; pt[6].y = cy - 50;
    pt[7].x = cx + 50; pt[7].y = cy - 50;
    pt[8].x = cx + 50; pt[8].y = cy - 25;
    pt[9].x = cx + 150; pt[9].y = cy - 25;
    pt[10].x = cx + 125; pt[10].y = cy + 25;
    pt[11].x = cx + 50; pt[11].y = cy + 25;

    HPEN hPen;
    HBRUSH hBrush;
    hPen = CreatePen(PS_SOLID, 10, RGB(180, 180, 180));
    hBrush = CreateHatchBrush(HS_CROSS, RGB(255, 215, 104));
    SelectObject(hdc, hPen);
    SelectObject(hdc, hBrush);

    Polygon(hdc, pt, 12);

    DeleteObject(hPen);
    DeleteObject(hBrush);
}

void lab5(HDC hdc) {
    drawHouse(hdc);
    drawSpruce(hdc);
    drawCar(hdc);
    drawTree(hdc);
    drawTractor(hdc, 1200, 450);
}

void lab6(HDC hdc) {
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    SelectObject(hdc, hPen);
    int x1 = 100;
    do {
        MoveToEx(hdc, 400, 300, NULL);
        LineTo(hdc, x1, 100);
        x1 += 25;
    } while (x1 <= 700);

    int x2 = 600, y2 = 400;
    do {
        MoveToEx(hdc, 800, 400, NULL);
        LineTo(hdc, x2, y2);
        x2 += 10;
        y2 -= 16;
    } while (x2 < 800);
    do {
        MoveToEx(hdc, 800, 400, NULL);
        LineTo(hdc, x2, y2);
        x2 += 10;
        y2 += 16;
    } while (x2 <= 1000);

    int x3 = 1100;
    do {
        MoveToEx(hdc, x3, 50, NULL);
        LineTo(hdc, x3, 300);
        x3 += 5;
    } while (x3 <= 1400);

    int x4 = 100, y4 = 350;
    int x5 = 400, y5 = 350;
    int i = 0;
    do {
        MoveToEx(hdc, x4, y4, NULL);
        LineTo(hdc, x5, y5);
        y4 += 10;
        x5 -= 10;
        i++;
    } while (i <= 30);

    int x6 = 600, y6 = 600;
    int dy = 10;
    i = 0;

    do {
        MoveToEx(hdc, x6, y6 - dy, NULL);
        LineTo(hdc, x6, y6 + dy);
        x6 += 10;
        dy += 10;
        i++;
    } while (i < 15);
}

void lab8(HDC hdc) {
    /*drawLogo(hdc, 155, 55);
    drawLogo(hdc, 155+300, 55);
    drawLogo(hdc, 155, 55+300);
    drawLogo(hdc, 155+300, 55+300);
    drawLogo(hdc, 155 + 150, 55 + 150);*/

    int x1 = 0, y1 = 0;
    int i = 0;
    do {
        drawLogo(hdc, 155 + x1, 55 + y1);
        x1 += 125;
        y1 += 125;
        i++;
    } while (i < 5);
}

int imageNum = 1;
bool netToggle = true;

//Рисует картинки по нажатию цифры на клавиатуре
void drawImageSequence1(HDC hdc) {
    switch (imageNum)
    {
    case 0:
        lab5(hdc);
        break;
    case 1:
        drawSpruce(hdc);
        break;
    case 2:
        drawHouse(hdc);
        break;
    case 3:
        drawLogo(hdc, 500, 300);
        break;
    case 4:
        drawCar(hdc);
        break;
    case 5:
        drawTree(hdc);
        break;
    case 6:
        drawTractor(hdc, 1200, 450);
        break;
    }
}

void draw5logos(HDC hdc, RECT rect) {
    drawLogo(hdc, rect.right - 200, rect.bottom - 100);
    drawLogo(hdc, rect.right - 200, rect.top + 100);
    drawLogo(hdc, rect.left + 200, rect.bottom - 100);
    drawLogo(hdc, rect.right / 2, rect.bottom / 2);
}

void drawImage1(HDC hdc, int cx, int cy, COLORREF color) {
    HPEN hPen = CreatePen(PS_SOLID, 4, color);
    SelectObject(hdc, hPen);

    POINT p[4] = {
        cx,        	cy - 20,
        cx + 20,	cy + 20,
        cx - 20,    cy + 20,
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
    HPEN hPen = CreatePen(PS_SOLID, 4, color);
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

void drawImage4(HDC hdc, int cx, int cy, COLORREF color) {
    HPEN hPen = CreatePen(PS_SOLID, 4, color);
    SelectObject(hdc, hPen);

    POINT p[6] = {
        cx - 20,    cy + 20,
        cx - 20,	cy - 20,
        cx + 20,    cy - 20,
        cx,         cy - 10,
        cx + 20,    cy,
        cx - 20,    cy
    };
    Polyline(hdc, p, 6);

    DeleteObject(hPen);
}

void drawImage5(HDC hdc, int cx, int cy, COLORREF color) {
    HPEN hPen = CreatePen(PS_SOLID, 4, color);
    SelectObject(hdc, hPen);

    POINT p[6] = {
        cx,         cy ,
        cx + 20,	cy - 20,
        cx + 20,    cy + 20,
        cx - 20,    cy + 20,
        cx - 20,    cy - 20,
        cx,         cy
    };
    Polyline(hdc, p, 6);

    DeleteObject(hPen);
}

void drawImageNet(HDC hdc, int cx, int cy, int width, int height, int step, void (*image)(HDC hdc, int cx, int cy, COLORREF color)) {
    int r, g, b, fb;
    r = 255;
    g = 40;
    b = 0;
    int dr, dg, db;
    dr = r / width;
    dg = (255 - g) / width;
    db = (255 - b) / height;
    for (int i = cx; i <= width * step; i += step) {
        fb = b;
        for (int j = cy; j <= height * step; j += step) {
            image(hdc, i, j, RGB(r, g, fb));
            fb += db;
        }
        //r -= dr;
        g += dg;
    }
}

enum Modes {
    image1,
    image2,
    image3,
    image4,
    image5
} mode;

void drawImageSequence2(HDC hdc, int cx, int cy, int width, int height, int step) {
    switch (mode)
    {
    case image1:
        drawImageNet(hdc, cx, cy, width, height, step, drawImage1);
        break;
    case image2:
        drawImageNet(hdc, cx, cy, width, height, step, drawImage2);
        break;
    case image3:
        drawImageNet(hdc, cx, cy, width, height, step, drawImage3);
        break;
    case image4:
        drawImageNet(hdc, cx, cy, width, height, step, drawImage4);
        break;
    case image5:
        drawImageNet(hdc, cx, cy, width, height, step, drawImage5);
        break;
    }
}

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

            if (netToggle) drawNet(hdc, rect.right, rect.bottom); //drawNet(hdc, 1400, 650);
            
            drawImageSequence1(hdc);

            //lab5(hdc);
            
            //lab6(hdc);
            
            //lab8(hdc);

            //draw5logos(hdc, rect);

            //drawImageNet(hdc, 50, 50, 8, 8, 100, drawImage4);

            //drawImageSequence2(hdc, 50, 50, 12, 8, 100);

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
            case 0x30:
                imageNum = 0;
                break;
            case 0x31:
                imageNum = 1;
                mode = image1;
                break;
            case 0x32:
                imageNum = 2;
                mode = image2;
                break;
            case 0x33:
                imageNum = 3;
                mode = image3;
                break;
            case 0x34:
                imageNum = 4;
                mode = image4;
                break;
            case 0x35:
                imageNum = 5;
                mode = image5;
                break;
            case 0x36:
                imageNum = 6;
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
