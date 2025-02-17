#include "framework.h"
#include "KALEVICH_DLL_I.h"
#include "..\KALEVICH_DLL\KALEVICH_DLL.h"

#pragma comment(lib,"..\\Debug\\KALEVICHDLL.lib")
int a = 1;
int b = 2;
int c = 3;

double in = (double)c / b;
double out = fnKALEVICHDLL() / (double)nKALEVICHDLL;

// Working with imported objects
BOOL KalevichImpLoad(HWND hWnd)
{
    Fun143(in, &out);
    g_nFnCallsCount = g_nFnCallsCount + 1;
    TCHAR txt[200];
    int res = fnKALEVICHDLL();  // Call the function from Dll    
    g_nFnCallsCount = g_nFnCallsCount + 1;   //Incrementing g_nFnCalsCount variable in Dll    
    int Var1 = nKALEVICHDLL; // Call the var nKALEVICHDLL from Dll

    double Fun141res = Fun141(10, 3);
    g_nFnCallsCount = g_nFnCallsCount + 1;
    _stprintf_s(txt, 200, TEXT("НЯЗ nKALEVICHDLL = %d , Функция = %d  \n10 / 3 = %.2f \nFun142(a, b, c) = %d \nout after Fun143 = %.2f"),
        Var1, res, Fun141res, Fun142(a, b, c), out);
    g_nFnCallsCount = g_nFnCallsCount + 1;
    MessageBox(hWnd, txt, TEXT(" Клиент.Неявная загрузка"), MB_OK);

    wsprintf(txt, TEXT("НЯЗ Загрузок Dll = %d , Вызовов функций = %d  "),
        g_nDllCallsCount, g_nFnCallsCount);
    MessageBox(hWnd, txt, TEXT(" Клиент.Неявная загрузка"), MB_OK);

    res = fnKALEVICHDLL();       // Call the function from Dll
    g_nFnCallsCount = g_nFnCallsCount + 1;
    Fun141res = Fun141(res, Var1);
    g_nFnCallsCount = g_nFnCallsCount + 1;    //Incrementing g_nFnCallsCount variable in Dll
    _stprintf_s(txt, 200, TEXT("НЯЗ nKALEVICHDLL = %d , Функция = %d \nfnKALEVICHDLL /nKALEVICHDLL = %.2f"),
        Var1, res, Fun141res);
    MessageBox(hWnd, txt, TEXT(" Клиент. Неявная загрузка"), MB_OK);

    wsprintf(txt, TEXT("НЯЗ Загрузок Dll = %d , Вызовов функций = %d  "),
        g_nDllCallsCount, g_nFnCallsCount);
    MessageBox(hWnd, txt, TEXT(" Клиент. Неявная загрузка"), MB_OK);
    return TRUE;
}


