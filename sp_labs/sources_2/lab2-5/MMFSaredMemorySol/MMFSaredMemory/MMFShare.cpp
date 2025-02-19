#include <windows.h>
#include <windowsx.h>
#include "resource.h"

const DWORD dwMaximumSizeLow = 4096;
HANDLE hFileMap = NULL;
LPVOID lpView = NULL;

BOOL InitMemoryMapping(HWND hwnd)
{
    hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,
        NULL, PAGE_READWRITE, 0, dwMaximumSizeLow,
        L"MMFSA");

    if (!hFileMap)
    {
        MessageBox(hwnd, TEXT("File mapping object is not created"),
            TEXT("MMFSA"), MB_OK);
        return FALSE;
    }

    lpView = MapViewOfFile(hFileMap, FILE_MAP_READ | FILE_MAP_WRITE,
        0, 0, dwMaximumSizeLow);

    if (!lpView)
    {
        MessageBox(hwnd, TEXT("View of a file mapping is not created"),
            TEXT("MMFSA"), MB_OK);
        CloseHandle(hFileMap);
        return FALSE;
    }
    return TRUE;
}

void WriteToMemory(HWND hwnd)
{
    if (lpView) {
        GetDlgItemText(hwnd, IDC_DATA, (LPTSTR)lpView, dwMaximumSizeLow);
    }
}

void ReadFromMemory(HWND hwnd)
{
    if (lpView)
    {
        SetDlgItemText(hwnd, IDC_DATA, (LPTSTR)lpView);
    }
}

BOOL CALLBACK Dlg_Proc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
        {
            InitMemoryMapping(hDlg);
            SetDlgItemText(hDlg, IDC_DATA, TEXT("Здесь вводите данные."));
        }return TRUE;

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case IDC_WRITE: WriteToMemory(hDlg); break;
                case IDC_READ: ReadFromMemory(hDlg); break;
                case IDCANCEL:
                {
                    if (lpView) UnmapViewOfFile(lpView);
                    if (hFileMap) CloseHandle(hFileMap);
                    EndDialog(hDlg, 0);
                    return TRUE;
                }
            }break;
        }        
    }return FALSE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,
    LPSTR lpCmd, int nShowCmd)
{
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_MMFSHARE),
        NULL, Dlg_Proc);
}
