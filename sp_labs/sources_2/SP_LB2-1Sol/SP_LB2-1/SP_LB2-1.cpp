// Splb2-1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SP_LB2-1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];                            // имя класса главного окна
TCHAR lpszFileSpec[MAX_PATH];                                   // для открытия файла
WORD showWnd = SW_NORMAL;

// Для запуска процессов
HANDLE ProcHandle[4] = { nullptr,nullptr,nullptr,nullptr };     // для дескрипторов процессов;
DWORD ProcId[4] = { 0,0,0,0 };// для идентификаторов процессов;
HANDLE ThreadHandle[4] = { nullptr,nullptr,nullptr,nullptr };   // для дескрипторов потоков;
DWORD ThreadId[4] = { 0,0,0,0 }; // для.идентификаторов потоков;

LPCTSTR ProcImage[4] = { nullptr,
                        TEXT("C:\\Windows\\notepad.exe"),
                        TEXT("C:\\Windows\\notepad.exe"),
                        TEXT("C:\\Windows\\System32\\calc.exe") }; //для указателей строк,
                                                                   //идентифицирущих файлы запускаемых программ;

TCHAR CmdParam[4][260] = { 0,0,0,0 }; // для строк c параметрами запускаемых программ.
//////////////////////

// глобальные переменные для времени процесса
FILETIME ftKernelTimeStart[5], ftUserTimeStart[5], ftDummy[5], ftCreate[5];//для хранения времени при создании

//=====================================
// глобальные объекты для потоков
//=====================================
HANDLE hThread[3] = { nullptr,nullptr,nullptr };
DWORD dwThreadId[3] = { 0,0,0 };
DWORD g_uXPos = 20;
DWORD g_uYPos = 50;
//THREAD_PARAM ThrParam1 = { 1, g_uXPos, g_uYPos, nullptr };
//THREAD_PARAM ThrParam2 = { 2, g_uXPos, g_uYPos + 40, nullptr };
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
INT_PTR CALLBACK    DlgInfoProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    dialogTestProcess(HWND, UINT, WPARAM, LPARAM);

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

    ProcHandle[0] = GetCurrentProcess();
    ThreadHandle[0] = GetCurrentThread();
    ProcId[0] = GetCurrentProcessId();
    ThreadId[0] = GetCurrentThreadId();
    TCHAR lpFileName[260];
    GetModuleFileName(nullptr, lpFileName, sizeof(lpFileName));
    ProcImage[0] = lpFileName;

    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPLB21));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SPLB21);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

    //HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
    //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        500, 100, 600, 400, nullptr, nullptr, hInstance, nullptr);

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

            /*BOOL f = CreateProcess(TEXT("C:\\Windows\\notepad.exe"),
                nullptr,
                &sap, &sat, FALSE, 0, nullptr, nullptr, &si, &pi);*/

                //TCHAR cmdLine1[] = { 0 };
               /* lstrcpy(CmdParam[2], cmdLine1);
                BOOL f = CreateProcess(ProcImage[1], nullptr,
                    &sap, &sat, FALSE, 0, nullptr, nullptr, &si, &pi);*/
            TCHAR cmdLine1[260];
            lstrcpy(cmdLine1, ProcImage[1]);
            BOOL f = CreateProcess(nullptr, cmdLine1, //(LPTSTR) ProcImage[1],
                &sap, &sat, FALSE, 0, nullptr, nullptr, &si, &pi);

            ProcHandle[1] = pi.hProcess;
            ThreadHandle[1] = pi.hThread;
            ProcId[1] = pi.dwProcessId;
            ThreadId[1] = pi.dwThreadId;

            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }break;

        //== Блокное с текстом =======================================
        case IDM_PROC_TEXT:
        {
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

                LPCWSTR cmd = TEXT("Notepad ");
                lstrcpy(CmdParam[2], (LPTSTR)TEXT(""));
                lstrcat(CmdParam[2], cmd);
                lstrcat(CmdParam[2], ofn.lpstrFile);

            }

            STARTUPINFO si;
            ZeroMemory(&si, sizeof(STARTUPINFO));
            si.cb = sizeof(STARTUPINFO);

            PROCESS_INFORMATION pi;

            //lstrcpy(CmdParam[2], TEXT(" D:\\IIT_labs\\ITI-BSUIR\\sp_labs\\sources_2\\SP_LB2-1Sol\\SP_LB2-1\\Resource.h"));
            //BOOL f = CreateProcess(ProcImage[1], CmdParam[2],
            //    &sap, &sat, FALSE, 0, nullptr, nullptr, &si, &pi);

            BOOL f = CreateProcess(ProcImage[2], CmdParam[2], NULL,
                NULL, false, 0, NULL, NULL, &si, &pi);

            ProcHandle[2] = pi.hProcess;
            ThreadHandle[2] = pi.hThread;
            ProcId[2] = pi.dwProcessId;
            ThreadId[2] = pi.dwThreadId;

            /*CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);*/

        }break;

        //== Калькулятор =======================================
        case IDM_PROC_CALC:
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

            /*BOOL f = CreateProcess(TEXT("C:\\Windows\\notepad.exe"),
                nullptr,
                &sap, &sat, FALSE, 0, nullptr, nullptr, &si, &pi);*/

                //TCHAR cmdLine1[] = { 0 };
               /* lstrcpy(CmdParam[2], cmdLine1);
                BOOL f = CreateProcess(ProcImage[1], nullptr,
                    &sap, &sat, FALSE, 0, nullptr, nullptr, &si, &pi);*/
            TCHAR cmdLine1[260];
            lstrcpy(cmdLine1, ProcImage[3]);
            BOOL f = CreateProcess(nullptr, cmdLine1, //(LPTSTR) ProcImage[1],
                &sap, &sat, FALSE, 0, nullptr, nullptr, &si, &pi);

            ProcHandle[3] = pi.hProcess;
            ThreadHandle[3] = pi.hThread;
            ProcId[3] = pi.dwProcessId;
            ThreadId[3] = pi.dwThreadId;

            //CloseHandle(pi.hProcess);
            //CloseHandle(pi.hThread);
        }break;

        case IDM_PROC_CLOSENOTEPAD:
        {
            if (!TerminateProcess(ProcHandle[1], 6))
            {
                DWORD err = GetLastError();
                TCHAR mess[200];
                wsprintf(mess, TEXT("Ошибка вызова ТР %d 0x%X"), err, err);
                MessageBox(hWnd, mess, nullptr, MB_OK);
            }

            /*if (!TerminateProcess(ProcHandle[2], 12))
            {
                DWORD err = GetLastError();
                TCHAR mess[200];
                wsprintf(mess, TEXT("Ошибка вызова ТР %d 0x%X"), err, err);
                MessageBox(hWnd, mess, nullptr, MB_OK);
            }*/
            //TerminateProcess(ProcHandle[2], 12);
        }break;

        case IDM_PROC_CLOSETEXT:
        {
            /*if (!TerminateProcess(ProcHandle[1], 5))
            {
                DWORD err = GetLastError();
                TCHAR mess[200];
                wsprintf(mess, TEXT("Ошибка вызова ТР %d 0x%X"), err, err);
                MessageBox(hWnd, mess, nullptr, MB_OK);
            }*/

            if (!TerminateProcess(ProcHandle[2], 6))
            {
                DWORD err = GetLastError();
                TCHAR mess[200];
                wsprintf(mess, TEXT("Ошибка вызова ТР %d 0x%X"), err, err);
                MessageBox(hWnd, mess, nullptr, MB_OK);
            }
            //TerminateProcess(ProcHandle[2], 12);
        }break;

        case IDM_PROC_TEST:
        {

            DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_TESTPROC), hWnd, dialogTestProcess, 0);

        } break;

        //=== информация о процессах =================================
        case IDM_INFO_CUR:
        {
            DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgInfoProc, 0);
        }break;
        case IDM_INFO_NOTEPAD:
        {
            DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgInfoProc, 1);
        }break;
        case IDM_INFO_TEXT:
        {
            DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgInfoProc, 2);
        }break;
        case IDM_INFO_CALC:
        {
            DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgInfoProc, 3);
        }break;

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

