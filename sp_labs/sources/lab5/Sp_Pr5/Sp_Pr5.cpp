// Sp_Pr5.cpp : Defines the entry point for the application.
//

#include "Sp_Pr5.h"

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR retMessage[textBufferSize] = {};
wchar_t pszFileTextBuff[fileBufferSize] = {};


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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
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
        HANDLE_MSG(hWnd, WM_COMMAND, WndProc_OnCommand);
        HANDLE_MSG(hWnd, WM_PAINT, WndProc_OnPaint);
        HANDLE_MSG(hWnd, WM_DESTROY, WndProc_OnDestroy);
    }
    return DefWindowProcW(hWnd, message, wParam, lParam);
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        HANDLE_MSG(hDlg, WM_INITDIALOG, About_OnInitDialog);
        HANDLE_MSG(hDlg, WM_COMMAND, About_OnCommand);
    }
    return (INT_PTR)FALSE;
}

// Message handler for ������ ���� "� ���������" box.
INT_PTR CALLBACK DlgAbout1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        HANDLE_MSG(hDlg, WM_INITDIALOG, DlgAbout1_OnInitDialog);
        HANDLE_MSG(hDlg, WM_COMMAND, DlgAbout1_OnCommand);
    }
    return (INT_PTR)FALSE;
}

// Message handler for "������ ��������� ���������� � ���������� ����" box.
INT_PTR CALLBACK DlgCtls(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        HANDLE_MSG(hDlg, WM_INITDIALOG, DlgAbout1_OnInitDialog);

    
        HANDLE_MSG(hDlg, WM_COMMAND, DlgCtls_OnCommand);
       /* int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);
        static wchar_t pszTextBuff[textBufferSize] = {};
        switch (wmId)
        {
        case IDCANCEL:
        {
            EndDialog(hDlg, LOWORD(wParam));
        } return (INT_PTR)TRUE;

        case IDOK:
        { // ����� ��������� ������
            GetDlgItemTextW(hDlg, IDC_EDIT1, retMessage, textBufferSize);
            EndDialog(hDlg, LOWORD(wParam));
        } return (INT_PTR)TRUE;

        case IDC_BUTTON1: // BTN_SAVE � ������
        {
            int cch;
            HWND hEdit = GetDlgItem(hDlg, IDC_EDIT1);
            cch = SendMessageW(hEdit, WM_GETTEXT, (WPARAM)textBufferSize, (LPARAM)pszTextBuff);
            if (cch == 0)
            {
                MessageBoxW(hDlg, L"������� �����", L"������ Edit", MB_OK);
                return (INT_PTR)TRUE;
            }
            else if (WM_GETTEXT > textBufferSize)
            {
                MessageBoxW(hDlg, L"��������� ������������ ����� ������", L"������ Edit", MB_OK | MB_ICONERROR);
                return (INT_PTR)TRUE;
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
        } return (INT_PTR)TRUE; //IDC_BTN_SAVE

        case IDC_BUTTON2: // BTN_ADD
        {
            int ind;
            HWND hListBox = GetDlgItem(hDlg, IDC_LIST1);
            ind = SendMessageW(hListBox, LB_ADDSTRING,
                (WPARAM)0, (LPARAM)pszTextBuff);
            if (ind == LB_ERR)
                MessageBoxW(hDlg, L"������ � ������", L"", MB_OK);
        } return (INT_PTR)TRUE; // end IDC_BTN_ADD
        }*/
    

    }
    return (INT_PTR)FALSE;
}

// Message handler for "�������� ���������� �����" box.
INT_PTR CALLBACK DlgTextView(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    
    switch (message)
    {
        HANDLE_MSG(hDlg, WM_INITDIALOG, DlgTextView_OnInitDialog);
        HANDLE_MSG(hDlg, WM_COMMAND, DlgTextView_OnCommand);   
    }
    return (INT_PTR)FALSE;
}