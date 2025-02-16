#include "framework.h"
#include "KALEVICH_DLL_I.h"
#include "..\KALEVICH_DLL\KALEVICH_DLL.h"

#pragma comment(lib,"..\\Debug\\KALEVICHDLL.lib")

// Working with imported objects
BOOL KalevichImpLoad(HWND hWnd)
{
    TCHAR txt[200];
    int res = fnKALEVICHDLL();  // Call the function from Dll
    g_nFnCallsCount = g_nFnCallsCount + 1;   //Incrementing g_nFnCalsCount variable in Dll    
    int Var1 = nKALEVICHDLL; // Call the var nKALEVICHDLL from Dll

    wsprintf(txt, TEXT("НЯЗ nKALEVICHDLL = %d , Функция = %d  "), Var1, res);
    MessageBox(hWnd, txt, TEXT(" Клиент.Неявная загрузка"), MB_OK);

    wsprintf(txt, TEXT("НЯЗ Загрузок Dll = %d , Вызовов функций = %d  "),
        g_nDllCallsCount, g_nFnCallsCount);
    MessageBox(hWnd, txt, TEXT(" Клиент.Неявная загрузка"), MB_OK);

    res = fnKALEVICHDLL();       // Call the function from Dll
    g_nFnCallsCount = g_nFnCallsCount + 1;    //Incrementing g_nFnCallsCount variable in Dll
    wsprintf(txt, TEXT("НЯЗ nSpLb24 = %d , Функция = %d  "), Var1, res);
    MessageBox(hWnd, txt, TEXT(" Клиент. Неявная загрузка"), MB_OK);

    wsprintf(txt, TEXT("НЯЗ Загрузок Dll = %d , Вызовов функций = %d  "),
        g_nDllCallsCount, g_nFnCallsCount);
    MessageBox(hWnd, txt, TEXT(" Клиент. Неявная загрузка"), MB_OK);
    return TRUE;
}
