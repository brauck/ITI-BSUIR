// ReadTextFile.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ReadTextFile.h"

#define MAX_LOADSTRING 100
#define IDC_EDIT1			150
static HWND hEdit;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

TCHAR* buffer;                                  // file content
DWORD bytesRead;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void ReadFileContent(const TCHAR* filePath);

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
    LoadStringW(hInstance, IDC_READTEXTFILE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_READTEXTFILE));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_READTEXTFILE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_READTEXTFILE);
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
      CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

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
    case WM_CREATE:
    {
        TCHAR lpszFileSpec[MAX_PATH];
        TCHAR CmdParam[260] = {};
        TCHAR pp[260] = TEXT("D:\\test.txt");

        SECURITY_ATTRIBUTES sap, sat;//стр. атр. безоп. проц. и потока
        sap.nLength = sizeof(SECURITY_ATTRIBUTES);
        sap.lpSecurityDescriptor = nullptr;
        sap.bInheritHandle = FALSE;

        sat.nLength = sizeof(SECURITY_ATTRIBUTES);
        sat.lpSecurityDescriptor = nullptr;
        sat.bInheritHandle = FALSE;

        OPENFILENAME ofn;
        ZeroMemory(&ofn, sizeof(OPENFILENAME));

        //HANDLE hFile;

        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = hWnd;
        ofn.lpstrFile = lpszFileSpec;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(lpszFileSpec);
        ofn.lpstrFilter = TEXT("All\0*.*\0Text\0*.txt\0");
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetOpenFileName(&ofn)) {

            LPCTSTR cmd = TEXT("Notepad ");
            lstrcpy(CmdParam, (LPTSTR)TEXT(""));
            lstrcat(CmdParam, cmd);
            lstrcat(CmdParam, ofn.lpstrFile);
        }

        STARTUPINFO si;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);

        PROCESS_INFORMATION pi;

        if (CreateProcess(TEXT("C:\\Windows\\notepad.exe"), CmdParam,
            &sap, &sat, FALSE, 0, nullptr, nullptr, &si, &pi))
        {
            // Ждать пока блокнот закроется
            DWORD waitResult = WaitForSingleObject(pi.hProcess, INFINITE);

            // Проверка результата ожидания
            switch (waitResult) {
            case WAIT_OBJECT_0: {
                // Успешно
                // Закрыть дескрипторы
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);

                // Считать содержимое файла
                ReadFileContent(ofn.lpstrFile);

                if (!(hEdit = CreateWindowEx(0L, TEXT("Edit"), buffer,
                    WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VISIBLE | WS_VSCROLL,
                    20, 50, 600, 400, hWnd, (HMENU)(IDC_EDIT1),
                    hInst, NULL))) return (-1);
            } break;
            case WAIT_TIMEOUT: {
                MessageBox(NULL, _T("Время ожидания истекло!"), _T("Ошибка"), MB_OK | MB_ICONERROR);
            } break;
            case WAIT_ABANDONED: {
                MessageBox(NULL, _T("Мьютекс оставлен без владельца!"), _T("Ошибка"), MB_OK | MB_ICONERROR);
            } break;
            case WAIT_FAILED: {
                DWORD lastError = GetLastError();
                TCHAR errMess[MAX_PATH];
                wsprintf(errMess, _T("Сбой функции ожидания: %X"), lastError);
                MessageBox(NULL, errMess, _T("Ошибка"), MB_OK | MB_ICONERROR);
            } break;
            default: {
                DWORD lastError = GetLastError();
                TCHAR errMess[MAX_PATH];
                wsprintf(errMess, _T("Произошла ошибка ожидания: %X"), lastError);
                MessageBox(NULL, errMess, _T("Ошибка"), MB_OK | MB_ICONERROR);
            } break;
            }
        }
    } break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
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

void ReadFileContent(const TCHAR* filePath) {
    HANDLE hFile = CreateFile(filePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        MessageBox(NULL, _T("Ошибка при открытии файла!"), _T("Ошибка"), MB_OK | MB_ICONERROR);
        return;
    }

    DWORD fileSize;
    fileSize = GetFileSize(hFile, NULL);
    if (fileSize == INVALID_FILE_SIZE) {
        MessageBox(NULL, _T("Ошибка при определении размера файла!"), _T("Ошибка"), MB_OK | MB_ICONERROR);
        CloseHandle(hFile);
        return;
    }

    buffer = new TCHAR[fileSize + 1];

    if (!ReadFile(hFile, buffer, fileSize, &bytesRead, NULL)) {
        MessageBox(NULL, _T("Ошибка при чтении файла!"), _T("Ошибка"), MB_OK | MB_ICONERROR);
        delete[] buffer;
        CloseHandle(hFile);
        return;
    }

    buffer[bytesRead / sizeof(TCHAR)] = '\0';

    CloseHandle(hFile);
}