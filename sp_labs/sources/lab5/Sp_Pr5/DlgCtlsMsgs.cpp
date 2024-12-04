#include "DlgCtlsMsgs.h"

BOOL DlgCtls_OnInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam)
{
    return TRUE;
}

void DlgCtls_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
    int wmId = id;
    int wmEvent = codeNotify;
    static wchar_t pszTextBuff[textBufferSize] = {};
    switch (wmId)
    {
    case IDCANCEL:
    {
        EndDialog(hDlg, id);
    } return;

    case IDOK:
    { // ����� ��������� ������
        GetDlgItemTextW(hDlg, IDC_EDIT1, retMessage, textBufferSize);
        EndDialog(hDlg, id);
    } return;

    case IDC_BUTTON1: // BTN_SAVE � ������
    {
        int cch;
        HWND hEdit = GetDlgItem(hDlg, IDC_EDIT1);
        cch = SendMessageW(hEdit, WM_GETTEXT, (WPARAM)textBufferSize, (LPARAM)pszTextBuff);
        if (cch == 0)
        {
            MessageBoxW(hDlg, L"������� �����", L"������ Edit", MB_OK);
            return;
        }
        else if (WM_GETTEXT > textBufferSize)
        {
            MessageBoxW(hDlg, L"��������� ������������ ����� ������", L"������ Edit", MB_OK | MB_ICONERROR);
            return;
        }
        else
        {
            wchar_t msgBuff[textBufferSize] = {};
            SYSTEMTIME st; GetSystemTime(&st);
            if (StringCchPrintfW(msgBuff, textBufferSize - 1, L"����� : %d � %d ��� %d ���\n",
                st.wHour, st.wMinute, st.wSecond) == S_OK)
            {
                if (StringCchCatW(msgBuff, textBufferSize - 1, L"����� � ������: ") == S_OK
                    && StringCchCatW(msgBuff, textBufferSize - 1, pszTextBuff) == S_OK)
                {
                    MessageBoxW(hDlg, msgBuff, L"���������� ������", MB_OK);
                }
                else
                {
                    MessageBoxW(hDlg, L"������ ��� ������������", L"���������� ������", MB_OK | MB_ICONERROR);
                }
            }
            else
            {
                MessageBoxW(hDlg, L"��������� ������������ ����� ������", L"���������� ������", MB_OK | MB_ICONERROR);
            }
        }
    } return; //IDC_BTN_SAVE

    case IDC_BUTTON2: // BTN_ADD
    {
        int ind;
        HWND hListBox = GetDlgItem(hDlg, IDC_LIST1);
        ind = SendMessageW(hListBox, LB_ADDSTRING,
            (WPARAM)0, (LPARAM)pszTextBuff);
        if (ind == LB_ERR)
            MessageBoxW(hDlg, L"������ � ������", L"", MB_OK);
    } return; // end IDC_BTN_ADD
    }
}