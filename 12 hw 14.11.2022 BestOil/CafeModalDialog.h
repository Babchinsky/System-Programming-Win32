#pragma once
#include "header.h"

#define SIZE 255

class CCafeModalDialog
{
public:
	CCafeModalDialog(void);
public:
	~CCafeModalDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CCafeModalDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);

	HWND hCheck[4], hEditLeft[4], hEditRight[4], hStaticTotal;
	HWND hParent;
	HWND hParentEdit;
	int fPrices[4];
	TCHAR textRightEdit[SIZE];
	int iSum;
};