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
	// �������� �����������
	for (size_t i = 0, a = IDC_CHECK1_CD, b = IDC_EDIT_LEFT1_CD, c = IDC_EDIT_RIGHT1_CD; i < 4; i++)
	{
		hCheck[i]     = GetDlgItem(hwnd, a++);
		hEditLeft[i]  = GetDlgItem(hwnd, b++);
		hEditRight[i] = GetDlgItem(hwnd, c++);
	}

	hStaticTotal = GetDlgItem(hwnd, IDC_STATIC_CD);

	hParent = GetParent(hwnd);
	hParentEdit = GetDlgItem(hParent, IDC_EDIT_CAFE_MD);

	// ����
	fPrices[0] = 20;
	fPrices[1] = 35;
	fPrices[2] = 50;
	fPrices[3] = 25;

	TCHAR buf[SIZE];

	// �������� ����� ����� ������
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
	// �������� ������� �� ���. �������� ����, ���� ������ ���
	// � ���������, ���� ������ ��� ���
	for (size_t i = IDC_CHECK1_CD, j = 0; i <= IDC_CHECK4_CD; i++, j++)
	{
		if (IsDlgButtonChecked(hwnd, i)) 
			EnableWindow(hEditRight[j], 1);
		else 
			EnableWindow(hEditRight[j], 0);
	}

	// �������� ������� �� ������
	if (id == IDOK)
	{
		TCHAR textSum[SIZE];

		// ������ �� ����� � �������� �� ������
		for (size_t i = IDC_CHECK1_CD, j = 0; i <= IDC_CHECK4_CD; i++, j++)
		{
			if (IsDlgButtonChecked(hwnd, i))	// ���� ������, ��
			{
				// �������� ��� �����
				GetWindowText(hEditRight[j], textRightEdit, SIZE);
				// ����� � ���
				int iPrice = _tstoi(textRightEdit); // convert to int;
				// ��������� ��� � ���� �� �����
				iSum += iPrice * fPrices[j];
			}
		}
		_stprintf_s(textSum, TEXT("%d"), iSum);

		SetWindowText(hStaticTotal, textSum);
		// ������ ����� � ������������ ����
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

