#include "SpPr7.h"


void DraweImage(HWND hWndForImage) {
	HDC hDC;
	HDC hCompDC;
	HANDLE hBmp;
	HANDLE hOldBmp;
	BITMAP Bmp;
	hBmp = LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	//hBmp = LoadImage(hInst, L"D:\\IIT_labs\\ITI-BSUIR\\sp_labs\\sources\\SpPr7\\bitmap1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	//hBmp = (HBITMAP)LoadImage(hInst, L"C:\\Users\\60032\\Pictures\\Screenshots\\Screenshot1.png", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	//hBmp = (HBITMAP)LoadImage(hInst, L"C:\\Users\\60032\\Downloads\\frame.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	//hBmp = (HBITMAP)LoadImage(hInst, L"frames\\frame.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);

	hDC = GetDC(hWndForImage);
	hCompDC = CreateCompatibleDC(hDC);
	GetObject(hBmp, sizeof(BITMAP), &Bmp);
	hOldBmp = SelectObject(hCompDC, hBmp);
	RECT rct;
	GetClientRect(hWndForImage, &rct);
	StretchBlt(hDC, 200, 200, rct.right-100, rct.bottom-100,
		hCompDC, 100, 100, Bmp.bmWidth-20, Bmp.bmHeight-20, SRCCOPY);
	/*StretchBlt(hDC, 20, 20, Bmp.bmWidth, Bmp.bmHeight,
		hCompDC, 0, 0, Bmp.bmWidth, Bmp.bmHeight, SRCCOPY);*/
	SelectObject(hCompDC, hOldBmp);
	DeleteDC(hCompDC);
	DeleteObject(hBmp);
	ReleaseDC(hWndForImage, hDC);
}
