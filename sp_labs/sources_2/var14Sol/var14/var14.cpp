// var14.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "resource.h"
#include <commdlg.h>
#include <iostream>
#include <vector>
#include <string>
#include "var14.h"

#define MAX_LOADSTRING 100
#define MAX_PATH_LENGTH 260

#define FILENAME "FILEREV.DAT"
std::vector<std::string> names;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
TCHAR buffer[10000] = {};
//TCHAR* buffer;                                  // file content
DWORD bytesRead;
DWORD fileSize2;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
bool OpenFileDialog(char* filename);
int ReadFileWithMemoryMapping(HWND hWnd, LPCSTR filePath);
void AppendNameToFile(const char* filename, const std::string& newName);

void ReadFileContent(HWND hWnd, const TCHAR* filePath);

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
    LoadStringW(hInstance, IDC_VAR14, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VAR14));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VAR14));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_VAR14);
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

   CreateWindow("BUTTON", "Открыть файл", WS_VISIBLE | WS_CHILD,
       20, 10, 200, 40, hWnd, (HMENU)ID_OPENFILE, hInst, NULL);

   /*CreateWindowEx(0L, TEXT("Edit"), buffer,
       WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VISIBLE | WS_VSCROLL,
       20, 50, 600, 400, hWnd, (HMENU)(IDC_EDIT1),
       hInst, NULL);*/

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
            case ID_OPENFILE:
            {
                OPENFILENAME ofn;
                char szFile[MAX_PATH] = { 0 };

                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = hWnd;
                ofn.lpstrFilter = "Все файлы\0*.*\0";
                ofn.lpstrFile = szFile;
                ofn.nMaxFile = MAX_PATH;
                ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

                if (GetOpenFileName(&ofn))
                {
                    //ReadFileContent(hWnd, szFile);
                    ReadFileWithMemoryMapping(hWnd, szFile);
                    //ReverseWords(szFile);
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

// Функция для чтения данных из файла с использованием проецирования
int ReadFileWithMemoryMapping(HWND hWnd, LPCSTR filePath)
{
    HANDLE hFile, hFileMap;
    LPVOID lpvFile;
    LPSTR fileContent;
    DWORD dwFileSize;
    int wordLengths[100] = { 0 };
    const DWORD wNum = 10000; // максимальное количество слов
    const DWORD lNum = 50;    // максимальное количество букв в слове

    if (!CopyFile(filePath, FILENAME, FALSE))
    {// Копирование не удалось
        MessageBox(NULL, "New file could not be created.", "FileRev", MB_OK);
        return 0;
    }

    // Открываем файл для чтения и записи. Для этого создаем объект ядра "Файл".
    hFile = CreateFile(
        FILENAME, GENERIC_READ | GENERIC_WRITE,
        0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        MessageBox(NULL, "File could not be opened.", "FileRev", MB_OK);
        return 0;
    }

    // Узнаем размер файла. Второй параметр равен NULL, так как предполагается,
    // что файл меньше 4 Гб.
    dwFileSize = GetFileSize(hFile, NULL);
    //fileSize2 = dwFileSize;
    if (dwFileSize == INVALID_FILE_SIZE || dwFileSize == 0) {
        MessageBox(NULL, "File is empty or error occured.", "FileRev", MB_OK);
        CloseHandle(hFile);
        return 0;
    }

    // Создаем объект "проецируемый файл".
    hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, dwFileSize, NULL);
    if (hFileMap == NULL) {
        MessageBox(NULL, "File map could not be opened.", "FileRev", MB_OK);
        CloseHandle(hFile);
        return 0;
    }

    // Открываем отображение файла на виртуальное адресное пространство и
    // получаем адрес, начиная с которого располагается образ файла в памяти.
    lpvFile = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);
    if (lpvFile == NULL) {
        MessageBox(NULL, "Could not map view of file.", "FileRev", MB_OK);
        CloseHandle(hFileMap);
        CloseHandle(hFile);
        return 0;
    }

    //===TODO=============================================================
    fileContent = (LPSTR)lpvFile;

    CHAR words[wNum][lNum] = { 0 };
    CHAR word[lNum] = { 0 };

    DWORD w = 0;    // индекс слова
    DWORD j = 0;    // индекс буквы
    DWORD wLen = 0; // длина слова

    for (int i = 0; i < dwFileSize; i++)
    {
        if (!isalpha((BYTE)fileContent[i]) && !strlen(word))
        {
            continue;
        }

        if (!isalpha((BYTE)fileContent[i]) && strlen(word))
        {
            wLen = strlen(word);
            for (int k = 0; k < wLen; k++)
            {
                words[w][k] = word[wLen - k - 1]; // reverse
            }
            w++;
            j = 0;
            wLen = 0;
            memset(word, 0, sizeof(word));
            continue;
        }

        if (isalpha((BYTE)fileContent[i]))
        {
            word[j] = fileContent[i];
            j++;
        }
    }
    //===END TODO================================================================

    // Закрываем представление файла в окне адресного пространства
    UnmapViewOfFile(lpvFile);

    // Уменьшаем счетчик ссылок на объект ядра "Проецируемый файл"
    CloseHandle(hFileMap);

    // Уменьшаем счетчик ссылок на объект ядра "Файл"
    CloseHandle(hFile);

    // Записываем обработанные данные в конец файла
    hFile = CreateFile(FILENAME, FILE_APPEND_DATA, 0, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    
    ReadFileContent(hWnd, FILENAME);

    if (hFile == INVALID_HANDLE_VALUE) {
        MessageBox(NULL, "File could not be opened.", "FileRev", MB_OK);
        return 0;
    }

    CHAR buffer[lNum];

    sprintf_s(buffer, sizeof(buffer), "\n\n--- Reveresed words ---\n\n");
    WriteFile(hFile, buffer, strlen(buffer), NULL, NULL);

    for (int i = 0; i < wNum; i++)
    {
        if (!words[i][0]) break;
        sprintf_s(buffer, sizeof(buffer), " %s", words[i]);
        WriteFile(hFile, buffer, strlen(buffer), NULL, NULL);
    }

    CloseHandle(hFile);

    // Запускаем NOTEPAD и загружаем в него созданный файл
    char cmd[MAX_PATH + 20];
    sprintf_s(cmd, sizeof(cmd), "notepad.exe %s", FILENAME);

    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi;
    si.cb = sizeof(si);
    si.wShowWindow = SW_SHOW;
    si.dwFlags = STARTF_USESHOWWINDOW;

    if (CreateProcess(NULL, cmd, NULL, NULL,
        FALSE, 0, NULL, NULL, &si, &pi))
    {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }
}

void ReadFileContent(HWND hWnd ,const TCHAR* filePath) 
{
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

    TCHAR *buffer = new TCHAR[fileSize + 1];

    if (!ReadFile(hFile, buffer, fileSize2, &bytesRead, NULL)) {
        MessageBox(NULL, _T("Ошибка при чтении файла!"), _T("Ошибка"), MB_OK | MB_ICONERROR);
        delete[] buffer;
        CloseHandle(hFile);
        return;
    }

    buffer[bytesRead / sizeof(TCHAR)] = '\0';

    if (!(CreateWindowEx(0L, TEXT("Edit"), buffer,
        WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VISIBLE | WS_VSCROLL,
        20, 50, 600, 400, hWnd, (HMENU)(IDC_EDIT1),
        hInst, NULL)));
    if (!(CreateWindowEx(0L, TEXT("Edit"), buffer,
        WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VISIBLE | WS_VSCROLL,
        20, 50, 600, 400, hWnd, (HMENU)(IDC_EDIT1),
        hInst, NULL)));
    CloseHandle(hFile);

    
}