INT_PTR CALLBACK DlgInfoProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        SetDlgItemText(hDlg, IDC_EDIT1, ProcImage[lParam]);
        TCHAR txtBuff[200];

        wsprintf(txtBuff, TEXT("0x%08X"), ProcHandle[lParam]);
        SetDlgItemText(hDlg, IDC_EDIT2, txtBuff);

        wsprintf(txtBuff, TEXT("0x%08X"), ThreadHandle[lParam]);
        SetDlgItemText(hDlg, IDC_EDIT3, txtBuff);

        wsprintf(txtBuff, TEXT("%d"), ProcId[lParam]);
        SetDlgItemText(hDlg, IDC_EDIT4, txtBuff);

        wsprintf(txtBuff, TEXT("%d"), ThreadId[lParam]);
        SetDlgItemText(hDlg, IDC_EDIT5, txtBuff);

        DWORD exitCode;
        if (!GetExitCodeProcess(ProcHandle[lParam], &exitCode))
        {
            DWORD err = GetLastError();
            wsprintf(txtBuff, TEXT("Ошибка 0x%08X"), err);
        }
        else
            if (exitCode == STILL_ACTIVE)
            {
                wsprintf(txtBuff, TEXT("Состояние - Активен"));
            }
            else
            {
                wsprintf(txtBuff, TEXT("код завершения %d"), exitCode);
            }
        SetDlgItemText(hDlg, IDC_EDIT6, txtBuff);

        DWORD thread;
        GetExitCodeThread(ThreadHandle[lParam], &thread);
        if (thread == STILL_ACTIVE)
        {
            SetDlgItemText(hDlg, IDC_EDIT7, TEXT("Состояние - Активен"));
        }
        else
        {
            SetDlgItemInt(hDlg, IDC_EDIT7, thread, true);
        }

        DWORD PriorityClass = GetPriorityClass(ProcHandle[lParam]);
        TCHAR decimalString[100];
        _itow_s(PriorityClass, decimalString, 16);//перевод из hex
        SetDlgItemText(hDlg, IDC_EDIT8, decimalString);

        FILETIME KernelTime, UserTime, CreateTime, EndTime;//переменные для определения конечного времени работы процесса
        UINT qwKernelTimeElapsed, qwUserTimeElapsed, qwTotalTimeElapsed, qwNotWorkTime;//переменные для хранения времени работы процесса
        GetProcessTimes(ProcHandle[lParam], &CreateTime, &EndTime, &KernelTime, &UserTime);

        qwTotalTimeElapsed = (&EndTime - &CreateTime);
        SetDlgItemInt(hDlg, IDC_EDIT9, qwTotalTimeElapsed, false);

        qwUserTimeElapsed = (&UserTime - &ftUserTimeStart[lParam]);
        SetDlgItemInt(hDlg, IDC_EDIT10, qwUserTimeElapsed, false);

        qwKernelTimeElapsed = (&KernelTime - &ftKernelTimeStart[lParam]);
        SetDlgItemInt(hDlg, IDC_EDIT11, qwKernelTimeElapsed, false);

        qwNotWorkTime = qwTotalTimeElapsed - (qwUserTimeElapsed + qwKernelTimeElapsed);
        SetDlgItemInt(hDlg, IDC_EDIT12, qwNotWorkTime, false);
    } return (INT_PTR)TRUE;    

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

