
#include "SpPr7.h"

void MyDraw(HWND hWnd)
{
    HDC hDraw;
    hDraw = GetDC(hWnd);
    HBRUSH hBr = CreateSolidBrush(RGB(255, 0, 0));
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hDraw, (HGDIOBJ)hBr);
    HPEN hOldPen = (HPEN)SelectObject(hDraw, (HGDIOBJ)hPen);
    Ellipse(hDraw, 30, 20, 90, 80);
    Rectangle(hDraw, 35, 80, 85, 130);

    SelectObject(hDraw, (HGDIOBJ)hOldBrush);
    SelectObject(hDraw, (HGDIOBJ)hOldPen);
    DeleteObject((HGDIOBJ)hBr);
    DeleteObject((HGDIOBJ)hPen);
    ReleaseDC(hWnd, hDraw);
}