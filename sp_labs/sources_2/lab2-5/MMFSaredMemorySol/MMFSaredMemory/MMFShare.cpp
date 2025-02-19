#include <windows.h>
#include <windowsx.h>
#include "resource.h"

#define MMF_SIZE 4096
#define MMF_NAME TEXT("MMFSharedData")

HANDLE hFileMap = NULL;
LPVOID lpView = NULL;


BOOL InitMemoryMapping(HWND hwnd) {
    hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MMF_SIZE, MMF_NAME);
    if (!hFileMap) {
        MessageBox(hwnd, TEXT("Не удалось создать File Mapping!"), TEXT("Ошибка"), MB_OK);
        return FALSE;
    }
    lpView = MapViewOfFile(hFileMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, MMF_SIZE);
    if (!lpView) {
        MessageBox(hwnd, TEXT("Не удалось создать окно просмотра!"), TEXT("Ошибка"), MB_OK);
        CloseHandle(hFileMap);
        return FALSE;
    }
    return TRUE;
}

void WriteToMemory(HWND hwnd) {
    if (lpView) {
        GetDlgItemText(hwnd, IDC_DATA, (LPTSTR)lpView, MMF_SIZE);
    }
}

void ReadFromMemory(HWND hwnd) {
    if (lpView) {
        SetDlgItemText(hwnd, IDC_DATA, (LPTSTR)lpView);
    }
}

BOOL CALLBACK Dlg_Proc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    
    

    switch (uMsg) {
    case WM_INITDIALOG:
        InitMemoryMapping(hDlg);
        SetDlgItemText(hDlg, IDC_DATA, TEXT("Введите текст..."));
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_WRITE: WriteToMemory(hDlg); break;
        case IDC_READ: ReadFromMemory(hDlg); break;
        case IDCANCEL:
            if (lpView) UnmapViewOfFile(lpView);
            if (hFileMap) CloseHandle(hFileMap);
            EndDialog(hDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShowCmd) {
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_MMFSHARE), NULL, Dlg_Proc);
}