INT_PTR CALLBACK dialogTestProcess(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_INITDIALOG: {
        SetDlgItemInt(hDlg, IDC_SIZE_X, 250, false);
        SetDlgItemInt(hDlg, IDC_SIZE_Y, 250, false);
        SetDlgItemInt(hDlg, IDC_X, 400, false);
        SetDlgItemInt(hDlg, IDC_Y, 400, false);
        CheckRadioButton(hDlg, ID_RBMAX, ID_RBNORMAL, ID_RBNORMAL);

        return (INT_PTR)TRUE;
    }
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK: {
            // Путь к приложению TestProc
            TCHAR lpszFileName[MAX_PATH] = _T("");

            // Настройка структуры OPENFILENAME
            OPENFILENAME ofn;;
            ZeroMemory(&ofn, sizeof(OPENFILENAME));
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = 0;
            ofn.lpstrFile = lpszFileName;
            ofn.lpstrTitle = _T("Запустить программу");
            ofn.nMaxFile = sizeof(lpszFileName);
            ofn.lpstrFilter = _T("Text Files (*.exe)\0*.exe\0All Files (*.*)\0*.*\0");
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            // Отображение диалогового окна
            if (!GetOpenFileName(&ofn)) return -1;

            // Настройка структуры SECURITY_ATTRIBUTES 
            SECURITY_ATTRIBUTES sa;
            sa.nLength = sizeof(SECURITY_ATTRIBUTES);
            sa.lpSecurityDescriptor = NULL;
            sa.bInheritHandle = FALSE;


            PROCESS_INFORMATION pi;
            ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

            STARTUPINFO si;

            //HWND hNormal = ID_RBNORMAL;
            /*if (Button_GetState(ID_RBNORMAL) == BST_CHECKED) {
            }*/

            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE | STARTF_USESHOWWINDOW;
            if (IsDlgButtonChecked(hDlg, ID_RBMAX) == BST_CHECKED) si.wShowWindow = SW_SHOWMAXIMIZED;
            if (IsDlgButtonChecked(hDlg , ID_RBNORMAL) == BST_CHECKED) si.wShowWindow = SW_SHOWNORMAL;
            if (IsDlgButtonChecked(hDlg, ID_RBMIN) == BST_CHECKED) si.wShowWindow = SW_SHOWMINIMIZED;
            si.dwXSize = GetDlgItemInt(hDlg, IDC_SIZE_X, NULL, false);
            si.dwYSize = GetDlgItemInt(hDlg, IDC_SIZE_Y, NULL, false);
            si.dwX = GetDlgItemInt(hDlg, IDC_X, NULL, false);
            si.dwY = GetDlgItemInt(hDlg, IDC_Y, NULL, false);


            //CreateProcess(L"D:\\С++\\SP_Lab_6Sol\\Debug\\TestProc.exe", NULL, NULL,
            //    NULL, false, 0, NULL, NULL, &si, &pi);

            /*CreateProcess(TEXT("TestProc.exe"), NULL, NULL,
                NULL, false, 0, NULL, NULL, &si, &pi);*/
            BOOL f = CreateProcess(lpszFileName, nullptr, &sa, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi);


            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
        case IDCANCEL:
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
        case ID_RBMAX:
        {
            showWnd = SW_MAXIMIZE;
            break;
        }
        case ID_RBMIN:
        {
            showWnd = SW_MINIMIZE;
            break;
        }
        case ID_RBNORMAL:
        {
            showWnd = SW_NORMAL;
            break;
        }
        }
        break;
    }
    return (INT_PTR)FALSE;
}