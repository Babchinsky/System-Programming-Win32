#include "GasModalDialog.h"

#define SIZE 255

CGasModalDialog* CGasModalDialog::ptr = NULL;

CGasModalDialog::CGasModalDialog(void)
{
	ptr = this;
}

CGasModalDialog::~CGasModalDialog(void)
{

}

void CGasModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CGasModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	// Получаем дескрипторы
	hCombo			= GetDlgItem(hwnd, IDC_COMBO_FUEL_GD);
	hEditPrice		= GetDlgItem(hwnd, IDC_EDIT_PRICE_GD);

	hRadioAmount	= GetDlgItem(hwnd, IDC_RADIO_AMOUNT_GD);
	hEditAmount		= GetDlgItem(hwnd, IDC_EDIT_AMOUNT_GD);
	hRadioSum		= GetDlgItem(hwnd, IDC_RADIO_SUM_GD);
	hEditSum		= GetDlgItem(hwnd, IDC_EDIT_SUM_GD);

	hStaticTotal	= GetDlgItem(hwnd, IDC_STATIC_TOTAL_GD);

	hParent			= GetParent(hwnd);
	hParentEdit     = GetDlgItem(hParent, IDC_EDIT_GAS_MD);

	
	// Добавляем в комбо бокс строки
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("А-95 премиум")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("А-95")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("А-92")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("Дизельное топливо")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("Газ авто­мобильный")));

	// Выбор 0 элемента в комбо. Чтобы поменять меняем wparam
	SendMessage(hCombo, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
	
	// цены на топливо
	fPrices[0] = 48;
	fPrices[1] = 49;
	fPrices[2] = 50;
	fPrices[3] = 28;
	fPrices[4] = 54;

	// назначаем индекс едита на 1 и выводим цену
	index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
	_stprintf_s(text, TEXT("%d"), fPrices[index]);
	SetWindowText(hEditPrice, text);

	// Делаем эдиты недоступными
	EnableWindow(hEditAmount, 0);
	EnableWindow(hEditSum, 0);

	return TRUE;
}

void CGasModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{	
	// Проверка выбора элемента в комбо боксе
	if (id == IDC_COMBO_FUEL_GD && codeNotify == CBN_SELCHANGE)
	{
		index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
		_stprintf_s(text, TEXT("%d"), fPrices[index]);
		SetWindowText(hEditPrice, text);
	}

	// Проверка нажатий на радио
	if (id == IDC_RADIO_AMOUNT_GD)
	{
		EnableWindow(hEditAmount, 1);
		EnableWindow(hEditSum, 0);
	}
	else if (id == IDC_RADIO_SUM_GD)
	{
		EnableWindow(hEditAmount, 0);
		EnableWindow(hEditSum, 1);
	}

	// Проверка нажатия на кнопку ОК
	if (id == IDOK)
	{
		TCHAR textSum[SIZE];
		// Выбрали радио количества
		if (IsDlgButtonChecked(hwnd, IDC_RADIO_AMOUNT_GD))
		{
			TCHAR textPriceForOne[SIZE];
			// получить существующий текст из элемента управления 
			// редактированием и поместить в массив
			GetWindowText(hEditPrice, textPriceForOne, SIZE);
			int iPriceForOne = _tstoi(textPriceForOne); // convert to int;


			TCHAR textAmount[SIZE];
			// получить существующий текст из элемента управления 
			// редактированием и поместить в массив
			GetWindowText(hEditAmount, textAmount, SIZE);
			int iAmount = _tstoi(textAmount); // convert to int;


			int iSum = iPriceForOne * iAmount;
			_stprintf_s(textSum, TEXT("%d"), iSum);

			SetWindowText(hStaticTotal, textSum);

			// Ставим текст в родительский эдит
			SetWindowText(hParentEdit, textSum);
		}
		// Выбрали радио суммы
		else if (IsDlgButtonChecked(hwnd, IDC_RADIO_SUM_GD))
		{			
			// Создаём буффер для текста
			TCHAR bufForAmount[SIZE];
			
			// получить существующий текст из элемента управления 
			// редактированием и поместить в буфер
			GetWindowText(hEditAmount, bufForAmount, SIZE);

			
			/*Для замены текста в количестве*/
			//TCHAR newTextForAmount[SIZE] = TEXT("1239");
			//// копировать новый текст в буфер
			//_tcscpy_s(bufForAmount, newTextForAmount);
			//// set текста в эдит количества
			//SetWindowText(hEditAmount, bufForAmount);


			// Делаем текст в итого такой же, как сумме
			GetWindowText(hEditSum, textSum, SIZE);
			SetWindowText(hStaticTotal, textSum);

			// Ставим текст в родительский эдит
			SetWindowText(hParentEdit, textSum);
		}
	}
}

BOOL CALLBACK CGasModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

