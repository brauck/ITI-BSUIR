// KALEVICH_DLL.cpp : Defines the exported functions for the DLL.
//

#include "framework.h"
#include "KALEVICH_DLL.h"


// This is an example of an exported variable
KALEVICHDLL_API int nKALEVICHDLL=0;

// This is an example of an exported function.
KALEVICHDLL_API int fnKALEVICHDLL(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CKALEVICHDLL::CKALEVICHDLL()
{
    return;
}
