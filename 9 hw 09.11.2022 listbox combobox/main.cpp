#include <windows.h>
#include <tchar.h>
#include <ctime>
#include "resource.h"

#define STR_LENGTH 2048
#define LIST_LENGTH 16
#define COUNT_RADIO 3

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

template <typename T>
T RandomNumFromDiapasone(T min, T max) //range : [min, max]
{
    static bool isItFirstTime = true;
    if (isItFirstTime)
    {
        srand(unsigned(time(0))); // ������ ������ ����� sRand
        isItFirstTime = false;
    }
    return min + rand() % ((max + 1) - min);
}




int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    // ������ ������� ���� ���������� �� ������ ���������� �������
    return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}



HWND hList, hEdit;          // �����������
HWND hRadio[COUNT_RADIO];   // �����������
TCHAR buf[STR_LENGTH];      // �����
int iList[LIST_LENGTH];
int iListSum;
long long iListProduct;
double iListAverage;
TCHAR sTitle[] = TEXT("�����������");

void GenerateList()
{
    // ���������� ������ �������� � ���������� �� � ����
    for (size_t i = 0; i < LIST_LENGTH; i++)
    {
        iList[i] = RandomNumFromDiapasone(-10, 10);
        iListSum += iList[i];
        iListProduct *= iList[i];

        swprintf_s(buf, TEXT("%d"), iList[i]);// ���������� � ����� ���� �����
        SendMessage(hList, LB_ADDSTRING, 0, LPARAM(buf));  // ��������� ������ � ��� ����
    }
    iListAverage = iListSum * 1.0 / LIST_LENGTH;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
    switch (message)
    {
    case WM_INITDIALOG:
        SetWindowText(hWnd, sTitle);                // ������ ����� ���������

        for (size_t i = IDC_RADIO1, j = 0; i <= IDC_RADIO3; i++)
            hRadio[j++] = GetDlgItem(hWnd, i);       // �������� ����������� �����


        hList = GetDlgItem(hWnd, IDC_LIST1);       // �������� ���������� �����
        hEdit = GetDlgItem(hWnd, IDC_EDIT1);       // �������� ���������� �����

        iListSum = 0, iListProduct = 1, iListAverage = 0; // ����������� ����������� �������� �� ���������

        GenerateList();

        SendMessage(hRadio[0], BM_SETCHECK, BST_CHECKED, 1);           // �������� ������ �����, ��� ����������
        swprintf_s(buf, TEXT("%d"), iListSum);                         // ���������� � ����� ���� �����
        SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(buf));                // ������������� ���������� ���� � EditControl
        return TRUE;

    case WM_COMMAND:
        if (LOWORD(wp) == IDC_BUTTON1)  // ���� ������ ������
        {
            SendMessage(hList, LB_RESETCONTENT, 0, 0);
            iListSum = 0, iListProduct = 1, iListAverage = 0; // ����������� ����������� �������� �� ���������

            GenerateList();

            if (SendDlgItemMessage(hWnd, IDC_RADIO1, BM_GETCHECK, 0, 0) == BST_CHECKED)
                swprintf_s(buf, TEXT("%d"), iListSum);// ���������� � ����� ���� �����

            if (SendDlgItemMessage(hWnd, IDC_RADIO2, BM_GETCHECK, 0, 0) == BST_CHECKED)
                swprintf_s(buf, TEXT("%d"), iListProduct);// ���������� � ����� ���� �����

            if (SendDlgItemMessage(hWnd, IDC_RADIO3, BM_GETCHECK, 0, 0) == BST_CHECKED)
                swprintf_s(buf, TEXT("%.1f"), iListAverage);// ���������� � ����� ���� �����

            SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(buf));   // ������������� ����� � EditControl
        }

        if (LOWORD(wp) == IDC_RADIO1)  // ���� ����� �����
        {
            swprintf_s(buf, TEXT("%d"), iListSum);// ���������� � ����� ���� �����
            SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(buf));   // ������������� ����� � EditControl
        }
        else if (LOWORD(wp) == IDC_RADIO2)// ���� ����� �����
        {
            swprintf_s(buf, TEXT("%d"), iListProduct);// ���������� � ����� ���� �����
            SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(buf));   // ������������� ����� � EditControl
        }
        else if (LOWORD(wp) == IDC_RADIO3)// ���� ����� �����
        {
            swprintf_s(buf, TEXT("%.1f"), iListAverage);// ���������� � ����� ���� �����
            SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(buf));   // ������������� ����� � EditControl
        }
        
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0); // ��������� ��������� ������
        return TRUE;
    }
    return FALSE;
}