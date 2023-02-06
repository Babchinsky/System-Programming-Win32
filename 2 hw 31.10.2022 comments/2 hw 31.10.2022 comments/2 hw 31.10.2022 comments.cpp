// 2 hw 31.10.2022 comments.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "2 hw 31.10.2022 comments.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                   //����� ������� ����� ������ ����������!	             // current instance
WCHAR szTitle[MAX_LOADSTRING];     // ����� ��������        // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING]; // ����� ����          // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);   //������������ ����� ����!
BOOL                InitInstance(HINSTANCE, int);           //� ����� ���� ����!
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);    //���������� ��� ������� ��������� ������ ����
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);      

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         //hInstanse ������ ���������� � ������. hInstance �������� ������������� ����������.
                     _In_opt_ HINSTANCE hPrevInstance,  //hInstanse ���������� �������� ���� ������ ����������
    // ������������� ���������� ����� ����������, ���� � ������� �������� ��������� ����� ������ ����������.
    //  ���� �������� ������ ���� �����, �� hPrevInstance ����� �������� NULL. � ����� Win32 �������� ����� �������������� ������ NULL.
		                                                //�� ������ ������ ����������
                     _In_ LPWSTR    lpCmdLine,  //��������� ������
                                                //��������� �� ������ ����������.
                     _In_ int       nCmdShow)   //��������� ������ ����(����������,��������)
                                                //���������� ������ ����������� ����(���������������� SW_MINIMIZE, ���������� SW_SHOW � �.�.).
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY2HW31102022COMMENTS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance); //� ��� �� �������������� ����� ������ ����

    // Perform application initialization:
    if (!InitInstance (hInstance //������ ����������
                    , nCmdShow   //��������� ������ ���� - � ������� ��� ���� ��� �������!
    ))                           //������� ���� ����������
    {                            //���� �� ���������-����� �� ���������
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2HW31102022COMMENTS)); // ���������� ������� �������������

    MSG msg;    // ��������� ��� ������ � �����������

    //����������� ���� ��������� ��������� Windows
    while (GetMessage(&msg, nullptr, 0, 0)) //�������� ������ ��������� �� ����� ��������� � msg
    {           //�������� ��������! �� ������ ����� ��������� Windows ��������
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg); 	//����������� ��������� ������
            DispatchMessage(&msg);      //��������� ��� ������ ����
        }
    }

    return (int) msg.wParam;
}



// ������������ ����� ����. Registers the window class.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    //����� ������ ����
    WNDCLASSEXW wcex;

    //��������� ��� ����������� � ����� ����
    wcex.cbSize = sizeof(WNDCLASSEX); // ������ ������ ����

    wcex.style          = CS_HREDRAW | CS_VREDRAW; //����� ����
    wcex.lpfnWndProc    = WndProc; //����� ������� ��������� ��������� ������ ����
    wcex.cbClsExtra     = 0; //�������������� ����� ����
    wcex.cbWndExtra     = 0; //����� ������� ��������� ������ ����,
                             // �.�. NULL, �� ����������� ����������� ����
    wcex.hInstance      = hInstance; //����� ���������
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2HW31102022COMMENTS)); // �������� ������ ������(����������� ��� �� ��������)
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW); // �������� ������ �������(����������� ��� �� ��������)
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); // ���� ������� ���� ����
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY2HW31102022COMMENTS); //	�������� ���� ������ ����
    wcex.lpszClassName  = szWindowClass; //	��� ������ ������ ����
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); //����� ��������� ������(��������� ����)

    return RegisterClassExW(&wcex); //������������ ����� ������ ���� - API
}




// ��������� ���������� ���������� � ������� ������� ����

//� ���� ������� �� ��������� ���������� ���������� � ���������� ���������� �
//������� � ���������� ������� ���� ���������.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��������� ���������� ���������� � ����� ���������� ����������

   //����       //������� ����! - API
   HWND hWnd = CreateWindowW(szWindowClass, //����� ����                                  HWND hwnd; // ���������� ����          
       szTitle, //���������� � ������ ������ ���� - Title Window
       WS_OVERLAPPEDWINDOW, //����� ����
       CW_USEDEFAULT, //���������� � ���������� ������ ���� ���� (���������� ����������)
       0,             //���������� Y ���������� ������ ���� ���� (���������� ����������)
       CW_USEDEFAULT, //���������� X ������� ������� ���� �� ������ ��������(���������)
       0,             //���������� Y ������� ������� ���� �� ������ ��������(���������)
       nullptr,       //hWnd ������������� ����
       nullptr,       //Handle Menu
       hInstance,     // ����� ��������� - ����������� ���� �  ���������
       nullptr);

   if (!hWnd) //���� ���� �� �������
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow); //�������� ����
   UpdateWindow(hWnd);         //������� ��������� ������� WinMain() � ����������� ����!

   return TRUE;
}

//HWND hwnd; // ���������� ����

//UINT message; // ����� ���������;

//WPARAM wParam; // �������������� ���������� � ���������

//LPARAM lParam; // �������������� ���������� � ���������

//DWORD time; // �����, � ������ ����������

// ��������� � �������

//POINT pt; // ��������� ������� ����, � ������ ����������



//  ������������ ��������� ��� �������� ����.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:    // ������������ ���� ����������
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:     // ������ about 
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About); // �������� ���������� ����
                break;
            case IDM_EXIT:  // �����
                DestroyWindow(hWnd);    // ���������
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:      // ������ ������� �����
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);    // �������� ��������
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);        // ����������� ��������
        }
        break;
    case WM_DESTROY: // ��������� ��������� � ������ � ���������
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���������� ��������� ��� ���� about.
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
