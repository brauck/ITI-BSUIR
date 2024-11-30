
#include "SpPr7.h"

HFONT APIENTRY MyFontCreate2(HWND hWnd,HDC hDcText)
{
    LOGFONT lf;
    ZeroMemory(&lf, sizeof(lf));
    lf.lfCharSet = RUSSIAN_CHARSET;
    lf.lfHeight = -MulDiv(14, GetDeviceCaps(hDcText, LOGPIXELSY), 72);
    lf.lfOrientation = 200;

    lf.lfFaceName;
    HRESULT hr = StringCchCopy(lf.lfFaceName, 16, TEXT("Times New Roman"));
    //HRESULT hr = StringCchCopy(lf.lfFaceName, 6, TEXT("Arial"));
    //HRESULT hr = StringCchCopy(lf.lfFaceName, 10, TEXT("FF_SCRIPT"));
    if (FAILED(hr)) {
        MessageBox(hWnd, TEXT("Ошибка FaceName"), TEXT(""), MB_OK);
    }
    // lstrcpy(lf.lfFaceName, (TEXT("Curier")));

    HFONT hFont = CreateFontIndirect(&lf);
    return hFont;
}