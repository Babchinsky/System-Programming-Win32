#pragma once
#include "header.h"

#define QUESTION_NUMBER 3
#define ANSWER_NUMBER 4

class CMultithreadDlg
{
public:
	CMultithreadDlg(void);
public:
	~CMultithreadDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CMultithreadDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	HWND hStaticTime, hProgress;
	HANDLE hndlTime;
};