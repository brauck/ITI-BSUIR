// FileRevers.cpp : Defines the entry point for the application.
//

#include "Windows.h"
#include "framework.h"
#include "FileRevers.h"


#define MAX_LOADSTRING 100
//#define FILENAME "FILEREV.DAT"

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
LPCWSTR FILENAME = L"FILEREV.DAT";

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
int reverseWords(LPWSTR fileName);

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
    LoadStringW(hInstance, IDC_FILEREVERS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FILEREVERS));

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
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FILEREVERS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

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
      CW_USEDEFAULT, 0, 400, 300, nullptr, nullptr, hInstance, nullptr);

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
            case IDM_OPENFILE:
            {
                OPENFILENAME ofn;
                WCHAR fileName[MAX_PATH] = { 0 };

                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = hWnd;
                ofn.lpstrFilter = L"��� �����\0*.*\0";
                ofn.lpstrFile = fileName;
                ofn.nMaxFile = MAX_PATH;
                ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

                if (GetOpenFileName(&ofn)) 
                {
                    reverseWords(fileName);
                }
            }break;
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
    //return 0;
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

int reverseWords(LPWSTR fileName)
{ 
    // ���������� ��������� ����������:

    HANDLE hFile;        // ��� ����������� ������� "����"
    HANDLE hFileMap;     // ��� ����������� ������� '������������ ����'
    LPVOID lpvFile;      // ��� ������ ������� � �������� ������������
    // ���� ����� ������������ ����

    LPWSTR  lpchANSI;     // ��������� �� ANSI ������
    DWORD  dwFileSize;   // ��� �������� ������� ����� 	
    STARTUPINFO si = { 0 };    // ��������� ��� �������
    PROCESS_INFORMATION pi;// CreateProcess 

    // ����� �� ��������� ������� ����, �������� ��� � ����� ����,
    // ��� �������� ��������� ����� ������������ ���� ����� FILENAME.

    if (!CopyFileW(fileName, FILENAME, FALSE))
    {// ����������� �� �������
        MessageBoxW(NULL, L"New file could not be created.", L"FileRev", MB_OK);
        return (0);
    }

    // ��������� ���� ��� ������ � ������. ��� ����� ������� ������ ���� "����".
    // � ������������ � ��������� ���������� ������� CreateFile
    //  ���� ��������� ������������ ����, ���� ������ ������.
    //  ������� ���������� ���������� ���������������� ����,
    //  ��� ��� ������ INVALID_HANDLE_VALUE.

    hFile = CreateFileW(
        FILENAME,  // ��������� �� ������ � ������� �����
        GENERIC_WRITE | GENERIC_READ, // ��������� ����� �������
        0,   //  ����� ����������,0 - ������������� ������ � �����.       
        NULL,// LPSECURITY_ATTRIBUTES=0 - ������ �� �����������.
        OPEN_EXISTING,//���� ���� �� ����������, �� ���������� ������.
        FILE_ATTRIBUTE_NORMAL,
        NULL //�� ������ ��� ������� ���� "����"
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {  // ������� ���� �� �������
        MessageBoxW(NULL, L"File could not be opened.", L"FileRev", MB_OK);
        return(0);
    }

    // ������ ������ �����. ������ �������� ����� NULL, ��� ��� ��������������,
    // ��� ���� ������ 4 ��.
    dwFileSize = GetFileSize(hFile, NULL);

    TCHAR SS[100];
    
    // ������� ������ "������������ ����". �� - �� 2 ����� ������
    // ������� �����, ����� ����� ���� �������� � ����� ����� ������� 
    // ������  � �������� � ������ ��� � ����-��������������� �������.
    // ��������� ���� ��� ���������� �������� ���� ANSI - ��� Unicode
    // - �������, ����������� ���� �� �������� ������� ������� WCHAR

    hFileMap = CreateFileMappingW(
        hFile,				// ���������� ������������ ������� "����" 
        NULL,						// LPSECURITY_ATTRIBUTES
        PAGE_READWRITE,				// �������� ������ ������� 
        0,							// ������� 32 ������� ������� �����
        dwFileSize + sizeof(WCHAR),   //� ������� 32 �������
        NULL
    );
    if (hFileMap == NULL)
    {	// ������� ������ "������������ ����" �� �������
        MessageBoxW(NULL, L"File map could not be opened.", L"FileRev", MB_OK);
        CloseHandle(hFile);	// ����� ������� ��������� �������� �������
        return (0);
    }

    // ��������� ����������� ����� �� ����������� �������� ������������ �
    // �������� �����, ������� � �������� ������������� ����� ����� � ������.

    lpvFile = MapViewOfFile(
        hFileMap, // ���������� ������� "������������ ����" 
        FILE_MAP_WRITE, // ����� �������
        0, // ������� 32 ������� �������� �� ������ �����, 
        0, // ������� 32 ������� �������� �� ������ �����
        0  // � ���������� ������������ ����. 0 �������� ���� ����.
    );

    if (lpvFile == NULL)
    {// ������������� ������� ������������� ����� �� �������
        MessageBoxW(NULL, L"Could not map view of file.", L"FileRev", MB_OK);
        CloseHandle(hFileMap);// ����� ������� ��������� �������� �������
        CloseHandle(hFile);
        return(0);
    }

    // ���������� � ����� ����� ������� ������
    lpchANSI = (LPWSTR)lpvFile;
    lpchANSI[dwFileSize] = 0;

    //====TODO=========================================================================
    //WriteFile(hFile, "\n\n=== ������������� ���� �� ����� ===\n", 42, NULL, NULL);
    
    LPWSTR fileContent = (LPWSTR)lpvFile;

    WCHAR word[30] = { 0 };        // ��������� �����
    WCHAR tempWord[30] = { 0 };    // ��������� ����� ��� �������

    DWORD j = 0;
    DWORD wLen = 0; // ����� �����

    /*wcslen(word);
    if (!iswalpha((wint_t)fileContent[0]) && !wcslen(word));*/

    for (DWORD i = 0; i < dwFileSize; i++)
    {
        if (!iswalpha((wint_t)fileContent[i]) && !wcslen(word))
        {
            continue;
        }

        if (!iswalpha((wint_t)fileContent[i]) && wcslen(word))
        {
            wLen = wcslen(word);
            for (DWORD k = 0; k < wLen; k++)
            {
                tempWord[k] = word[wLen - k - 1];
            }
            //cout << tempWord << ' ';
            j = 0;
            wLen = 0;
            memset(word, 0, sizeof(word));
            break;
            memset(tempWord, 0, sizeof(tempWord));
            continue;
        }

        if (iswalpha((wint_t)fileContent[i]))
        {
            word[j] = fileContent[i];
            j++;
        }
    }

    //return 0;
    //===END TODO=====================================================================

    // ��������� ������������� ����� � ���� ��������� ������������
    UnmapViewOfFile(lpvFile);

    // ��������� ������� ������ �� ������ ���� "������������ ����"
    CloseHandle(hFileMap);

    // ������� ����������� ����� �������� ������� ����.��� �����
    // ���������� ��������� ����� � ����� �� ������� ����,
    // � ����� ���� ������� ���������� � ���� ����� ����� �����
    SetFilePointer(hFile, dwFileSize, NULL, FILE_BEGIN);
    SetEndOfFile(hFile);
    // SetEndOfFlle ����� �������� ����� �������� ����������� �������
    // ���� "������������ ����"

    CloseHandle(hFile);// ��������� ������� ������ �� ������ ���� "����"


    hFile = CreateFile(FILENAME, FILE_APPEND_DATA, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        MessageBox(NULL, L"������ �������� ����� ��� ������.", L"������", MB_OK);
        return 0;
    }
    //WriteFile(hFile, "\n\n=== ������������� ���� �� ����� ===\n", 42, NULL, NULL);
    WriteFile(hFile, tempWord, wcslen(tempWord), NULL, NULL);
    CloseHandle(hFile);
     /*��������� NOTEPAD � ��������� � ���� ��������� ����,
     ����� ������� ����� ����� ������*/
    //si.cb = sizeof(si);		// ��������� ���� ������� ��������� si
    //si.wShowWindow = SW_SHOW;	// ������ ����� ������ ���� NOTEPAD
    //si.dwFlags = STARTF_USESHOWWINDOW;	// ������������� ���� - ���������
    //// �������� ���� wShowWindow
    //if (CreateProcessW(NULL, (LPWSTR)L"NOTEPAD.EXE " L"FILEREV.DAT",
    //    NULL, NULL, FALSE, 0,
    //    NULL, NULL, &si, &pi))
    //{
    //    // ���� ������� ������, ����������� ����������� ������ � ��������	
    //    CloseHandle(pi.hThread);
    //    CloseHandle(pi.hProcess);
    //}	
    return(0);
}
