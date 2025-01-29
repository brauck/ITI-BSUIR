// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"
#include "KALEVICH_DLL.h"
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {// инициализация DLL
        MessageBox(nullptr, TEXT("Загружается DLL KALEVICH_DLL"), TEXT("Из DllMain"), MB_OK);
        g_nDllCallsCount = g_nDllCallsCount + 1;
    } return TRUE;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
    { // деинициализация
        MessageBox(nullptr, TEXT("Выгружается DLL KALEVICH_DLL"), TEXT("Из DllMain"), MB_OK);

    } break;
    }
    return TRUE;
}

