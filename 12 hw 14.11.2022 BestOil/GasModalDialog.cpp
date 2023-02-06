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
	// �������� �����������
	hCombo			= GetDlgItem(hwnd, IDC_COMBO_FUEL_GD);
	hEditPrice		= GetDlgItem(hwnd, IDC_EDIT_PRICE_GD);

	hRadioAmount	= GetDlgItem(hwnd, IDC_RADIO_AMOUNT_GD);
	hEditAmount		= GetDlgItem(hwnd, IDC_EDIT_AMOUNT_GD);
	hRadioSum		= GetDlgItem(hwnd, IDC_RADIO_SUM_GD);
	hEditSum		= GetDlgItem(hwnd, IDC_EDIT_SUM_GD);

	hStaticTotal	= GetDlgItem(hwnd, IDC_STATIC_TOTAL_GD);

	hParent			= GetParent(hwnd);
	hParentEdit     = GetDlgItem(hParent, IDC_EDIT_GAS_MD);

	
	// ��������� � ����� ���� ������
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("�-95 �������")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("�-95")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("�-92")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("��������� �������")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("��� �������������")));

	// ����� 0 �������� � �����. ����� �������� ������ wparam
	SendMessage(hCombo, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
	
	// ���� �� �������
	fPrices[0] = 48;
	fPrices[1] = 49;
	fPrices[2] = 50;
	fPrices[3] = 28;
	fPrices[4] = 54;

	// ��������� ������ ����� �� 1 � ������� ����
	index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
	_stprintf_s(text, TEXT("%d"), fPrices[index]);
	SetWindowText(hEditPrice, text);

	// ������ ����� ������������
	EnableWindow(hEditAmount, 0);
	EnableWindow(hEditSum, 0);

	return TRUE;
}

void CGasModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{	
	// �������� ������ �������� � ����� �����
	if (id == IDC_COMBO_FUEL_GD && codeNotify == CBN_SELCHANGE)
	{
		index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
		_stprintf_s(text, TEXT("%d"), fPrices[index]);
		SetWindowText(hEditPrice, text);
	}

	// �������� ������� �� �����
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

	// �������� ������� �� ������ ��
	if (id == IDOK)
	{
		TCHAR textSum[SIZE];
		// ������� ����� ����������
		if (IsDlgButtonChecked(hwnd, IDC_RADIO_AMOUNT_GD))
		{
			TCHAR textPriceForOne[SIZE];
			// �������� ������������ ����� �� �������� ���������� 
			// ��������������� � ��������� � ������
			GetWindowText(hEditPrice, textPriceForOne, SIZE);
			int iPriceForOne = _tstoi(textPriceForOne); // convert to int;


			TCHAR textAmount[SIZE];
			// �������� ������������ ����� �� �������� ���������� 
			// ��������������� � ��������� � ������
			GetWindowText(hEditAmount, textAmount, SIZE);
			int iAmount = _tstoi(textAmount); // convert to int;


			int iSum = iPriceForOne * iAmount;
			_stprintf_s(textSum, TEXT("%d"), iSum);

			SetWindowText(hStaticTotal, textSum);

			// ������ ����� � ������������ ����
			SetWindowText(hParentEdit, textSum);
		}
		// ������� ����� �����
		else if (IsDlgButtonChecked(hwnd, IDC_RADIO_SUM_GD))
		{			
			// ������ ������ ��� ������
			TCHAR bufForAmount[SIZE];
			
			// �������� ������������ ����� �� �������� ���������� 
			// ��������������� � ��������� � �����
			GetWindowText(hEditAmount, bufForAmount, SIZE);

			
			/*��� ������ ������ � ����������*/
			//TCHAR newTextForAmount[SIZE] = TEXT("1239");
			//// ���������� ����� ����� � �����
			//_tcscpy_s(bufForAmount, newTextForAmount);
			//// set ������ � ���� ����������
			//SetWindowText(hEditAmount, bufForAmount);


			// ������ ����� � ����� ����� ��, ��� �����
			GetWindowText(hEditSum, textSum, SIZE);
			SetWindowText(hStaticTotal, textSum);

			// ������ ����� � ������������ ����
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

