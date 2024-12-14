#include "SpPr7.h"

LPCTSTR MetaDraw()
{
	LPCTSTR fileName = TEXT("SpPr7.wmf");
	HDC hdcMeta = CreateMetaFile(fileName);

    const int R = 20;
    const int A = 100;
    const int B = 60;

    const int x0 = 20;              // начало окружности
    const int y0 = 100;             // начало окружности

    const int x1 = x0 + R * 2;      // начало пятиугольника
    const int y1 = y0 + R + A / 2;  // начало пятиугольника

    //HBRUSH hBr = CreateSolidBrush(RGB(255, 0, 0));
    HBRUSH hBrVert = CreateHatchBrush(HS_VERTICAL, RGB(255, 0, 0));
    HBRUSH hBrHor = CreateHatchBrush(HS_HORIZONTAL, RGB(255, 0, 0));
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdcMeta, (HGDIOBJ)hBrVert);
    HPEN hOldPen = (HPEN)SelectObject(hdcMeta, (HGDIOBJ)hPen);

    Ellipse(hdcMeta, x0, y0, (x0 + (R * 2)), (y0 + (R * 2)));

    DeleteObject((HGDIOBJ)hBrVert);

    POINT pt[5] =
    {
        {x1, y1},
        {x1, y1 - A},
        {x1 + (B / 2), y1 - A - (A / 2)},
        {x1 + B, y1 - A},
        {x1 + B, y1}
    };

    hOldBrush = (HBRUSH)SelectObject(hdcMeta, (HGDIOBJ)hBrHor);
    Polygon(hdcMeta, pt, sizeof(pt) / sizeof(pt[0]));

    DeleteObject((HGDIOBJ)hBrHor);
    DeleteObject((HGDIOBJ)hPen);
    CloseMetaFile(hdcMeta);

    return fileName;
}