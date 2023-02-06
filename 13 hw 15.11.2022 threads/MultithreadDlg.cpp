#include "MultithreadDlg.h"

HWND hRadio[QUESTION_NUMBER][ANSWER_NUMBER];
bool isFirstPressed;
bool isSecondPressed;
bool isThirdPressed;

CMultithreadDlg* CMultithreadDlg::ptr = NULL;

CMultithreadDlg::CMultithreadDlg(void)
{
	ptr = this;
}

CMultithreadDlg::~CMultithreadDlg(void)
{

}

void CMultithreadDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI Thread_Timer(LPVOID lp)
{
	HWND hStaticTime = HWND(lp);

	short minutes = 3;
	short seconds = 0;
	TCHAR textMyTime[255];
	TCHAR textSeconds[255];

	while (true)
	{
		seconds--;

		if (minutes == 0 && seconds == -1) break;

		if (seconds == -1) 
		{
			minutes--;
			seconds = 59;
		}

		// Записываем в текст число минут
		if (minutes < 11) _stprintf_s(textMyTime, TEXT("0%d"), minutes);
		else _stprintf_s(textMyTime, TEXT("%d"), minutes);

		
		if (seconds < 11) wcscat_s(textMyTime, 255, TEXT(":0"));
		else wcscat_s(textMyTime, 255, TEXT(":"));
		

		_stprintf_s(textSeconds, TEXT("%d"), seconds);
		wcscat_s(textMyTime, 255, textSeconds);

		SetWindowText(hStaticTime, textMyTime);
		Sleep(980);
	}

	SetWindowText(hStaticTime, TEXT("END"));
	return 0;
}

BOOL CMultithreadDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	isFirstPressed = false;
	isSecondPressed = false;
	isThirdPressed = false;

	// получаем дескрипторы
	hStaticTime = GetDlgItem(hwnd, IDC_STATIC_TIME);
	hProgress = GetDlgItem(hwnd, IDC_PROGRESS);

	SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 3));
	SendMessage(hProgress, PBM_SETSTEP, 1, 0);
	SendMessage(hProgress, PBM_SETPOS, 0, 0);


	for (size_t i = 0, x = IDC_RADIO1A; i < QUESTION_NUMBER; i++)
	{
		for (size_t j = 0; j < ANSWER_NUMBER; j++)
		{
			hRadio[i][j] = GetDlgItem(hwnd, x++);
		}
	}

	hndlTime = CreateThread(NULL, 0, Thread_Timer, hStaticTime, 0, NULL);
	return TRUE;
}

void CMultithreadDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	// Деактивация кнопок после первого нажатия
	for (size_t i = IDC_RADIO1A; i <= IDC_RADIO3D; i += 4)
	{
		if (IsDlgButtonChecked(hwnd, i) || IsDlgButtonChecked(hwnd, i + 1) || IsDlgButtonChecked(hwnd, i + 2) || IsDlgButtonChecked(hwnd, i + 3))
		{
			EnableWindow(GetDlgItem(hwnd, i), 0);
			EnableWindow(GetDlgItem(hwnd, i + 1), 0);
			EnableWindow(GetDlgItem(hwnd, i + 2), 0);
			EnableWindow(GetDlgItem(hwnd, i + 3), 0);
		}
	}

	if (IsDlgButtonChecked(hwnd, IDC_RADIO1B) && !isFirstPressed)
	{
		SendMessage(hProgress, PBM_STEPIT, 0, 0);
		isFirstPressed = true;
	}

	if (IsDlgButtonChecked(hwnd, IDC_RADIO2C) && !isSecondPressed)
	{
		SendMessage(hProgress, PBM_STEPIT, 0, 0);
		isSecondPressed = true;
	}

	if (IsDlgButtonChecked(hwnd, IDC_RADIO3D) && !isThirdPressed)
	{
		SendMessage(hProgress, PBM_STEPIT, 0, 0);
		isThirdPressed = true;
	}

	if (id == IDOK) 
	{ 
		SuspendThread(hndlTime);
	}
}

BOOL CALLBACK CMultithreadDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}
	return FALSE;
}