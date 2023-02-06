#pragma once
#include "header.h"

class CGasModalDialog
{
public:
	CGasModalDialog(void);
public:
	~CGasModalDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CGasModalDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	int fPrices[5];
	int index;
	TCHAR text[255];
	HWND hCombo, hEditPrice, hRadioAmount, hRadioSum, hEditAmount, hEditSum, hStaticTotal;
	HWND hParent;
	HWND hParentEdit;
};