// Splb2-1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Splb2-1.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Глобальные переменные:
HINSTANCE hInst;                                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];                            // имя класса главного окна

// Для запуска процессов
HANDLE ProcHandle[4] = { nullptr,nullptr,nullptr,nullptr };     // для дескрипторов процессов;
DWORD ProcId[4] = { 0,0,0,0 };// для идентификаторов процессов;
HANDLE ThreadHandle[4] = { nullptr,nullptr,nullptr,nullptr };   // для дескрипторов потоков;
DWORD ThreadId[4] = { 0,0,0,0 }; // для.идентификаторов потоков;

LPCTSTR ProcImage[4] = { nullptr,
                        TEXT("C:\\Windows\\notepad.exe"),
                        nullptr,
                        TEXT("C:\\Windows\\System32\\calc.exe") }; //для указателей строк,
//идентифицирущих файлы запускаемых программ;

TCHAR CmdParam[4][260] = { 0,0,0,0 };// для строк c параметрами запускаемых программ.
//////////////////////
// глобальные объекты для потоков
//=====================================
HANDLE hThread[3] = { nullptr,nullptr,nullptr };
DWORD dwThreadId[3] = { 0,0,0 };
DWORD g_uXPos = 20;
DWORD g_uYPos = 50;
THREAD_PARAM ThrParam1 = { 1, g_uXPos, g_uYPos, nullptr };
THREAD_PARAM ThrParam2 = { 2, g_uXPos, g_uYPos + 40, nullptr };
BOOL fSin = FALSE;

// Для синхронизации
HANDLE g_hMutex = nullptr;
BOOL fSyn = FALSE;
HANDLE g_hSemaphore = nullptr;
HANDLE g_hEvent = nullptr;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_SPLB21, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPLB21));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPLB21));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SPLB21);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
            //== Обработка команд меню ====================================
            //== ПРОЦЕССЫ =================================================
            case IDM_PROC_NOTEPAD:
            {
                SECURITY_ATTRIBUTES sap, sat;//стр. атр. безоп. проц. и потока
                sap.nLength = sizeof(SECURITY_ATTRIBUTES);
                sap.lpSecurityDescriptor = nullptr;
                sap.bInheritHandle = FALSE;

                sat.nLength = sizeof(SECURITY_ATTRIBUTES);
                sat.lpSecurityDescriptor = nullptr;
                sat.bInheritHandle = FALSE;

                STARTUPINFO si;
                ZeroMemory(&si, sizeof(STARTUPINFO));
                si.cb = sizeof(STARTUPINFO);

                PROCESS_INFORMATION pi;

                //TCHAR cmdLine1[] = { 0 };
                //lstrcpy(CmdParam[2], cmdLine1);
                BOOL f = CreateProcess(ProcImage[1], nullptr,
                    &sap, &sat, FALSE, 0, nullptr, nullptr, &si, &pi);

                ProcHandle[1] = pi.hProcess;
                ThreadHandle[1] = pi.hThread;
                ProcId[1] = pi.dwProcessId;
                ThreadId[1] = pi.dwThreadId;

                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);

            }break;
            //============================================================
            //============================================================
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
