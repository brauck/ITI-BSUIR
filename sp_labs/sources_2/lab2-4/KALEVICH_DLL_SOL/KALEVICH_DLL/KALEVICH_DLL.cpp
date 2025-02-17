// KALEVICH_DLL.cpp : Defines the exported functions for the DLL.
//
#include "framework.h"
#include "KALEVICH_DLL.h"
#include <iostream>

// Пример разделяемой переменной
#pragma data_seg(".AHARE")
KALEVICHDLL_API int g_nDllCallsCount = 0;
#pragma data_seg()

#pragma comment(linker, "/SECTION:.AHARE,RWS")

// This is an example of an exported variable
KALEVICHDLL_API int nKALEVICHDLL=17;
KALEVICHDLL_API int g_nFnCallsCount = 10;

// This is an example of an exported function.
KALEVICHDLL_API int fnKALEVICHDLL(void)
{
    return 20250117;
}

KALEVICHDLL_API double Fun141(int a, int b)
{
    return (double)a / b;
}

KALEVICHDLL_API int WINAPI Fun142(int a, int b , int c)
{
    return a + b + c;
}

KALEVICHDLL_API void Fun143(double in, double* out)
{ 
    *out = *out / in;
}

// This is the constructor of a class that has been exported.
CKALEVICHDLL::CKALEVICHDLL()
{
    return;
}
