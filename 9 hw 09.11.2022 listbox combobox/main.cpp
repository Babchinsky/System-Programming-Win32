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
        srand(unsigned(time(0))); // Каждый запуск новый sRand
        isItFirstTime = false;
    }
    return min + rand() % ((max + 1) - min);
}




int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    // создаём главное окно приложения на основе модального диалога
    return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}



HWND hList, hEdit;          // дескрипторы
HWND hRadio[COUNT_RADIO];   // дескрипторы
TCHAR buf[STR_LENGTH];      // буфер
int iList[LIST_LENGTH];
int iListSum;
long long iListProduct;
double iListAverage;
TCHAR sTitle[] = TEXT("Калькулятор");

void GenerateList()
{
    // Генерируем массив значений и записываем их в лист
    for (size_t i = 0; i < LIST_LENGTH; i++)
    {
        iList[i] = RandomNumFromDiapasone(-10, 10);
        iListSum += iList[i];
        iListProduct *= iList[i];

        swprintf_s(buf, TEXT("%d"), iList[i]);// Записываем в буфер наше число
        SendMessage(hList, LB_ADDSTRING, 0, LPARAM(buf));  // Добавляем строку в наш лист
    }
    iListAverage = iListSum * 1.0 / LIST_LENGTH;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
    switch (message)
    {
    case WM_INITDIALOG:
        SetWindowText(hWnd, sTitle);                // Меняем текст заголовка

        for (size_t i = IDC_RADIO1, j = 0; i <= IDC_RADIO3; i++)
            hRadio[j++] = GetDlgItem(hWnd, i);       // Получаем дескрипторы радио


        hList = GetDlgItem(hWnd, IDC_LIST1);       // Получаем дескриптор листа
        hEdit = GetDlgItem(hWnd, IDC_EDIT1);       // Получаем дескриптор едита

        iListSum = 0, iListProduct = 1, iListAverage = 0; // присваиваем результатам значения по умолчанию

        GenerateList();

        SendMessage(hRadio[0], BM_SETCHECK, BST_CHECKED, 1);           // Отмечаем первое радио, как отмеченное
        swprintf_s(buf, TEXT("%d"), iListSum);                         // Записываем в буфер наше число
        SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(buf));                // Устанавливаем количество дней в EditControl
        return TRUE;

    case WM_COMMAND:
        if (LOWORD(wp) == IDC_BUTTON1)  // Если нажата кнопка
        {
            SendMessage(hList, LB_RESETCONTENT, 0, 0);
            iListSum = 0, iListProduct = 1, iListAverage = 0; // присваиваем результатам значения по умолчанию

            GenerateList();

            if (SendDlgItemMessage(hWnd, IDC_RADIO1, BM_GETCHECK, 0, 0) == BST_CHECKED)
                swprintf_s(buf, TEXT("%d"), iListSum);// Записываем в буфер наше число

            if (SendDlgItemMessage(hWnd, IDC_RADIO2, BM_GETCHECK, 0, 0) == BST_CHECKED)
                swprintf_s(buf, TEXT("%d"), iListProduct);// Записываем в буфер наше число

            if (SendDlgItemMessage(hWnd, IDC_RADIO3, BM_GETCHECK, 0, 0) == BST_CHECKED)
                swprintf_s(buf, TEXT("%.1f"), iListAverage);// Записываем в буфер наше число

            SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(buf));   // Устанавливаем ответ в EditControl
        }

        if (LOWORD(wp) == IDC_RADIO1)  // Если нажат радио
        {
            swprintf_s(buf, TEXT("%d"), iListSum);// Записываем в буфер наше число
            SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(buf));   // Устанавливаем ответ в EditControl
        }
        else if (LOWORD(wp) == IDC_RADIO2)// Если нажат радио
        {
            swprintf_s(buf, TEXT("%d"), iListProduct);// Записываем в буфер наше число
            SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(buf));   // Устанавливаем ответ в EditControl
        }
        else if (LOWORD(wp) == IDC_RADIO3)// Если нажат радио
        {
            swprintf_s(buf, TEXT("%.1f"), iListAverage);// Записываем в буфер наше число
            SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(buf));   // Устанавливаем ответ в EditControl
        }
        
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0); // закрываем модальный диалог
        return TRUE;
    }
    return FALSE;
}