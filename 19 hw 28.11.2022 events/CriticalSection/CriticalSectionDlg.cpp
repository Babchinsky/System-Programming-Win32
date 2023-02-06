#include "CriticalSectionDlg.h"

CriticalSectionDlg* CriticalSectionDlg::ptr = NULL;

CRITICAL_SECTION cs;

CriticalSectionDlg::CriticalSectionDlg(void)
{
	ptr = this;
}

CriticalSectionDlg::~CriticalSectionDlg(void)
{
	DeleteCriticalSection(&cs);
}

void CriticalSectionDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CriticalSectionDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	InitializeCriticalSection(&cs);
	return TRUE;
}

void MessageAboutError(DWORD dwError)
{
	LPVOID lpMsgBuf = NULL;
	TCHAR szBuf[300];

	BOOL fOK = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	if (lpMsgBuf != NULL)
	{
		wsprintf(szBuf, TEXT("Ошибка %d: %s"), dwError, lpMsgBuf);
		MessageBox(0, szBuf, TEXT("Сообщение об ошибке"), MB_OK | MB_ICONSTOP);
		LocalFree(lpMsgBuf);
	}
}

TCHAR Fname[256] = TEXT("file.txt");
int arrSize = 0;
bool isFirst = true;

DWORD WINAPI Write(LPVOID lp)
{
	const int n = 3;
	srand(time(0));
	EnterCriticalSection(&cs);
	fstream fout((Fname));
	if (!fout.is_open())
	{
		MessageAboutError(GetLastError());
		return 1;
	}
	int B[1024];

	int i = 0;
	while (!fout.eof()) {
		fout >> B[i];
		i++;
	}
	fout.close();


	for (int i = 0; i < n; i++)
	{
		TCHAR buff[256];
		wsprintf(buff, TEXT("%s - %d.txt"), Fname, i);
		ofstream out(((buff)));
		for (int i = 0; i < arrSize; i++)  // 9 поменять на динамический параметр
		{
			out << B[i] << ' ';
		}
		out.close();

	}

	LeaveCriticalSection(&cs);
	MessageBox(0, TEXT("Поток записал информацию в файл"), TEXT("Критическая секция"), MB_OK);
	return 0;
}

DWORD WINAPI Read(LPVOID lp)
{
	if (isFirst == true)
	{
		//Cчитаем количество чисел
		fstream countNum;
		countNum.open(Fname);
		int buf;

		while (countNum >> buf)
			arrSize++;
		countNum.close();
		isFirst = false;
	}

	EnterCriticalSection(&cs);
	for (int i = 0; i < 3; i++)
	{
		TCHAR buff[256];
		wsprintf(buff, TEXT("%s - %d.txt"), Fname, i);
		fstream in(buff);
		if (!in.is_open())
		{
			MessageAboutError(GetLastError());
			return 1;
		}
		int A[1024];

		for (int i = 0; i < arrSize; i++)
		{
			in >> A[i];

		}
		in.close();
		ofstream fout(TEXT("Result.txt"), ios::app);
		for (int i = 0; i < arrSize; i++)
		{
			fout << A[i];

		}
		fout.close();
	}


	LeaveCriticalSection(&cs);
	MessageBox(0, TEXT("Поток прочитал информацию из файла"), TEXT("Критическая секция"), MB_OK);;

	return 0;
}


void CriticalSectionDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_BUTTON1)
	{
		//HANDLE hThread = CreateThread(NULL, 0, Write, 0, 0, NULL);
		//CloseHandle(hThread);
		//hThread = CreateThread(NULL, 0, Read, 0, 0, NULL);
		//CloseHandle(hThread);

		CreateEvent(NULL,
			FALSE, /*автоматический сброс события*/
			TRUE,  /*несигнальное состояние*/
			TEXT("1D9D2503-DCD2-46EA-974D-7A590D5E0D49"));

		EnableWindow(GetDlgItem(hwnd, IDC_BUTTON1), FALSE);

		HANDLE hndl;

		hndl = CreateThread(NULL, 0, Write, 0, 0, NULL);
		CloseHandle(hndl);

		hndl = CreateThread(NULL, 0, Read, 0, 0, NULL);
		CloseHandle(hndl);
	}
}

BOOL CALLBACK CriticalSectionDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}