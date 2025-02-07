#include "framework.h"


DWORD WINAPI DraweImage(PVOID pvParam) {
	HWND hWndForImage = (HWND)pvParam;
	HDC hDC;
	HDC hCompDC;
	HANDLE hBmp;
	HANDLE hOldBmp;
	BITMAP Bmp;

	LPCTSTR frames[] =
	{
		TEXT("frames\\frame_00_delay-0.04s.bmp"),
		TEXT("frames\\frame_01_delay-0.04s.bmp"),
		TEXT("frames\\frame_02_delay-0.04s.bmp"),
		TEXT("frames\\frame_03_delay-0.04s.bmp"),
		TEXT("frames\\frame_04_delay-0.04s.bmp"),
		TEXT("frames\\frame_05_delay-0.04s.bmp"),
		TEXT("frames\\frame_06_delay-0.04s.bmp"),
		TEXT("frames\\frame_07_delay-0.04s.bmp"),
		TEXT("frames\\frame_08_delay-0.04s.bmp"),
		TEXT("frames\\frame_09_delay-0.04s.bmp"),
		TEXT("frames\\frame_10_delay-0.04s.bmp"),
		TEXT("frames\\frame_11_delay-0.04s.bmp"),
	};

	hDC = GetDC(hWndForImage);
	hCompDC = CreateCompatibleDC(hDC);

	int i = 0;
	while (true)
	{
		if (i == 11) i = 0;
		hBmp = (HBITMAP)LoadImage(hInst, frames[i], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
		GetObject(hBmp, sizeof(BITMAP), &Bmp);
		hOldBmp = SelectObject(hCompDC, hBmp);
		RECT rct;
		GetClientRect(hWndForImage, &rct);
		/*StretchBlt(hDC, 200, 200, rct.right-100, rct.bottom-100,
			hCompDC, 100, 100, Bmp.bmWidth-20, Bmp.bmHeight-20, SRCCOPY);*/
		StretchBlt(hDC, 20, 100, Bmp.bmWidth, Bmp.bmHeight,
			hCompDC, 0, 0, Bmp.bmWidth, Bmp.bmHeight, SRCCOPY);
		Sleep(70);
		i++;
	}

	SelectObject(hCompDC, hOldBmp);
	DeleteObject(hBmp);
	DeleteDC(hCompDC);
	ReleaseDC(hWndForImage, hDC);

	return 0;
}
