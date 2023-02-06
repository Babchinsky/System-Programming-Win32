// Файл WINDOWS.H содержит определения, макросы, и структуры 
// которые используются при написании приложений под Windows. 
#include <windows.h>
#include <tchar.h>
#include <ctime>

#define SIZE 256

//прототип оконной процедуры
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение"); /* Имя класса окна */

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;

	/* 1. Определение класса окна  */

	wcl.cbSize = sizeof (wcl);	// размер структуры WNDCLASSEX 
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// окно сможет получать сообщения о двойном щелчке (DBLCLK)
	wcl.lpfnWndProc = WindowProc;	// адрес оконной процедуры
	wcl.cbClsExtra = 0;		// используется Windows 
	wcl.cbWndExtra  = 0; 	// используется Windows 
	wcl.hInstance = hInst;	// дескриптор данного приложения
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// загрузка стандартной иконки
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);		// загрузка стандартного курсора
	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);	//заполнение окна белым цветом			
	wcl.lpszMenuName = NULL;	// приложение не содержит меню
	wcl.lpszClassName = szClassWindow;	// имя класса окна
	wcl.hIconSm = NULL;	// отсутствие маленькой иконки для связи с классом окна


	/*  2. Регистрация класса окна  */

	if (!RegisterClassEx(&wcl))
		return 0;	// при неудачной регистрации - выход

	/*  3. Создание окна  */

	// создается окно и  переменной hWnd присваивается дескриптор окна
	hWnd = CreateWindowEx(
		0,		// расширенный стиль окна
		szClassWindow,	// имя класса окна
		TEXT("Каркас  Windows приложения"),	// заголовок окна
		/* Заголовок, рамка, позволяющая менять размеры, системное меню,
			кнопки развёртывания и свёртывания окна  */
		WS_OVERLAPPEDWINDOW,	// стиль окна
		CW_USEDEFAULT,	// х-координата левого верхнего угла окна
		CW_USEDEFAULT,	// y-координата левого верхнего угла окна
		CW_USEDEFAULT,	// ширина окна
		CW_USEDEFAULT,	// высота окна
		NULL,			// дескриптор родительского окна
		NULL,			// дескриптор меню окна
		hInst,		// идентификатор приложения, создавшего окно
		NULL);		// указатель на область данных приложения


	/* 4. Отображение окна */

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);	// перерисовка окна


	/* 5. Запуск цикла обработки сообщений  */

	// получение очередного сообщения из очереди сообщений
	while (GetMessage(&Msg, NULL, 0, 0)) 
	{
		TranslateMessage(&Msg);	// трансляция сообщения
		DispatchMessage(&Msg);	// диспетчеризация сообщений
	}
	return Msg.wParam;
}


