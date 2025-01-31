// KALEVICH_thread_lb.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "KALEVICH_thread_lb.h"

#define MAX_LOADSTRING 100

struct THREAD_PARAM
{
    int Num;  	 //Номер потока (1,2)
    UINT XPos; 	 //Позиция X области вывода 
    UINT YPos;	 //Позиция Y области вывода
    HWND hWnd; 	 //Дескриптор окна вывода
};

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
DWORD dwThreadId[3] = { 0,0,0 };
HANDLE hThr[3] = { nullptr,nullptr, nullptr };
DWORD g_uXPos = 10;
DWORD g_uYPos = 40;
THREAD_PARAM ThrParam1 = { 1, g_uXPos, g_uYPos, nullptr };
THREAD_PARAM ThrParam2 = { 2, g_uXPos, g_uYPos + 24, nullptr };
HANDLE hMutex;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
// Функция задержки
void for_delay(int param) {
    double x, y, z; x = 2.0; y = 3.0;
    for (int i = 0; i < param; i++) { z = x * y - 1; z = z + 1; }
}

DWORD WINAPI ThreadFunc1(PVOID pvParam);// Функция потока

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    hMutex = CreateMutex(nullptr, FALSE, TEXT("Mut1"));

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KALEVICHTHREADLB, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KALEVICHTHREADLB));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KALEVICHTHREADLB));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KALEVICHTHREADLB);
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
       CW_USEDEFAULT, 0, 500, 500, nullptr, nullptr, hInstance, nullptr);

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
        // Разобрать выбор в меню:
        switch (wmId)
        {
            //==========================================
        case IDM_TH1_CREATE:
        {
            ThrParam1.hWnd = hWnd;

            hThr[1] = CreateThread(nullptr, 0,
                ThreadFunc1, &ThrParam1, 0, &dwThreadId[1]);

        }break;
        case IDM_TH1_SUSP:
        {
            SuspendThread(hThr[1]);

        }break;
        case IDM_TH1_RESUME:
        {
            ResumeThread(hThr[1]);

        }break;
        case IDM_TH1_TERMINATE:
        {
            TerminateThread(hThr[1], 5);
        }break;




        case IDM_TH2_CREATE:
        {
            ThrParam2.hWnd = hWnd;

            hThr[2] = CreateThread(nullptr, 0,
                ThreadFunc1, &ThrParam2, 0, &dwThreadId[2]);

        }break;
        case IDM_TH2_SUSP:
        {
            SuspendThread(hThr[2]);

        }break;
        case IDM_TH2_RESUME:
        {
            ResumeThread(hThr[2]);

        }break;
        case IDM_TH2_TERMINATE:
        {
            TerminateThread(hThr[2], 5);
        }break;
        //==========================================
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
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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

// Обработчик сообщений для окна "О программе".
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


DWORD WINAPI ThreadFunc1(PVOID pvParam)
{
    THREAD_PARAM* pThrParam; //Локальная переменная для параметра
    pThrParam = (THREAD_PARAM*)pvParam;

#define MAXCHAR 100
    TCHAR CreepStr[MAXCHAR]; //Буфер для символов строки
    TCHAR buf[MAXCHAR] = { 0 }; //Рабочий буфер для циклического сдвига
    int   begIndex; // индекс начала выводимой последовательности
    int   SLen = 0; //Длина строки

    RECT  rc;
    HDC   hDC;
    int cRun = 0; //Счетчик «пробегов» строки
    int N = 3; // Размер серии из «пробегов»

    //Формирование текста бегущей строки
    wsprintf(CreepStr, TEXT("#### 90322, Петров, № %d, идентификатор - 0x%08X. >>>>>"),
        pThrParam->Num, dwThreadId[pThrParam->Num]);
    // Длинна строки
    SLen = begIndex = lstrlen(CreepStr);

    lstrcpy(buf, CreepStr);

    // Задание прямоугольной области вывода
    GetClientRect(pThrParam->hWnd, &rc);
    rc.top = pThrParam->YPos;
    rc.left = pThrParam->XPos;
    rc.right = rc.right - pThrParam->XPos;

    // Получение контекста для вывода строки		
    hDC = GetDC(pThrParam->hWnd);
    TCHAR c;
    // Бесконечный цикл вывода строк сериями по N строк
    while (TRUE)
    {
        //Взаимное исключение одновременного вывода
        //серии строк более чем одним потоком

        WaitForSingleObject(hMutex, INFINITE);
        ////////////////////////////////////////////////////
        //InvalidateRect(pThrParam->hWnd, &rc, TRUE);
        // 
            //Cдвиг символов в рабочем буфере на одну позицию
        for (int j = 0; j < SLen; j++)
        {
            for (int i = 0; i <= j; i++)//Цикл сдвига
            {
                buf[j - i] = CreepStr[SLen - i];
                TextOut(hDC, rc.left, rc.top, &buf[0], j);
            }
            Sleep(100);
        }
        //Конец цикла полного первого «пробега» строки
        ///////////////////////////////////////////////////
        cRun = 1;

        TCHAR buf1[100];
        wsprintf(buf1, TEXT("№ %d Пробегов %d"), pThrParam->Num, cRun);
        TextOut(hDC, rc.left, rc.bottom - 80 + 25 * pThrParam->Num, buf1, 14);

        while (cRun < N)//Цикл вывода серии из N-1 строк
        {

            //Цикл продвижения строки на символ слева направо
            for (int j = 0; j < SLen; j++)
            {
                //Cдвиг символов в рабочем буфере на одну позицию
                c = buf[SLen - 1];
                for (int i = SLen; i > 0; i--)//Цикл сдвига
                    buf[i] = buf[i - 1];
                buf[0] = c;

                //Ввывод строки
                TextOut(hDC, rc.left, rc.top, buf, SLen);
                Sleep(200); //приостановка потока на 200 мсек -
                // замедление "вращения" цикла
                // Альтернативный" подход - замедление "вращения" цикла 
                // без отказа от остатка кванта путем выполнения
                //        for_delay(10000000);
                // Позволяет наблюдать эффект от изменения приоритета потока. 
                // Здесь for_delay(mywait) - любая работа, занимающая 
                // процессор на некоторое время

            } //Конец цикла полного однократного «пробега» строки
            cRun++;
            wsprintf(buf1, TEXT("№ %d Пробегов %d"), pThrParam->Num, cRun);
            TextOut(hDC, rc.left, rc.bottom - 80 + 25 * pThrParam->Num, buf1, 14);
        }//Конец цикла вывода серии строк 

     //конец критического участка кода – вывод серии строк
        ReleaseMutex(hMutex);

    }
    return 0;
}
