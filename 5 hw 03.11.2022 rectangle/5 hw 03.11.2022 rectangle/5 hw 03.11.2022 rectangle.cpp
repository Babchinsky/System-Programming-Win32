#include "framework.h"
#include "5 hw 03.11.2022 rectangle.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
HCURSOR hCursor1, hCursor2;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY5HW03112022RECTANGLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY5HW03112022RECTANGLE));

    MSG msg;

    // Main message loop:
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


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
    wcex.hCursor        = LoadCursor(hInstance, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

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


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect;
    GetClientRect(hWnd, &rect);
    unsigned int uTop = rect.top + 10;
    unsigned int uBottom = rect.bottom - 10;
    unsigned int uLeft = rect.left + 10;
    unsigned int uRight = rect.right - 10;

    int x, y;
    x = LOWORD(lParam);
    y = HIWORD(lParam);
    HINSTANCE hInstance;
    switch (message)
    {
    case WM_CREATE:
        hInstance = GetModuleHandle(0);

        hCursor1 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
        hCursor2 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));

        break;
    case WM_MOUSEMOVE:
        wsprintf(szTitle, TEXT("X = %d, Y = %d"), x, y);
        SetWindowText(hWnd, szTitle);

        if (x >= uLeft && x <= uRight &&
            y >= uTop && y <= uBottom)
        {
            SetCursor(hCursor1);
        }
        else SetCursor(hCursor2);
        break;



    case WM_LBUTTONDOWN:

        if (x == uLeft || x == uRight ||
            y == uTop || y == uBottom)
        {
            wsprintf(szTitle, TEXT("Вы нажали на рамку прямоугольника"));
        }
        else if (x > uLeft && x < uRight &&
            y > uTop && y < uBottom)
        {
            wsprintf(szTitle, TEXT("Вы нажали внутри прямоугольника"));
        }
        else wsprintf(szTitle, TEXT("Вы нажали вне прямоугольника"));

        SetWindowText(hWnd, szTitle);
        break;


    case WM_RBUTTONDOWN:
        wsprintf(szTitle, TEXT("Ширина окна = %d, Высота окна = %d"), rect.right, rect.bottom);
        SetWindowText(hWnd, szTitle);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}