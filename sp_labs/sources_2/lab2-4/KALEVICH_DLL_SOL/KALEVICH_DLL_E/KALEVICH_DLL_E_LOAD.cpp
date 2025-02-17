#include "framework.h"
#include "KALEVICH_DLL_E.h"

int a = 1;
int b = 2;
int c = 3;

// Явная загрузка
BOOL DllExplicitLoading(HWND hWnd)
{
    TCHAR txt[200];
    // wsprintf(txt, TEXT("Переменная = %d , Функция = %d"), nSpLb24, fnSpLb24());
    // MessageBox(hWnd, txt, TEXT("Вызов из Dll"), MB_OK);
    MessageBox(hWnd, TEXT("Явная загрузка Dll SPLB24.dll"),
        TEXT("Вызов из клиента с явной загрукой"), MB_OK);

    HINSTANCE hDll = nullptr;       // Handle to DLL
    hDll = LoadLibrary(TEXT("KALEVICHDLL.dll"));
    if (hDll == NULL) {// Error Loading Dll
        MessageBox(hWnd, TEXT("Модуль KALEVICHDLL.dll не найден"), TEXT("Ошибка загрузки Dll"), MB_OK);
        return FALSE;
    }
    //=======================================================================
    // связывание с импортируемыми объектами из SpLb24.dll 

    // Функция fnKALEVICHDLL. Имя не декорировано
    typedef INT(*LPFNTYPE)(VOID);   // Function pointer type
    LPFNTYPE lpfnDllFunc1;          // Function pointer
    lpfnDllFunc1 = (LPFNTYPE)GetProcAddress(hDll, "fnKALEVICHDLL");
    if (!lpfnDllFunc1) { // the error
        FreeLibrary(hDll);
        MessageBox(hWnd, TEXT("Не найдена fnKALEVICHDLL"), TEXT("Вызов GPA"), MB_OK);
        return FALSE;
    }

    // Функция Fun141. Имя не декорировано
    typedef double (*fun141_ptr)(int, int);
    fun141_ptr lpfnDllFun141;          // Function pointer
    lpfnDllFun141 = (fun141_ptr)GetProcAddress(hDll, "Fun141");
    if (!lpfnDllFun141) { // the error
        FreeLibrary(hDll);
        MessageBox(hWnd, TEXT("Не найдена lpfnDllFun141"), TEXT("Вызов GPA"), MB_OK);
        return FALSE;
    }

    // Функция Fun142. Имя не декорировано  
    typedef int (WINAPI *fun142_ptr)(int, int, int);
    fun142_ptr lpfnDllFun142;          // Function pointer
    lpfnDllFun142 = (fun142_ptr)GetProcAddress(hDll, "Fun142");
    if (!lpfnDllFun142) { // the error
        FreeLibrary(hDll);
        MessageBox(hWnd, TEXT("Не найдена lpfnDllFun142"), TEXT("Вызов GPA"), MB_OK);
        return FALSE;
    }

    // Функция Fun143. Имя не декорировано
    typedef void (*fun143_ptr)(double, double*);
    fun143_ptr lpfnDllFun143;          // Function pointer
    lpfnDllFun143 = (fun143_ptr)GetProcAddress(hDll, "Fun143");
    if (!lpfnDllFun143) { // the error
        FreeLibrary(hDll);
        MessageBox(hWnd, TEXT("Не найдена lpfnDllFun143"), TEXT("Вызов GPA"), MB_OK);
        return FALSE;
    }

    // Var nKALEVICHDLL. Имя не декорировано
    int* pVar1 = (int*)GetProcAddress(hDll, "nKALEVICHDLL");
    if (!pVar1) { // the error
        FreeLibrary(hDll);
        MessageBox(hWnd, TEXT("Не найдена nKALEVICHDLL"), TEXT("Вызов GPA"), MB_OK);
        return FALSE;
    }

    // Var g_nDllCallsCount. Декорированное имя
    int* pDllCount = (int*)GetProcAddress(hDll, "?g_nDllCallsCount@@3HA");
    if (!pDllCount) { // the error
        FreeLibrary(hDll);
        MessageBox(hWnd, TEXT("Не найдена g_nDllCallsCount"), TEXT("Вызов GPA"), MB_OK);
        return FALSE;
    }

    // Var g_nFnCallsCount. Связывание по ординалу 
    int* pFnCalls = (int*)GetProcAddress(hDll, (LPCSTR)MAKEINTRESOURCE(10));
    if (!pFnCalls) { // the error
        FreeLibrary(hDll);
        MessageBox(hWnd, TEXT("Не найдена g_nFnCallsCount"), TEXT("Вызов GPA"), MB_OK);
        return FALSE;
    }
    //==========================================================================
    // Working with imported objects
    double in = (double)c / b;
    double out = lpfnDllFunc1() / (double)*pVar1;
    lpfnDllFun143(in, &out);
    *pFnCalls = *pFnCalls + 1;

    double Fun141res = lpfnDllFun141(10, 3);
    *pFnCalls = *pFnCalls + 1;
    int res = lpfnDllFunc1();  // Call the function from Dll
    *pFnCalls = *pFnCalls + 1;   //Incrementing g_nFnCallsCount variable in Dll    
    int Var1 = *pVar1; // Call the var nSpLb24 from Dll

    _stprintf_s(txt, 200, TEXT("ЯЗ nKALEVICHDLL = %d , Функция = %d\n10 / 3 = %.2f\nFun142(a, b, c) = %d\nout after Fun143 = %.2f"),
        Var1, res, Fun141res, lpfnDllFun142(a, b, c), out);
    *pFnCalls = *pFnCalls + 1;
    MessageBox(hWnd, txt, TEXT(" Клиент. Явная загрузка"), MB_OK);

    wsprintf(txt, TEXT("ЯЗ Загрузок Dll = %d , Вызовов функций = %d  "), *pDllCount, *pFnCalls);
    MessageBox(hWnd, txt, TEXT(" Клиент. Явная загрузка"), MB_OK);

    res = lpfnDllFunc1();       // Call the function from Dll
    *pFnCalls = *pFnCalls + 1;    //Incrementing g_nFnCalsCount variable in Dll
    wsprintf(txt, TEXT("ЯЗ nKALEVICHDLL = %d , Функция = %d  "), Var1, res);
    MessageBox(hWnd, txt, TEXT(" Клиент. Явная загрузка"), MB_OK);

    wsprintf(txt, TEXT("ЯЗ Загрузок Dll = %d , Вызовов функций = %d  "), *pDllCount, *pFnCalls);
    MessageBox(hWnd, txt, TEXT(" Клиент. Явная загрузка"), MB_OK);

    FreeLibrary(hDll);
    return TRUE;
}