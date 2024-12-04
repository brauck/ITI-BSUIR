#pragma once

#include <windows.h>
#include <windowsx.h>
#include <strsafe.h>
#include "framework.h"
#include "resource.h"

#include "WndProcMsgs.h"
#include "AboutMsgs.h"
#include "DlgAbout1Msgs.h"
#include "DlgCtlsMsgs.h"
#include "DlgTextViewMsgs.h"

#define MAX_LOADSTRING 100

extern HINSTANCE hInst;                                // current instance
extern WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
extern WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
const UINT32 textBufferSize = 500;
const UINT32 fileBufferSize = 1000;
extern WCHAR retMessage[textBufferSize];
extern wchar_t pszFileTextBuff[fileBufferSize];

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DlgAbout1(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DlgCtls(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DlgTextView(HWND, UINT, WPARAM, LPARAM);
