//Отобразить список фамилий слушателей в элементе управления «список
//(ListBox)».Список получить из текстового файла, спецификация которого задаётся
//в стандартном диалоге открытия файла.Для доступа к данным файла
//использовать технологию проецирования файлов данных на адресное
//пространство процесса.Обеспечить возможность добавления  фамилий в список
//и в файл.

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


#define FILENAME "FILEREV.DAT"

int ReverseWords(LPCSTR filePath);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

std::vector<std::string> names;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hinstPrev,
    LPSTR lpszCmdLine, int nCmdShow)
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "ReverseWords";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("ReverseWords", "Words reversing",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300, NULL, NULL, hInst, NULL);

    CreateWindow("BUTTON", "Открыть файл", WS_VISIBLE | WS_CHILD,
        80, 80, 200, 40, hwnd, (HMENU)ID_OPENFILE, hInst, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_OPENFILE)
        {
            OPENFILENAME ofn;
            char szFile[MAX_PATH] = { 0 };

            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hwnd;
            ofn.lpstrFilter = "Все файлы\0*.*\0";
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = MAX_PATH;
            ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

            if (GetOpenFileName(&ofn))
            {
                ReverseWords(szFile);
            }
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int ReverseWords(LPCSTR filePath) {
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
        sprintf_s(buffer, sizeof(buffer)," %s", words[i]);
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
