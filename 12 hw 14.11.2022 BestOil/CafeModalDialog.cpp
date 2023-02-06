#include "CafeModalDialog.h"

CCafeModalDialog* CCafeModalDialog::ptr = NULL;

CCafeModalDialog::CCafeModalDialog(void)
{
	ptr = this;
}

CCafeModalDialog::~CCafeModalDialog(void)
{

}

void CCafeModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CCafeModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	// Получаем дескрипторы
	for (size_t i = 0, a = IDC_CHECK1_CD, b = IDC_EDIT_LEFT1_CD, c = IDC_EDIT_RIGHT1_CD; i < 4; i++)
	{
		hCheck[i]     = GetDlgItem(hwnd, a++);
		hEditLeft[i]  = GetDlgItem(hwnd, b++);
		hEditRight[i] = GetDlgItem(hwnd, c++);
	}

	hStaticTotal = GetDlgItem(hwnd, IDC_STATIC_CD);

	hParent = GetParent(hwnd);
	hParentEdit = GetDlgItem(hParent, IDC_EDIT_CAFE_MD);

	// цены
	fPrices[0] = 20;
	fPrices[1] = 35;
	fPrices[2] = 50;
	fPrices[3] = 25;

	TCHAR buf[SIZE];

	// Назначем текст левым эдитам
	for (size_t i = 0; i < 4; i++)
	{
		_stprintf_s(buf, TEXT("%d"), fPrices[i]);
		SetWindowText(hEditLeft[i], buf);
	}
		
	iSum = 0;
	return TRUE;
}

void CCafeModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	iSum = 0;
	// Проверка нажатий на чек. Включаем эдит, если нажали чек
	// и отключаем, если нажали ещё раз
	for (size_t i = IDC_CHECK1_CD, j = 0; i <= IDC_CHECK4_CD; i++, j++)
	{
		if (IsDlgButtonChecked(hwnd, i)) 
			EnableWindow(hEditRight[j], 1);
		else 
			EnableWindow(hEditRight[j], 0);
	}

	// Проверка нажатия на кнопку
	if (id == IDOK)
	{
		TCHAR textSum[SIZE];

		// Шагаем по чекам и проверям на селект
		for (size_t i = IDC_CHECK1_CD, j = 0; i <= IDC_CHECK4_CD; i++, j++)
		{
			if (IsDlgButtonChecked(hwnd, i))	// если селект, то
			{
				// Получаем его текст
				GetWindowText(hEditRight[j], textRightEdit, SIZE);
				// Текст в инт
				int iPrice = _tstoi(textRightEdit); // convert to int;
				// Суммируем инт и цену за штуку
				iSum += iPrice * fPrices[j];
			}
		}
		_stprintf_s(textSum, TEXT("%d"), iSum);

		SetWindowText(hStaticTotal, textSum);
		// Ставим текст в родительский эдит
		SetWindowText(hParentEdit, textSum);
	}
}

BOOL CALLBACK CCafeModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

