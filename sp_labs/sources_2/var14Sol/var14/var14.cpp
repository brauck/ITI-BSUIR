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

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
TCHAR* buffer;
void ReadFileContent(const TCHAR* filePath);

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
bool OpenFileDialog(char* filename);
std::vector<std::string> ReadFileWithMemoryMapping(const char* filename);
void AppendNameToFile(const char* filename, const std::string& newName);
int mainFunc();
int mainFunc(HWND hWnd);

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
                mainFunc(hWnd);
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

bool OpenFileDialog(char* filename) 
{
    OPENFILENAME ofn;       // Диалоговое окно
    char szFile[MAX_PATH] = ""; // Буфер для имени файла

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Text files\0*.TXT\0All files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE) {
        strcpy_s(filename, MAX_PATH, ofn.lpstrFile);
        return true;
    }
    return false;
}

// Функция для чтения данных из файла с использованием проецирования
std::vector<std::string> ReadFileWithMemoryMapping(const char* filename) 
{
    HANDLE hFile = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening file.\n";
        return {};
    }

    // Получаем размер файла
    DWORD fileSize = GetFileSize(hFile, NULL);
    if (fileSize == INVALID_FILE_SIZE) {
        std::cerr << "Error getting file size.\n";
        CloseHandle(hFile);
        return {};
    }

    // Создаем отображение файла в память
    HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, fileSize, NULL);
    if (hMapping == NULL) {
        std::cerr << "Error creating file mapping.\n";
        CloseHandle(hFile);
        return {};
    }

    // Отображаем содержимое файла в память
    char* pMap = (char*)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, fileSize);
    if (pMap == NULL) {
        std::cerr << "Error mapping view of file.\n";
        CloseHandle(hMapping);
        CloseHandle(hFile);
        return {};
    }

    // Чтение строк из файла
    std::vector<std::string> names;
    std::string currentName;
    for (DWORD i = 0; i < fileSize; ++i) {
        if (pMap[i] == '\n') {
            if (!currentName.empty()) {
                names.push_back(currentName);
                currentName.clear();
            }
        }
        else {
            currentName += pMap[i];
        }
    }

    // Очистка ресурсов
    UnmapViewOfFile(pMap);
    CloseHandle(hMapping);
    CloseHandle(hFile);

    return names;
}

// Функция для записи новой фамилии в файл
void AppendNameToFile(const char* filename, const std::string& newName) 
{
    HANDLE hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening file.\n";
        return;
    }

    // Перемещаем курсор в конец файла
    SetFilePointer(hFile, 0, NULL, FILE_END);

    // Записываем фамилию в файл
    DWORD bytesWritten;
    WriteFile(hFile, newName.c_str(), newName.size(), &bytesWritten, NULL);
    WriteFile(hFile, "\n", 1, &bytesWritten, NULL);

    CloseHandle(hFile);
}

int mainFunc(HWND hWnd) 
{
    char filename[MAX_PATH_LENGTH];

    // Открытие файла с фамилиями
    if (!OpenFileDialog(filename)) {
        std::cerr << "No file selected.\n";
        return -1;
    }

    CreateWindowEx(0L, TEXT("Edit"), buffer,
        WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VISIBLE | WS_VSCROLL,
        20, 50, 600, 400, hWnd, (HMENU)(IDC_EDIT1),
        hInst, NULL);
    // Чтение фамилий из файла
    std::vector<std::string> names = ReadFileWithMemoryMapping(filename);

    //// Вывод фамилий на экран (можно заменить на ListBox в GUI)
    //std::cout << "Current names in file:\n";
    //for (const auto& name : names) {
    //    std::cout << name << "\n";
    //}

    //// Добавление новой фамилии
    //std::string newName;
    //std::cout << "Enter a new name to add: ";
    //std::getline(std::cin, newName);

    //// Добавляем фамилию в ListBox (или на экран)
    //std::cout << "Adding name: " << newName << "\n";

    //// Записываем фамилию в файл
    //AppendNameToFile(filename, newName);

    return 0;
}