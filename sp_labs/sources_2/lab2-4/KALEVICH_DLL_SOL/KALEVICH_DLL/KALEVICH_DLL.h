// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the KALEVICHDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// KALEVICHDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef KALEVICHDLL_EXPORTS
#define KALEVICHDLL_API __declspec(dllexport)
#else
#define KALEVICHDLL_API __declspec(dllimport)
#endif

// This class is exported from the dll
class KALEVICHDLL_API CKALEVICHDLL {
public:
	CKALEVICHDLL(void);
	// TODO: add your methods here.
};

extern KALEVICHDLL_API int g_nDllCallsCount;
extern KALEVICHDLL_API int g_nFnCallsCount;
extern KALEVICHDLL_API int nKALEVICHDLL;

KALEVICHDLL_API int fnKALEVICHDLL(void);
KALEVICHDLL_API double Fun141(int, int);
KALEVICHDLL_API int WINAPI Fun142(int, int, int);
KALEVICHDLL_API void Fun143(double in, double* out);
