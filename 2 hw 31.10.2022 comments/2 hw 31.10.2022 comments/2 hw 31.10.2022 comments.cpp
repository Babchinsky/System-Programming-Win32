// 2 hw 31.10.2022 comments.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "2 hw 31.10.2022 comments.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                   //Будем хранить хэндл нашего приложения!	             // current instance
WCHAR szTitle[MAX_LOADSTRING];     // Текст заголока        // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING]; // Класс окна          // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);   //Регистрируем класс окна!
BOOL                InitInstance(HINSTANCE, int);           //А здесь само окно!
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);    //Вызывается при приходе сообщений нашему окну
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);      

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         //hInstanse нашего приложения в памяти. hInstance содержит идентификатор приложения.
                     _In_opt_ HINSTANCE hPrevInstance,  //hInstanse приложения стоящего выше нашего приложения
    // идентификатор предыдущей копии приложения, если в системе работает несколько копий одного приложения.
    //  Если запущена только одна копия, то hPrevInstance имеет значение NULL. В среде Win32 значение этого идентификатора всегда NULL.
		                                                //по дереву связей приложений
                     _In_ LPWSTR    lpCmdLine,  //Командная строка
                                                //указывает на строку параметров.
                     _In_ int       nCmdShow)   //Состояние нашего окна(Развернуто,Свернуто)
                                                //определяет способ отображения окна(минимизированное SW_MINIMIZE, нормальное SW_SHOW и т.д.).
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY2HW31102022COMMENTS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance); //В ней мы зарегистрируем класс нашего окна

    // Perform application initialization:
    if (!InitInstance (hInstance //Нашего приложения
                    , nCmdShow   //Состояние нашего окна - в котором нам надо его создать!
    ))                           //Создаем окно приложения
    {                            //если не создалось-выход из программы
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2HW31102022COMMENTS)); // дескриптор таблицы акселераторов

    MSG msg;    // структура для работы с сообщениями

    //Стандартный цикл обработки сообщений Windows
    while (GetMessage(&msg, nullptr, 0, 0)) //Получаем первое сообщение из стэка сообщений в msg
    {           //Обратите внимание! Из общего стэка сообщений Windows получаем
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg); 	//Транслируем сообщение дальше
            DispatchMessage(&msg);      //Сообщение для нашего окна
        }
    }

    return (int) msg.wParam;
}



// Регистрирует класс окна. Registers the window class.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    //Класс нашего окна
    WNDCLASSEXW wcex;

    //Заполняем его информацией о нашем окне
    wcex.cbSize = sizeof(WNDCLASSEX); // Размер класса окна

    wcex.style          = CS_HREDRAW | CS_VREDRAW; //Стиль окна
    wcex.lpfnWndProc    = WndProc; //Адрес функции обработки сообщений нашего окна
    wcex.cbClsExtra     = 0; //Дополнительный класс окна
    wcex.cbWndExtra     = 0; //Адрес функции рисования нашего окна,
                             // т.к. NULL, то стандартная перерисовка окна
    wcex.hInstance      = hInstance; //нашей программы
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2HW31102022COMMENTS)); // загрузка хендла иконки(стандартная или из ресурсов)
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW); // загрузка хендла курсора(стандартная или из ресурсов)
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); // Цвет заднего фона окна
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY2HW31102022COMMENTS); //	Название меню нашего окна
    wcex.lpszClassName  = szWindowClass; //	Имя класса нашего окна
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); //хендл маленькой иконки(свернутое окно)

    return RegisterClassExW(&wcex); //Регистрируем класс нашего окна - API
}




// Сохраняет дескриптор экземпляра и создает главное окно

//В этой функции мы сохраняем дескриптор экземпляра в глобальной переменной и
//создать и отобразить главное окно программы.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохраните дескриптор экземпляра в нашей глобальной переменной

   //окна       //Создаем окно! - API
   HWND hWnd = CreateWindowW(szWindowClass, //Класс окна                                  HWND hwnd; // дескриптор окна          
       szTitle, //Информация в верней строке окна - Title Window
       WS_OVERLAPPEDWINDOW, //Стиль окна
       CW_USEDEFAULT, //Координата Х верхневого левого угла окна (Глобальные координаты)
       0,             //Координата Y верхневого левого угла окна (Глобальные координаты)
       CW_USEDEFAULT, //Координата X правого нижнего угла от левого верхнего(локальные)
       0,             //Координата Y правого нижнего угла от левого верхнего(локальные)
       nullptr,       //hWnd Родительского окна
       nullptr,       //Handle Menu
       hInstance,     // нашей программы - привязываем окно к  программе
       nullptr);

   if (!hWnd) //Если окно не создано
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow); //Показать окно
   UpdateWindow(hWnd);         //Послать сообщение функции WinMain() о перерисовке окна!

   return TRUE;
}

//HWND hwnd; // дескриптор окна

//UINT message; // номер сообщения;

//WPARAM wParam; // дополнительная информация о сообщении

//LPARAM lParam; // дополнительная информация о сообщении

//DWORD time; // время, в момент постановки

// сообщения в очередь

//POINT pt; // положение курсора мыши, в момент постановки



//  Обрабатывает сообщения для главного окна.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:    // обрабатывает меню приложения
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:     // кнопка about 
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About); // вызывает диалоговое окно
                break;
            case IDM_EXIT:  // Выход
                DestroyWindow(hWnd);    // закрываем
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:      // Рисует главное окноы
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);    // Начинает рисовать
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);        // Заканчивает рисовать
        }
        break;
    case WM_DESTROY: // публикует сообщение о выходе и вернуться
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для поля about.
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
