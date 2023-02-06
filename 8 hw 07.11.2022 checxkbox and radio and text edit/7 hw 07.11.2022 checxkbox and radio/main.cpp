#include <windows.h>
#include <tchar.h>
#include "resource.h"

#define SIZE 20

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    // создаём главное окно приложения на основе модального диалога
    return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	LRESULT elems[35]; // radio, check, edit text
	HWND hEight, hNine;

    switch (message)
    {
	case WM_COMMAND:
		if (LOWORD(wp) >= IDC_RADIO1A && LOWORD(wp) <= IDC_RADIO13C)
		{
			// Заголовок показывает последний переключатель, который нажали
			TCHAR str[SIZE];
			wsprintf(str, TEXT("Переключатель %d"), LOWORD(wp) - IDC_RADIO1A + 1);
			SetWindowText(hWnd, str);
		}
		else if (LOWORD(wp) == IDOK) // если нажали на кнопку
		{
			TCHAR str[1024] = TEXT("Выбраны следующие переключатели:\n");
			TCHAR questionEightText[SIZE], questionNineText[SIZE];

			unsigned int uintAllAnswers = 13;
			unsigned int uintMyAnswers = 0;
			float uintPercentsCorrect = 0;

			// Шагаем по кнопкам
			for (size_t i = IDC_RADIO1A, j = 0; i <= IDC_RADIO13C; i++)
				elems[j++] = SendDlgItemMessage(hWnd, i, BM_GETCHECK, 0, 0);	// получаем их дескрипторы и записываем в массив

			hEight = GetDlgItem(hWnd, IDC_EDIT6);
			hNine = GetDlgItem(hWnd, IDC_EDIT7);

			GetWindowText(hEight, questionEightText, SIZE);
			GetWindowText(hNine, questionNineText, SIZE);
			
			if (elems[1] == BST_CHECKED) uintMyAnswers++; // 1B
			if (elems[4] == BST_CHECKED) uintMyAnswers++; // 2B
			if (elems[7] == BST_CHECKED) uintMyAnswers++; // 3B
			if (elems[9] == BST_CHECKED && elems[11] == BST_CHECKED) uintMyAnswers++;// 4AC
			if (elems[14] == BST_CHECKED) uintMyAnswers++;// 5C
			if (elems[18] == BST_CHECKED) uintMyAnswers++;// 8B
			if (elems[20] == BST_CHECKED) uintMyAnswers++;// 9A
			if (elems[25] == BST_CHECKED) uintMyAnswers++;// 10C
			if (elems[27] == BST_CHECKED) uintMyAnswers++;// 11B
			if (elems[30] == BST_CHECKED) uintMyAnswers++;// 12B
			if (elems[32] == BST_CHECKED) uintMyAnswers++;// 13A
			
			if (!lstrcmp(questionEightText, TEXT(";")))
				uintMyAnswers++;

			if (!lstrcmp(questionNineText, TEXT("bool")))
				uintMyAnswers++;
			
			uintPercentsCorrect = uintMyAnswers * 1.0 / uintAllAnswers * 100;
			swprintf_s(str, TEXT("%d/%d\n%.1f/100%%"), uintMyAnswers, uintAllAnswers, uintPercentsCorrect);
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