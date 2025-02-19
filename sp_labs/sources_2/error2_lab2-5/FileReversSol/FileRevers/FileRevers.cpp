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
                ofn.lpstrFilter = L"Все файлы\0*.*\0";
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
    // Объявление локальных переменных:

    HANDLE hFile;        // Для дескриптора объекта "файл"
    HANDLE hFileMap;     // Для дескриптора объекта 'проецируемый файл'
    LPVOID lpvFile;      // Для адреса региона в адресном пространстве
    // куда будет отображаться файл

    LPWSTR  lpchANSI;     // Указатель на ANSI строку
    DWORD  dwFileSize;   // Для значения размера файла 	
    STARTUPINFO si = { 0 };    // Структуры для функции
    PROCESS_INFORMATION pi;// CreateProcess 

    // Чтобы не испортить входной файл, копируем его в новый файл,
    // имя которого указываем через определенное выше макро FILENAME.

    if (!CopyFileW(fileName, FILENAME, FALSE))
    {// Копирование не удалось
        MessageBoxW(NULL, L"New file could not be created.", L"FileRev", MB_OK);
        return (0);
    }

    // Открываем файл для чтения и записи. Для этого создаем объект ядра "Файл".
    // В соответствии с указанным параметром функция CreateFile
    //  либо открывает существующий файл, либо выдает ошибку.
    //  Функция возвращает дескриптор открытогообъекта ядра,
    //  или код ошибки INVALID_HANDLE_VALUE.

    hFile = CreateFileW(
        FILENAME,  // Указатель на строку с имененм файла
        GENERIC_WRITE | GENERIC_READ, // Требуемый режим доступа
        0,   //  Режим разделения,0 - безраздельный доступ к файлу.       
        NULL,// LPSECURITY_ATTRIBUTES=0 - объект не наследуемый.
        OPEN_EXISTING,//Если файл не существует, то возвратить ошибку.
        FILE_ATTRIBUTE_NORMAL,
        NULL //Не давать имя объекту ядра "Файл"
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {  // Открыть файл не удалось
        MessageBoxW(NULL, L"File could not be opened.", L"FileRev", MB_OK);
        return(0);
    }

    // Узнаем размер файла. Второй параметр равен NULL, так как предполагается,
    // что файл меньше 4 Гб.
    dwFileSize = GetFileSize(hFile, NULL);

    TCHAR SS[100];
    
    // Создаем объект "проецируемый файл". Он - на 2 байта больше
    // размера файла, чтобы можно было записать в конец файла нулевой 
    // символ  и работать с файлом как с нуль-терминированной строкой.
    // Поскольку пока еще неизвестно содержит файл ANSI - или Unicode
    // - символы, увеличиваем файл на величину размера символа WCHAR

    hFileMap = CreateFileMappingW(
        hFile,				// Дескриптор проецирумого объекта "Файл" 
        NULL,						// LPSECURITY_ATTRIBUTES
        PAGE_READWRITE,				// Атрибуты защиты страниц 
        0,							// Старшие 32 разряда размера файла
        dwFileSize + sizeof(WCHAR),   //и младшие 32 разряда
        NULL
    );
    if (hFileMap == NULL)
    {	// Открыть объект "проецируемый файл" не удалось
        MessageBoxW(NULL, L"File map could not be opened.", L"FileRev", MB_OK);
        CloseHandle(hFile);	// Перед выходом закрываем открытые объекты
        return (0);
    }

    // Открываем отображение файла на виртуальное адресное пространство и
    // получаем адрес, начиная с которого располагается образ файла в памяти.

    lpvFile = MapViewOfFile(
        hFileMap, // Дескриптор объекта "Проецируемый файл" 
        FILE_MAP_WRITE, // Режим доступа
        0, // Старшие 32 разряда смещения от начала файла, 
        0, // младшие 32 разряда смещения от начала файла
        0  // и количество отображаемых байт. 0 означает весь файл.
    );

    if (lpvFile == NULL)
    {// Спроецировать оконное представление файла не удалось
        MessageBoxW(NULL, L"Could not map view of file.", L"FileRev", MB_OK);
        CloseHandle(hFileMap);// Перед выходом закрываем открытые объекты
        CloseHandle(hFile);
        return(0);
    }

    // Записываем в конец файла нулевой символ
    lpchANSI = (LPWSTR)lpvFile;
    lpchANSI[dwFileSize] = 0;

    //====TODO=========================================================================
    //WriteFile(hFile, "\n\n=== Распределение слов по длине ===\n", 42, NULL, NULL);
    
    LPWSTR fileContent = (LPWSTR)lpvFile;

    WCHAR word[30] = { 0 };        // найденное слово
    WCHAR tempWord[30] = { 0 };    // временное слово для реверса

    DWORD j = 0;
    DWORD wLen = 0; // длина слова

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

    // Закрываем представление файла в окне адресного пространства
    UnmapViewOfFile(lpvFile);

    // Уменьшаем счетчик ссылок на объект ядра "Проецируемый файл"
    CloseHandle(hFileMap);

    // Удаляем добавленный ранее концевой нулевой байт.Для этого
    // перемещаем указатель файла в конец на нулевой байт,
    // а затем даем команду установить в этом месте конец файла
    SetFilePointer(hFile, dwFileSize, NULL, FILE_BEGIN);
    SetEndOfFile(hFile);
    // SetEndOfFlle нужно вызывать после закрытия дескриптора объекта
    // ядра "Проецируемый файл"

    CloseHandle(hFile);// Уменьшаем счетчик ссылок на объект ядра "Файл"


    hFile = CreateFile(FILENAME, FILE_APPEND_DATA, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        MessageBox(NULL, L"Ошибка открытия файла для записи.", L"Ошибка", MB_OK);
        return 0;
    }
    //WriteFile(hFile, "\n\n=== Распределение слов по длине ===\n", 42, NULL, NULL);
    WriteFile(hFile, tempWord, wcslen(tempWord), NULL, NULL);
    CloseHandle(hFile);
     /*Запускаем NOTEPAD и загружаем в него созданный файл,
     чтобы увидеть плоды своих трудов*/
    //si.cb = sizeof(si);		// Заполняем поле размера структуры si
    //si.wShowWindow = SW_SHOW;	// Задаем режим показа окна NOTEPAD
    //si.dwFlags = STARTF_USESHOWWINDOW;	// Устанавливаем флаг - учитывать
    //// значение поля wShowWindow
    //if (CreateProcessW(NULL, (LPWSTR)L"NOTEPAD.EXE " L"FILEREV.DAT",
    //    NULL, NULL, FALSE, 0,
    //    NULL, NULL, &si, &pi))
    //{
    //    // Если процесс создан, освобождаем дескрипторы потока и процесса	
    //    CloseHandle(pi.hThread);
    //    CloseHandle(pi.hProcess);
    //}	
    return(0);
}
