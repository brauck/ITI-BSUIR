#include "WndProcMsgs.h"

void WndProc_OnCommand(HWND hWnd, int wmId, HWND hwndCtl, UINT wmEvent)
{
    {
        //int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            MessageBoxW(hWnd, L"Выбрана команда О программе", L"О программе", MB_OK);
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_HELP_ABOUT:
            MessageBoxW(hWnd, L"Выбрана команда Пример диалога", L"Пример диалога", MB_OK);
            INT_PTR retVal;
            retVal = DialogBoxW(hInst, MAKEINTRESOURCEW(IDD_DIALOG1), hWnd, DlgAbout1);
            if (retVal == IDCANCEL) MessageBoxW(hWnd, L"Диалог завершен IDCANCEL", L"Диалог", MB_OK);
            else if (retVal == IDOK) MessageBoxW(hWnd, L"Диалог завершен IDOK", L"Диалог", MB_OK);
            break;
        case IDM_HELP_DLGCTLS:
            MessageBoxW(hWnd, L"Выбрана команда Элементы управления", L"Элементы управления", MB_OK);
            INT_PTR retVal1;
            retVal1 = DialogBoxW(hInst, MAKEINTRESOURCEW(IDD_DIALOG2), hWnd, DlgCtls);
            //if (retVal1 == IDOK) MessageBoxW(hWnd, retMessage, L"Диалог2", MB_OK);
            break;
        case IDM_TEXT_VIEW:
        {
            MessageBoxW(hWnd, L"Выбрана команда Просмотр файла", L"Просмотр файла", MB_OK);
            DialogBoxW(hInst, MAKEINTRESOURCEW(IDD_DIALOG3), hWnd, DlgTextView);
        } break;
        case IDM_EXIT:
            MessageBoxW(hWnd, L"Выбрана команда Выход", L"Выход", MB_OK);
            DestroyWindow(hWnd);
            break;
        }
        FORWARD_WM_COMMAND(hWnd, wmId, hwndCtl, wmEvent, DefWindowProc);
    }	
}

void WndProc_OnPaint(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hDC = BeginPaint(hwnd, &ps); // Получение контекста для обновления окна 
    EndPaint(hwnd, &ps); // Завершение обновления окна
}

void WndProc_OnDestroy(HWND hwnd)
{
    PostQuitMessage(0);
}