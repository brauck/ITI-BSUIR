

#include "SpPr7.h"

HFONT APIENTRY MyFontCreate(void)
{
    CHOOSEFONT cf;
    LOGFONT lf;
    HFONT hfont;

    // Initialize members of the CHOOSEFONT structure.  

    cf.lStructSize = sizeof(CHOOSEFONT);
    cf.hwndOwner = (HWND)NULL;
    cf.hDC = (HDC)NULL;
    cf.lpLogFont = &lf;
    cf.iPointSize = 0;
    cf.Flags = CF_SCREENFONTS;
    cf.rgbColors = RGB(0, 0, 0);
    cf.lCustData = 0L;
    cf.lpfnHook = (LPCFHOOKPROC)NULL;
    cf.lpTemplateName = (LPCTSTR)NULL;
    cf.hInstance = (HINSTANCE)NULL;
    cf.lpszStyle = (LPTSTR)NULL;
    cf.nFontType = SCREEN_FONTTYPE;
    cf.nSizeMin = 0;
    cf.nSizeMax = 0;

    // Display the CHOOSEFONT common-dialog box.  

    ChooseFont(&cf);

    // Create a logical font based on the user's  
    // selection and return a handle identifying  
    // that font.  

    hfont = CreateFontIndirect(cf.lpLogFont);//&lf
    return (hfont);
}