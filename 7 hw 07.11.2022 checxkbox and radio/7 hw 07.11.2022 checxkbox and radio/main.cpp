#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    // создаём главное окно приложения на основе модального диалога
    return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	LRESULT radio[33];
	LRESULT check[3];
    switch (message)
    {
	case WM_COMMAND:
		if (LOWORD(wp) >= IDC_RADIO1 && LOWORD(wp) <= IDC_RADIO33)
		{
			// Заголовок показывает последний переключатель, который нажали
			TCHAR str[20];
			wsprintf(str, TEXT("Переключатель %d"), LOWORD(wp) - IDC_RADIO1 + 1);
			SetWindowText(hWnd, str);
		}
		else if (LOWORD(wp) == IDOK) // если нажали на кнопку
		{
			TCHAR str[1024] = TEXT("Выбраны следующие переключатели:\n");
			TCHAR buf[100];
			unsigned int uintAllAnswers = 12;
			unsigned int uintMyAnswers = 0;
			unsigned int uintPercentsCorrect;

			// Шагаем по кнопкам
			for (size_t i = IDC_RADIO1, j = 0; i <= IDC_RADIO33; i++)
				radio[j++] = SendDlgItemMessage(hWnd, i, BM_GETCHECK, 0, 0);	// получаем их дескрипторы и записываем в массив


			for (size_t i = IDC_CHECK5, j = 0; i <= IDC_CHECK7; i++)
				check[j++] = SendDlgItemMessage(hWnd, i, BM_GETCHECK, 0, 0);	// получаем их дескрипторы и записываем в массив
			
			if (radio[1] == BST_CHECKED) uintMyAnswers++;
			if (radio[4] == BST_CHECKED) uintMyAnswers++;
			if (radio[7] == BST_CHECKED) uintMyAnswers++;
			if (radio[11] == BST_CHECKED) uintMyAnswers++;
			if (radio[14] == BST_CHECKED) uintMyAnswers++;
			if (radio[16] == BST_CHECKED) uintMyAnswers++;
			if (radio[18] == BST_CHECKED) uintMyAnswers++;
			if (radio[23] == BST_CHECKED) uintMyAnswers++;
			if (radio[26] == BST_CHECKED) uintMyAnswers++;
			if (radio[28] == BST_CHECKED) uintMyAnswers++;
			if (radio[30] == BST_CHECKED) uintMyAnswers++;
			if (check[0] == BST_CHECKED && check[2] == BST_CHECKED) uintMyAnswers++;
			
			uintPercentsCorrect = uintMyAnswers * 1.0 / uintAllAnswers * 100;
			wsprintf(str, TEXT("%d/%d\n%d/100%%"), uintMyAnswers, uintAllAnswers, uintPercentsCorrect);

			MessageBox(hWnd, str, TEXT("Quiz"), MB_OK | MB_ICONINFORMATION);
		}
		else if (LOWORD(wp) == IDCANCEL) EndDialog(hWnd, 0); // закрываем модальный диалог
		
		return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0); // закрываем модальный диалог
        return TRUE;
    }
    return FALSE;
}