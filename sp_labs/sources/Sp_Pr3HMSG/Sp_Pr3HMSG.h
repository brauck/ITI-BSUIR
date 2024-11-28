#pragma once
#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include <strsafe.h>

extern HWND hEdit;
extern HWND hListBox;
extern HWND hButtonSave;
extern HWND hButtonAdd;
extern HWND hButtonExit;

extern HINSTANCE g_hInst;

#define IDC_BTN_SAVE	150
#define IDC_BTN_ADD		151
#define IDC_EDIT1		152
#define IDC_LISTBOX		153	

//-- Prototypes -------------------

void WindowProc_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void WindowProc_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
BOOL WindowProc_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void WindowProc_OnPaint(HWND hwnd);
void WindowProc_OnDestroy(HWND hwnd);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);