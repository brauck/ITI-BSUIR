// KALEVICH_DLL.cpp : Defines the exported functions for the DLL.
//

#include "framework.h"
#include "KALEVICH_DLL.h"


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

// This is the constructor of a class that has been exported.
CKALEVICHDLL::CKALEVICHDLL()
{
    return;
}
