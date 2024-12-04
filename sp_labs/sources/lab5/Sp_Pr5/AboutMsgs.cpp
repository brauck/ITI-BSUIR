#include "AboutMsgs.h"

BOOL About_OnInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam)
{
	return TRUE;
}

void About_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
    if (id == IDOK || id == IDCANCEL)
    {
        EndDialog(hDlg, LOWORD(hwndCtl));
        return;
    }
}