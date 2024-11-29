// Sp_Pr5.cpp : Defines the entry point for the application.
//
#include <strsafe.h>
#include "framework.h"
#include "Sp_Pr5.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
const UINT32 textBufferSize = 500;
WCHAR retMessage[textBufferSize];

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DlgAbout1(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DlgCtls(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SPPR5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPPR5));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPPR5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SPPR5);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      500, 100, 600, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_HELP_ABOUT:
                INT_PTR retVal;
                retVal = DialogBoxW(hInst, MAKEINTRESOURCEW(IDD_DIALOG1), hWnd, DlgAbout1);
                if (retVal == IDCANCEL) MessageBoxW(hWnd, L"Диалог завершен IDCANCEL", L"Диалог", MB_OK);
                else if (retVal == IDOK) MessageBoxW(hWnd, L"Диалог завершен IDOK", L"Диалог", MB_OK);
                break;
            case IDM_HELP_DLGCTLS:
                INT_PTR retVal1;
                retVal1 = DialogBoxW(hInst, MAKEINTRESOURCEW(IDD_DIALOG2), hWnd, DlgCtls);
                if (retVal1 == IDOK) MessageBoxW(hWnd, retMessage, L"Диалог2", MB_OK);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// Message handler for Диалог окна "О программе" box.
INT_PTR CALLBACK DlgAbout1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        SYSTEMTIME st; GetLocalTime(&st);
        const UINT32 textBufferSize  = 200;
        WCHAR txt[textBufferSize] = {};
        if (StringCchPrintfW(txt, textBufferSize - 1, L"%d ч %d мин %d сек\n",
            st.wHour, st.wMinute, st.wSecond) == S_OK)
        {
            SetDlgItemTextW(hDlg, IDC_TIME, txt);
        }
        else
        {
            MessageBoxW(hDlg, L"Превышена максимальная длина текста", L"Содержимое буфера", MB_OK | MB_ICONERROR);
        }
    }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if ((LOWORD(wParam) == IDOK) || (LOWORD(wParam) == IDCANCEL))
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// Message handler for "Пример элементов управления в диалоговом окне" box.
INT_PTR CALLBACK DlgCtls(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        /*SYSTEMTIME st; GetLocalTime(&st);
        const UINT32 textBufferSize = 200;
        WCHAR txt[textBufferSize] = {};
        if (StringCchPrintfW(txt, textBufferSize - 1, L"%d ч %d мин %d сек\n",
            st.wHour, st.wMinute, st.wSecond) == S_OK)
        {
            SetDlgItemTextW(hDlg, IDC_TIME, txt);
        }
        else
        {
            MessageBoxW(hDlg, L"Превышена максимальная длина текста", L"Содержимое буфера", MB_OK | MB_ICONERROR);
        }*/
    } return (INT_PTR)TRUE;

    case WM_COMMAND:
    {        
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);
        static wchar_t pszTextBuff[textBufferSize] = {};
        switch (wmId)
        {
        case IDCANCEL:
        {
            EndDialog(hDlg, LOWORD(wParam));
        } return (INT_PTR)TRUE;

        case IDOK:
        { // здесь сохраняем данные
            GetDlgItemTextW(hDlg, IDC_EDIT1, retMessage, textBufferSize);
            EndDialog(hDlg, LOWORD(wParam));
        } return (INT_PTR)TRUE;

        case IDC_BUTTON1: // BTN_SAVE в память
        {
            int cch;
            HWND hEdit = GetDlgItem(hDlg, IDC_EDIT1);
            cch = SendMessageW(hEdit, WM_GETTEXT, (WPARAM)textBufferSize, (LPARAM)pszTextBuff);
            if (cch == 0)
            {
                MessageBoxW(hDlg, L"Введите текст", L"Читаем Edit", MB_OK);
                return (INT_PTR)TRUE;
            }
            else if (WM_GETTEXT > textBufferSize)
            {
                MessageBoxW(hDlg, L"Превышена максимальная длина текста", L"Читаем Edit", MB_OK | MB_ICONERROR);
                return (INT_PTR)TRUE;
            }
            else
            {
                wchar_t msgBuff[textBufferSize] = {};
                SYSTEMTIME st; GetSystemTime(&st);
                if (StringCchPrintfW(msgBuff, textBufferSize - 1, L"Время : %d ч %d мин %d сек\n",
                    st.wHour, st.wMinute, st.wSecond) == S_OK)
                {
                    if (StringCchCatW(msgBuff, textBufferSize - 1, L"Текст в памяти: ") == S_OK
                        && StringCchCatW(msgBuff, textBufferSize - 1, pszTextBuff) == S_OK)
                    {
                        MessageBoxW(hDlg, msgBuff, L"Содержимое буфера", MB_OK);
                    }
                    else
                    {
                        MessageBoxW(hDlg, L"Ошибка при конкатенации", L"Содержимое буфера", MB_OK | MB_ICONERROR);
                    }
                }
                else
                {
                    MessageBoxW(hDlg, L"Превышена максимальная длина текста", L"Содержимое буфера", MB_OK | MB_ICONERROR);
                }
            }
        } return (INT_PTR)TRUE; //IDC_BTN_SAVE

        case IDC_BUTTON2: // BTN_ADD
        {
            int ind;
            HWND hListBox = GetDlgItem(hDlg, IDC_LIST1);
            ind = SendMessageW(hListBox, LB_ADDSTRING,
                (WPARAM)0, (LPARAM)pszTextBuff);
            if (ind == LB_ERR)
                MessageBoxW(hDlg, L"Ошибка в списке", L"", MB_OK);
        } return (INT_PTR)TRUE; // end IDC_BTN_ADD
        }
    } return (INT_PTR)TRUE;
        /*
        if ((LOWORD(wParam) == IDOK) || (LOWORD(wParam) == IDCANCEL))
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }*/
        //break;
    }
    return (INT_PTR)FALSE;
}