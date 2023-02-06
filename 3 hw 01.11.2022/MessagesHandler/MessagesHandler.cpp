// ���� WINDOWS.H �������� �����������, �������, � ��������� 
// ������� ������������ ��� ��������� ���������� ��� Windows. 
#include <windows.h>
#include <tchar.h>
#include <ctime>

#define SIZE 256

//�������� ������� ���������
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("��������� ����������"); /* ��� ������ ���� */

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;

	/* 1. ����������� ������ ����  */

	wcl.cbSize = sizeof (wcl);	// ������ ��������� WNDCLASSEX 
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// ���� ������ �������� ��������� � ������� ������ (DBLCLK)
	wcl.lpfnWndProc = WindowProc;	// ����� ������� ���������
	wcl.cbClsExtra = 0;		// ������������ Windows 
	wcl.cbWndExtra  = 0; 	// ������������ Windows 
	wcl.hInstance = hInst;	// ���������� ������� ����������
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// �������� ����������� ������
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);		// �������� ������������ �������
	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);	//���������� ���� ����� ������			
	wcl.lpszMenuName = NULL;	// ���������� �� �������� ����
	wcl.lpszClassName = szClassWindow;	// ��� ������ ����
	wcl.hIconSm = NULL;	// ���������� ��������� ������ ��� ����� � ������� ����


	/*  2. ����������� ������ ����  */

	if (!RegisterClassEx(&wcl))
		return 0;	// ��� ��������� ����������� - �����

	/*  3. �������� ����  */

	// ��������� ���� �  ���������� hWnd ������������� ���������� ����
	hWnd = CreateWindowEx(
		0,		// ����������� ����� ����
		szClassWindow,	// ��� ������ ����
		TEXT("������  Windows ����������"),	// ��������� ����
		/* ���������, �����, ����������� ������ �������, ��������� ����,
			������ ������������ � ���������� ����  */
		WS_OVERLAPPEDWINDOW,	// ����� ����
		CW_USEDEFAULT,	// �-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// y-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// ������ ����
		CW_USEDEFAULT,	// ������ ����
		NULL,			// ���������� ������������� ����
		NULL,			// ���������� ���� ����
		hInst,		// ������������� ����������, ���������� ����
		NULL);		// ��������� �� ������� ������ ����������


	/* 4. ����������� ���� */

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);	// ����������� ����


	/* 5. ������ ����� ��������� ���������  */

	// ��������� ���������� ��������� �� ������� ���������
	while (GetMessage(&Msg, NULL, 0, 0)) 
	{
		TranslateMessage(&Msg);	// ���������� ���������
		DispatchMessage(&Msg);	// ��������������� ���������
	}
	return Msg.wParam;
}


