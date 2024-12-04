#include "DlgAbout1Msgs.h"

BOOL DlgAbout1_OnInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam)
{
    SYSTEMTIME st; GetLocalTime(&st);
    const UINT32 textBufferSize = 200;
    WCHAR txt[textBufferSize] = {};
    if (StringCchPrintfW(txt, textBufferSize - 1, L"%d � %d ��� %d ���\n",
        st.wHour, st.wMinute, st.wSecond) == S_OK)
    {
        SetDlgItemTextW(hDlg, IDC_TIME, txt);
    }
    else
    {
        MessageBoxW(hDlg, L"��������� ������������ ����� ������", L"���������� ������", MB_OK | MB_ICONERROR);
    }
    return TRUE;
}

void DlgAbout1_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
    if (id == IDOK || id == IDCANCEL)
    {
        EndDialog(hDlg, LOWORD(hwndCtl));
        return;
    }
}