#include "MainModalDialog.h"
#include "GasModalDialog.h"
#include "CafeModalDialog.h"

CMainModalDialog* CMainModalDialog::ptr = NULL;

CMainModalDialog::CMainModalDialog(void)
{
	ptr = this;
}

CMainModalDialog::~CMainModalDialog(void)
{

}

void CMainModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CMainModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hButtonGas = GetDlgItem(hwnd, IDC_BUTTON_GAS_MD);
	hButtonCafe = GetDlgItem(hwnd, IDC_BUTTON_CAFE_MD);
	hEditGas = GetDlgItem(hwnd, IDC_EDIT_GAS_MD);
	hEditCafe = GetDlgItem(hwnd, IDC_EDIT_CAFE_MD);
	hEditTotal = GetDlgItem(hwnd, IDC_EDIT_TOTAL_MD);
	iSum = 0;
	return TRUE;
}

void CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_BUTTON_GAS_MD)
	{
		CGasModalDialog dlg;
		INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_GAS), hwnd, CGasModalDialog::DlgProc);
	}
	else if (id == IDC_BUTTON_CAFE_MD)
	{
		CCafeModalDialog dlg;
		INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_CAFE), hwnd, CCafeModalDialog::DlgProc);
	}

	if (id == IDOK)
	{
		iSum = 0;
		TCHAR textSum[SIZE];
		int iPrice = 0;
		
		TCHAR buf[SIZE];

		// Получаем его текст
		GetWindowText(hEditGas, buf, SIZE);
		// Текст в инт
		iPrice = _tstoi(buf); // convert to int;
		// Суммируем инт и цену за штуку
		iSum += iPrice;


		// Получаем его текст
		GetWindowText(hEditCafe, buf, SIZE);
		// Текст в инт
		iPrice = _tstoi(buf); // convert to int;
		// Суммируем инт и цену за штуку
		iSum += iPrice;

		_stprintf_s(textSum, TEXT("%d"), iSum);
		SetWindowText(hEditTotal, textSum);
	}
}

BOOL CALLBACK CMainModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