// Оконная процедура вызывается операционной системой и получает в качестве 
// параметров сообщения из очереди сообщений данного приложения	
int Guess()
{
	srand(time(0));
	TCHAR str[SIZE];

	wsprintf(str, TEXT("Это число %d?"), rand() % 99 + 1);

	return MessageBox(
		0,
		str,
		TEXT("Угадайка"),
		MB_YESNO);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	//TCHAR str[50];
	//
	//switch(uMessage)
	//{
	//	int rez;
	//case WM_LBUTTONDBLCLK:
	//	rez = MessageBox(0, // дескриптор родительского окна. Можно писать hWnd
	//		TEXT("Двойной щелчок левой кнопкой мыши"),	// Текст сообщений
	//		TEXT("WM_LBUTTONDBLCLK"),					// Заголовок окна
	//		MB_OKCANCEL /*кнопки ок и cancel*/ | /*MB_ICONINFORMATION*/ MB_ICONSTOP /*иконка*/);
	//	
	//	if (rez == IDOK)
	//	{
	//		MessageBox(0, "OK", "Заголовк", MB_OK | MB_ICONASTERISK);
	//	}
	//	else
	//	{
	//		MessageBox(0, "Cancel", "Заголовк", MB_OK | MB_ICONASTERISK);
	//	}
	//	 
	//	break;
	//
	//case WM_LBUTTONDOWN:
	//	MessageBox(
	//		0,
	//		TEXT("Нажата левая кнопка мыши"),
	//		TEXT("WM_LBUTTONDOWN"),
	//		MB_OK | MB_ICONINFORMATION);
	//	break;
	//case WM_LBUTTONUP:
	//	MessageBox(
	//		0,
	//		TEXT("Отпущена левая кнопка мыши"),
	//		TEXT("WM_LBUTTONUP"),
	//		MB_OK | MB_ICONINFORMATION);
	//	break;
	//case WM_RBUTTONDOWN:
	//	MessageBox(
	//		0,
	//		TEXT("Нажата правая кнопка мыши"),
	//		TEXT("WM_RBUTTONDOWN"),
	//		MB_OK | MB_ICONINFORMATION);
	//	break;
	//case WM_MOUSEMOVE: 
	//	wsprintf(str, TEXT("X=%d  Y=%d"), LOWORD(lParam), HIWORD(lParam)); // текущие координаты курсора мыши
	//	SetWindowText(hWnd, str);	// строка выводится в заголовок окна
	//	break;
	//case WM_CHAR:
	//	wsprintf(str, TEXT("Нажата клавиша %c"), (TCHAR) wParam);	// ASCII-код нажатой клавиши
	//	rez = MessageBox(0, str, TEXT("WM_CHAR"), MB_OK | MB_ICONINFORMATION);
	//	if (rez == IDOK)
	//	{
	//		MessageBox(0, "OK", "Заголовк", MB_OK | MB_ICONASTERISK);
	//	}
	//	else
	//	{
	//		MessageBox(0, "Cancel", "Заголовк", MB_OK | MB_ICONASTERISK);
	//	}
	//	break;
	//case WM_DESTROY: // сообщение о завершении программы
	//	PostQuitMessage(0);	// посылка сообщения WM_QUIT
	//	break;
	//default:
	//	// все сообщения, которые не обрабатываются в данной оконной 
	//	// функции направляются обратно Windows на обработку по умолчанию
	//	return DefWindowProc(hWnd, uMessage, wParam, lParam);
	//}
	//

	///////////////////////////////////////////////////// Task 1

	//TCHAR str[50];
	//int rez = 0;
	//unsigned int number_symbols = 0;
	//unsigned int number_windows = 0;
	//unsigned int average_symbols = 0;
	//TCHAR text[256] = ("Бабчинский Алексей Павлович");
	//switch (uMessage)
	//{
	//case WM_LBUTTONUP:
	//		rez = MessageBox(
	//			0,
	//			text,
	//			TEXT("ФИО"),
	//			MB_OK | MB_ICONINFORMATION);
	//		number_windows++;
	//		number_symbols += _tcslen(text);
	//		
	//		if (rez == IDOK)
	//		{
	//			_tcscpy_s(text, TEXT("19"));
	//			rez = MessageBox(
	//				0,
	//				text,
	//				TEXT("Возраст"),
	//				MB_OK | MB_ICONINFORMATION);
	//			number_windows++;
	//			number_symbols += _tcslen(text);
	//			if (rez == IDOK)
	//			{
	//				_tcscpy_s(text, TEXT("Украина"));
	//				rez = MessageBox(
	//					0,
	//					text,
	//					TEXT("Гражданство"),
	//					MB_OK | MB_ICONINFORMATION);
	//				number_windows++;
	//				number_symbols += _tcslen(text);
	//			}
	//			if (rez == IDOK)
	//			{
	//				average_symbols = number_symbols / number_windows;
	//				wsprintf(str, TEXT("Cреднее количество символов в окнах: %d"), average_symbols);
	//				_tcscpy_s(text, "Cреднее количество символов в окнах: ");
	//				rez = MessageBox(
	//					0,
	//					str,
	//					TEXT("Ответ"),
	//					MB_OK | MB_ICONINFORMATION);
	//			}
	//		}
	//		break;
	//case WM_DESTROY: // сообщение о завершении программы
	//	PostQuitMessage(0);	// посылка сообщения WM_QUIT
	//	break;
	//default:
	//	// все сообщения, которые не обрабатываются в данной оконной 
	//	// функции направляются обратно Windows на обработку по умолчанию
	//	return DefWindowProc(hWnd, uMessage, wParam, lParam);
	//}

	///////////////////////////////////////////////////// Task 2
	
	TCHAR szText[SIZE];
	int iTries;
	int iMaxTries = 10;
	bool bIsWin;
	switch (uMessage)
	{
	case WM_LBUTTONUP:
		iTries = 1;
		bIsWin = false;
		for (; Guess() != IDYES; iTries++)
		{
			if (iTries == iMaxTries)
			{
				bIsWin = true;
				break;
			}
		}
		if (bIsWin)
		{
			wsprintf(szText, TEXT("Поздравляю! Вы победили! Компьютер не смог угадать за %d попыток"), iTries);
		}
		else
		{
			wsprintf(szText, TEXT("Компьютер угадал за %d попыток"), iTries);
		}
		MessageBox(
			0,
			szText,
			TEXT("Угадайка"),
			MB_OK | MB_ICONINFORMATION);
		break;
	case WM_DESTROY: // сообщение о завершении программы
		PostQuitMessage(0);	// посылка сообщения WM_QUIT
		break;
	default:
		// все сообщения, которые не обрабатываются в данной оконной 
		// функции направляются обратно Windows на обработку по умолчанию
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
}