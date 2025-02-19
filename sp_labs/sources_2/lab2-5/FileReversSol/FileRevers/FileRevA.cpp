#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "resource.h"
#include <commdlg.h> // Для диалога выбора файла

#define ID_BUTTON_OPEN 1  // ID кнопки
#define FILENAME "FILEREV.DAT"

void AnalyzeWordLengthAndAppendToFile(LPCSTR filePath);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hinstPrev, LPSTR lpszCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "FileAnalysisWin";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("FileAnalysisWin", "Word Length Distribution", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 200,
        NULL, NULL, hInst, NULL);

    CreateWindow("BUTTON", "Выбрать файл", WS_VISIBLE | WS_CHILD,
        50, 50, 150, 30, hwnd, (HMENU)ID_BUTTON_OPEN, hInst, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_BUTTON_OPEN) {
            OPENFILENAME ofn;
            char szFile[MAX_PATH] = { 0 };

            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hwnd;
            ofn.lpstrFilter = "Все файлы\0*.*\0";
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = MAX_PATH;
            ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

            if (GetOpenFileName(&ofn)) {
                AnalyzeWordLengthAndAppendToFile(szFile);
            }
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void AnalyzeWordLengthAndAppendToFile(LPCSTR filePath) {
    HANDLE hFile, hFileMap;
    LPVOID lpvFile;
    LPSTR fileContent;
    DWORD dwFileSize;
    int wordLengths[100] = { 0 };
    const DWORD wNum = 10000; // максимальное количество слов
    const DWORD lNum = 50;    // максимальное количество букв в слове

    // Проверяем переданный путь
    if (!filePath || filePath[0] == '\0') {
        MessageBox(NULL, "Ошибка: не указан путь к файлу!", "Ошибка", MB_OK);
        return;
    }

    if (!CopyFile(filePath, FILENAME, FALSE))
    {// Копирование не удалось
        MessageBoxW(NULL, L"New file could not be created.", L"FileRev", MB_OK);
        return;
    }

    // Открываем файл
    hFile = CreateFile(FILENAME, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        MessageBox(NULL, "Ошибка открытия файла.", "Ошибка", MB_OK);
        return;
    }

    // Получаем размер файла
    dwFileSize = GetFileSize(hFile, NULL);

    /*TCHAR buff[100];
    wsprintf(buff, "length %d", dwFileSize);
    MessageBox(NULL, buff, TEXT("FileRev"), MB_OK);*/

    if (dwFileSize == INVALID_FILE_SIZE || dwFileSize == 0) {
        MessageBox(NULL, "Файл пуст или ошибка при получении размера.", "Ошибка", MB_OK);
        CloseHandle(hFile);
        return;
    }

    // Создаем отображение файла в память
    hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, dwFileSize, NULL);
    if (hFileMap == NULL) {
        MessageBox(NULL, "Ошибка создания отображения файла.", "Ошибка", MB_OK);
        CloseHandle(hFile);
        return;
    }

    lpvFile = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);
    if (lpvFile == NULL) {
        MessageBox(NULL, "Ошибка маппинга файла в память.", "Ошибка", MB_OK);
        CloseHandle(hFileMap);
        CloseHandle(hFile);
        return;
    }

    // Анализируем содержимое файла
    fileContent = (LPSTR)lpvFile;
    int wordLength = 0;
    

    CHAR words[wNum][lNum] = { 0 };
    CHAR word[lNum] = { 0 };

    DWORD w = 0;
    DWORD j = 0;
    DWORD wLen = 0;

    for (int i = 0; i < dwFileSize; i++)
    {
        if (!isalpha((CHAR)fileContent[i]) && !strlen(word))
        {
            continue;
        }

        if (!isalpha((CHAR)fileContent[i]) && strlen(word))
        {
            wLen = strlen(word);
            for (int k = 0; k < wLen; k++)
            {
                words[w][k] = word[wLen - k - 1];
            }
            w++;
            j = 0;
            wLen = 0;
            memset(word, 0, sizeof(word));
            continue;
        }

        if (isalpha((CHAR)fileContent[i]))
        {
            word[j] = fileContent[i];
            j++;
        }
    }

    



   // char word[300] = { 0 };        // найденное слово
   // char tempWord[300] = { 0 };    // временное слово для реверса

   // DWORD j = 0;
   // DWORD wLen = 0; // длина слова

   //for (DWORD i = 0; i < dwFileSize; i++)
   // {
   //     //if (fileContent[i] == 0) break;
   //     if (!isalpha((CHAR)fileContent[i]) && !strlen(word))
   //     {
   //         continue;
   //     }

   //     if (!isalpha((char)fileContent[i]) && strlen(word))
   //     {
   //         wLen = strlen(word);
   //         for (DWORD k = 0; k < wLen; k++)
   //         {
   //             tempWord[k] = word[wLen - k - 1];
   //         }
   //         //cout << tempWord << ' ';
   //         j = 0;
   //         wLen = 0;
   //         memset(word, 0, sizeof(word));
   //         break;
   //         memset(tempWord, 0, sizeof(tempWord));
   //         continue;
   //     }

   //     if (isalpha((char)fileContent[i]))
   //     {
   //         word[j] = fileContent[i];
   //         j++;
   //     }
   // }

    //return;


    //========================================
    for (DWORD i = 0; i < 100; i++) {
        if (isalnum((unsigned char)fileContent[i])) { // Проверка на буквы и цифры
            wordLength++;
        }
        else if (wordLength > 0) {
            if (wordLength < 100) {
                wordLengths[wordLength]++;
            }
            wordLength = 0;
        }
    }
    if (wordLength > 0 && wordLength < 100) {
        wordLengths[wordLength]++;
    }

    // Освобождаем ресурсы
    UnmapViewOfFile(lpvFile);
    CloseHandle(hFileMap);
    CloseHandle(hFile);

    // Добавляем статистику в конец файла
    hFile = CreateFile(FILENAME, FILE_APPEND_DATA, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        MessageBox(NULL, "Ошибка открытия файла для записи.", "Ошибка", MB_OK);
        return;
    }

    DWORD written;
    CHAR buffer[lNum];

    //WriteFile(hFile, "\n\n=== Распределение слов по длине ===\n", 42, &written, NULL);

    /*for (int i = 1; i < 100; i++) {
        if (wordLengths[i] > 0) {
            sprintf_s(buffer, sizeof(buffer), "Слов длиной %d: %d\n", i, wordLengths[i]);
            WriteFile(hFile, buffer, strlen(buffer), &written, NULL);
        }
    }*/

    sprintf_s(buffer, sizeof(buffer), "\n\n--- Reveresed words ---\n");
    WriteFile(hFile, buffer, strlen(buffer), NULL, NULL);

    for (int i = 0; i < wNum; i++)
    {
        if (!words[i][0]) break;
        sprintf_s(buffer, sizeof(buffer)," %s", words[i]);
        WriteFile(hFile, buffer, strlen(buffer), &written, NULL);
    }

    WriteFile(hFile, words[5], strlen(words[5]), &written, NULL);
    CloseHandle(hFile);

    // Открываем измененный файл в Notepad
    char cmd[MAX_PATH + 20];
    sprintf_s(cmd, sizeof(cmd), "notepad.exe %s", FILENAME);

    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi;
    si.cb = sizeof(si);
    si.wShowWindow = SW_SHOW;
    si.dwFlags = STARTF_USESHOWWINDOW;

    if (!CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        MessageBox(NULL, "Ошибка запуска Notepad.", "Ошибка", MB_OK);
    }
    else {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }
}
