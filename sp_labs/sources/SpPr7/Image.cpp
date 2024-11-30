#include "SpPr7.h"


void DraweImage(HWND hWndForImage) {
	//case IDM_VIEW_GRAPHIC:
	HDC hDC;
	HDC hCompDC;
	HANDLE hBmp;
	HANDLE hOldBmp;
	BITMAP Bmp;
	hBmp = LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	hDC = GetDC(hWndForImage);
	hCompDC = CreateCompatibleDC(hDC);
	GetObject(hBmp, sizeof(BITMAP), &Bmp);
	hOldBmp = SelectObject(hCompDC, hBmp);
	RECT rct;
	GetClientRect(hWndForImage, &rct);
	StretchBlt(hDC, 200, 200, rct.right-100, rct.bottom-100,
		hCompDC, 100, 100, Bmp.bmWidth-20, Bmp.bmHeight-20, SRCCOPY);
	SelectObject(hCompDC, hOldBmp);
	DeleteDC(hCompDC);
	DeleteObject(hBmp);
	ReleaseDC(hWndForImage, hDC);
}
//	break;