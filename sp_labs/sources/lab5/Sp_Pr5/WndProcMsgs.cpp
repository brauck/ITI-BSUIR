#include "WndProcMsgs.h"

void WndProc_OnCommand(HWND hWnd, int wmId, HWND hwndCtl, UINT wmEvent)
{
    {
        //int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            MessageBoxW(hWnd, L"������� ������� � ���������", L"� ���������", MB_OK);
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_HELP_ABOUT:
            MessageBoxW(hWnd, L"������� ������� ������ �������", L"������ �������", MB_OK);
            INT_PTR retVal;
            retVal = DialogBoxW(hInst, MAKEINTRESOURCEW(IDD_DIALOG1), hWnd, DlgAbout1);
            if (retVal == IDCANCEL) MessageBoxW(hWnd, L"������ �������� IDCANCEL", L"������", MB_OK);
            else if (retVal == IDOK) MessageBoxW(hWnd, L"������ �������� IDOK", L"������", MB_OK);
            break;
        case IDM_HELP_DLGCTLS:
            MessageBoxW(hWnd, L"������� ������� �������� ����������", L"�������� ����������", MB_OK);
            INT_PTR retVal1;
            retVal1 = DialogBoxW(hInst, MAKEINTRESOURCEW(IDD_DIALOG2), hWnd, DlgCtls);
            //if (retVal1 == IDOK) MessageBoxW(hWnd, retMessage, L"������2", MB_OK);
            break;
        case IDM_TEXT_VIEW:
        {
            MessageBoxW(hWnd, L"������� ������� �������� �����", L"�������� �����", MB_OK);
            DialogBoxW(hInst, MAKEINTRESOURCEW(IDD_DIALOG3), hWnd, DlgTextView);
        } break;
        case IDM_EXIT:
            MessageBoxW(hWnd, L"������� ������� �����", L"�����", MB_OK);
            DestroyWindow(hWnd);
            break;
        }
        FORWARD_WM_COMMAND(hWnd, wmId, hwndCtl, wmEvent, DefWindowProc);
    }	
}

void WndProc_OnPaint(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hDC = BeginPaint(hwnd, &ps); // ��������� ��������� ��� ���������� ���� 
    EndPaint(hwnd, &ps); // ���������� ���������� ����
}

void WndProc_OnDestroy(HWND hwnd)
{
    PostQuitMessage(0);
}