// ������� ��������� ���������� ������������ �������� � �������� � �������� 
// ���������� ��������� �� ������� ��������� ������� ����������	
int Guess()
{
	srand(time(0));
	TCHAR str[SIZE];

	wsprintf(str, TEXT("��� ����� %d?"), rand() % 99 + 1);

	return MessageBox(
		0,
		str,
		TEXT("��������"),
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
	//	rez = MessageBox(0, // ���������� ������������� ����. ����� ������ hWnd
	//		TEXT("������� ������ ����� ������� ����"),	// ����� ���������
	//		TEXT("WM_LBUTTONDBLCLK"),					// ��������� ����
	//		MB_OKCANCEL /*������ �� � cancel*/ | /*MB_ICONINFORMATION*/ MB_ICONSTOP /*������*/);
	//	
	//	if (rez == IDOK)
	//	{
	//		MessageBox(0, "OK", "��������", MB_OK | MB_ICONASTERISK);
	//	}
	//	else
	//	{
	//		MessageBox(0, "Cancel", "��������", MB_OK | MB_ICONASTERISK);
	//	}
	//	 
	//	break;
	//
	//case WM_LBUTTONDOWN:
	//	MessageBox(
	//		0,
	//		TEXT("������ ����� ������ ����"),
	//		TEXT("WM_LBUTTONDOWN"),
	//		MB_OK | MB_ICONINFORMATION);
	//	break;
	//case WM_LBUTTONUP:
	//	MessageBox(
	//		0,
	//		TEXT("�������� ����� ������ ����"),
	//		TEXT("WM_LBUTTONUP"),
	//		MB_OK | MB_ICONINFORMATION);
	//	break;
	//case WM_RBUTTONDOWN:
	//	MessageBox(
	//		0,
	//		TEXT("������ ������ ������ ����"),
	//		TEXT("WM_RBUTTONDOWN"),
	//		MB_OK | MB_ICONINFORMATION);
	//	break;
	//case WM_MOUSEMOVE: 
	//	wsprintf(str, TEXT("X=%d  Y=%d"), LOWORD(lParam), HIWORD(lParam)); // ������� ���������� ������� ����
	//	SetWindowText(hWnd, str);	// ������ ��������� � ��������� ����
	//	break;
	//case WM_CHAR:
	//	wsprintf(str, TEXT("������ ������� %c"), (TCHAR) wParam);	// ASCII-��� ������� �������
	//	rez = MessageBox(0, str, TEXT("WM_CHAR"), MB_OK | MB_ICONINFORMATION);
	//	if (rez == IDOK)
	//	{
	//		MessageBox(0, "OK", "��������", MB_OK | MB_ICONASTERISK);
	//	}
	//	else
	//	{
	//		MessageBox(0, "Cancel", "��������", MB_OK | MB_ICONASTERISK);
	//	}
	//	break;
	//case WM_DESTROY: // ��������� � ���������� ���������
	//	PostQuitMessage(0);	// ������� ��������� WM_QUIT
	//	break;
	//default:
	//	// ��� ���������, ������� �� �������������� � ������ ������� 
	//	// ������� ������������ ������� Windows �� ��������� �� ���������
	//	return DefWindowProc(hWnd, uMessage, wParam, lParam);
	//}
	//

	///////////////////////////////////////////////////// Task 1

	//TCHAR str[50];
	//int rez = 0;
	//unsigned int number_symbols = 0;
	//unsigned int number_windows = 0;
	//unsigned int average_symbols = 0;
	//TCHAR text[256] = ("���������� ������� ��������");
	//switch (uMessage)
	//{
	//case WM_LBUTTONUP:
	//		rez = MessageBox(
	//			0,
	//			text,
	//			TEXT("���"),
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
	//				TEXT("�������"),
	//				MB_OK | MB_ICONINFORMATION);
	//			number_windows++;
	//			number_symbols += _tcslen(text);
	//			if (rez == IDOK)
	//			{
	//				_tcscpy_s(text, TEXT("�������"));
	//				rez = MessageBox(
	//					0,
	//					text,
	//					TEXT("�����������"),
	//					MB_OK | MB_ICONINFORMATION);
	//				number_windows++;
	//				number_symbols += _tcslen(text);
	//			}
	//			if (rez == IDOK)
	//			{
	//				average_symbols = number_symbols / number_windows;
	//				wsprintf(str, TEXT("C������ ���������� �������� � �����: %d"), average_symbols);
	//				_tcscpy_s(text, "C������ ���������� �������� � �����: ");
	//				rez = MessageBox(
	//					0,
	//					str,
	//					TEXT("�����"),
	//					MB_OK | MB_ICONINFORMATION);
	//			}
	//		}
	//		break;
	//case WM_DESTROY: // ��������� � ���������� ���������
	//	PostQuitMessage(0);	// ������� ��������� WM_QUIT
	//	break;
	//default:
	//	// ��� ���������, ������� �� �������������� � ������ ������� 
	//	// ������� ������������ ������� Windows �� ��������� �� ���������
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
			wsprintf(szText, TEXT("����������! �� ��������! ��������� �� ���� ������� �� %d �������"), iTries);
		}
		else
		{
			wsprintf(szText, TEXT("��������� ������ �� %d �������"), iTries);
		}
		MessageBox(
			0,
			szText,
			TEXT("��������"),
			MB_OK | MB_ICONINFORMATION);
		break;
	case WM_DESTROY: // ��������� � ���������� ���������
		PostQuitMessage(0);	// ������� ��������� WM_QUIT
		break;
	default:
		// ��� ���������, ������� �� �������������� � ������ ������� 
		// ������� ������������ ������� Windows �� ��������� �� ���������
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
}