// Обработка ввода мыши и клавиатуры 
// Справочная информация
// Platform SDK/User Interface Services/User Input/Keyboard Input/
// Keyboard Input Reference/Keyboard Input Messages

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <string.h>
#include <stdio.h>

// Глобальные переменные
int     nPosX = 10;
int     nPosY = 0;
LPCTSTR  lpszAppName = TEXT("Демонстрация обработки ввода мыши и клавиатуры");
LPCTSTR lpszClassName = TEXT("Key And Mause Demo Class");
HWND    hMainWnd;
BOOL fDraw = FALSE; // флаг рисовать, если нажата левая кнопка мыши
HDC drawDC; // контекст для рисования

int x0 = 60;
int y0 = 160;
int cx = 100;
int cy = 300;
const int d = 4;
const int n = 10;
int count = 0;

const COLORREF color = RGB(0, 255, 255);
HPEN hpen1 = CreatePen(PS_SOLID, 2, color);

//========Предварительное объявление функций=========================
  /* Процедура главного окна */
LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
/* Регистрация класса главного окна */
BOOL Register(HINSTANCE);
/* Создание главного окна */
HWND Create(HINSTANCE, int);

/* Обработчики соощений */
/*--- WM_DESTROY -----------------------------------------------------*/
void  km_OnDestroy(HWND hwnd);
/*--- WM_KEYUP,WM_KEYDOWN --------------------------------------------*/
void  km_OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);
/*--- WM_LBUTTONDOWN, WM_LBUTTONDBLCLK -------------------------------*/
void  km_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
/*--- WM_LBUTTONUP ---------------------------------------------------*/
void  km_OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
/*--- WM_MOUSEMOVE ---------------------------------------------------*/
void  km_OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
/*--- WM_PAINT -------------------------------------------------------*/
void  km_OnPaint(HWND hwnd);
/*---- WM_WINDOWPOSCHANGED ------------------------------------------*/
BOOL km_OnWindowPosChanged(HWND hwnd, LPWINDOWPOS lpwpos);
//====================================================================//


// Точка входа в программу ===========================================//
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst,
	LPTSTR lpszCmdLine, int nCmdShow)
{
	MSG Msg;
	BOOL ok;

	ok = Register(hInst);
	if (!ok) return FALSE;

	hMainWnd = Create(hInst, nCmdShow);
	if (!hMainWnd) return FALSE;
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

//== Функция для регистрации класса окна =============================//
BOOL Register(HINSTANCE hinst)
{
	WNDCLASSEX WndClass;
	BOOL fRes;

	memset(&WndClass, 0, sizeof(WNDCLASSEX));
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.lpszClassName = lpszClassName;
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hinst;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.lpszMenuName = NULL;

	fRes = (BOOL)RegisterClassEx(&WndClass);
	return fRes;
}

//== Функция создания окна ===========================================//
HWND Create(HINSTANCE hInstance, int nCmdShow)
{
	HWND hwnd = CreateWindowEx(0,
		lpszClassName, lpszAppName,
		WS_OVERLAPPEDWINDOW,
		x0, y0,
		cx, cy,
		NULL, NULL, hInstance, NULL);
	if (hwnd == NULL) return hwnd;
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	return hwnd;
}

//== Оконная процедура главного окна =================================//
LRESULT WINAPI
WndProc(HWND hwnd, UINT MesId, WPARAM wParam, LPARAM lParam)
{
	switch (MesId)
	{
		HANDLE_MSG(hwnd, WM_DESTROY, km_OnDestroy);
		HANDLE_MSG(hwnd, WM_KEYDOWN, km_OnKey);
		HANDLE_MSG(hwnd, WM_MOUSEMOVE, km_OnMouseMove);
		HANDLE_MSG(hwnd, WM_LBUTTONDBLCLK, km_OnLButtonDown);
		HANDLE_MSG(hwnd, WM_LBUTTONDOWN, km_OnLButtonDown);
		HANDLE_MSG(hwnd, WM_LBUTTONUP, km_OnLButtonUp);
		HANDLE_MSG(hwnd, WM_PAINT, km_OnPaint);
		HANDLE_MSG(hwnd, WM_WINDOWPOSCHANGED, km_OnWindowPosChanged);		

	default:
		return DefWindowProc(hwnd, MesId, wParam, lParam);
	}
}

//====================================================================//
//====================================================================//

//=== Обработчик сообщения WM_DESTROY ================================//
void km_OnDestroy(HWND hwnd)
{
	DeleteObject(hpen1);
	PostQuitMessage(0);
}

//=== Обработчик сообщения WM_KEYUP,WM_KEYDOWN =======================//
void km_OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
	switch (vk)
	{
	case 0x47: // G
	{
		x0 -= d;
		SetWindowPos(hwnd, NULL, x0, y0, 0, 0, SWP_NOSIZE);
	} return;

	case 0x48: // H
	{
		x0 += d;
		SetWindowPos(hwnd, NULL, x0, y0, 0, 0, SWP_NOSIZE);
	} return;

	case 0x42: // B
	{
		y0 -= d;
		SetWindowPos(hwnd, NULL, x0, y0, 0, 0, SWP_NOSIZE);
	} return;

	case 0x4E: // N
	{
		y0 += d;
		SetWindowPos(hwnd, NULL, x0, y0, 0, 0, SWP_NOSIZE);
	} return;

	case VK_F2:
	{
		fDraw = TRUE;
	} return;

	case VK_F3:
	{
		fDraw = FALSE;
	} return;
	}
}


//=== Обработчик сообщения WM_LBUTTONDOWN, WM_LBUTTONDBLCLK ==========//
void km_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x,
	int y, UINT keyFlags)
{
	if (!fDraw) return;
	drawDC = GetDC(hMainWnd); // определение контекста для рисования	
	SelectObject(drawDC, hpen1);
	MoveToEx(drawDC, x, y, NULL); // начальные координаты рисования
	SetCapture(hwnd); // захват окна для корректной отрисовки линии, если курсор вышел за границы окна
}

//=== Обработчик сообщения WM_LBUTTONUP ==============================//
void km_OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	ReleaseCapture(); // освобождение захвата окна
	ReleaseDC(hwnd, drawDC); // освобождение ресурсов контекста
}

//=== Обработчик сообщения WM_MOUSEMOVE ==============================//
void km_OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	if (count != n)
	{
		count++;
		return;
	}
	count = 0;
	if (fDraw)  Ellipse(drawDC, x - n, y + n, x + n, y - n); // рисование окружности, если нажата левая кнопка мыши (курсор в центре)
}

//=== Обработчик сообщения WM_PAINT ==================================//
void km_OnPaint(HWND hwnd)
{
	PAINTSTRUCT PaintStruct;

	HDC PaintDC = BeginPaint(hwnd, &PaintStruct);//Получаем контекст

	/*TCHAR S[45];
	RECT CRect;
	GetClientRect(hwnd, &CRect);
	RECT WRect;
	GetWindowRect(hwnd, &WRect);
	SetTextColor(PaintDC, color);
	wsprintf(S, TEXT("x0: %d, y0: %d   "), x0, y0);
	TextOut(PaintDC, CRect.right - 105, CRect.bottom - 20, S, 45);
	ReleaseDC(hwnd, PaintDC);*/

	EndPaint(hwnd, &PaintStruct);//Освобождаем контекст устройства
}

BOOL km_OnWindowPosChanged(HWND hwnd, LPWINDOWPOS lpwpos)
{
	x0 = lpwpos->x;
	y0 = lpwpos->y;

	TCHAR S[45];
	RECT CRect;
	GetClientRect(hwnd, &CRect);
	RECT WRect;
	GetWindowRect(hwnd, &WRect);
	HDC PaintDC = GetDC(hwnd);
	SetTextColor(PaintDC, color);
	wsprintf(S, TEXT("x0: %d, y0: %d   "), x0, y0);
	TextOut(PaintDC, CRect.right - 105, CRect.bottom - 20, S, 45);
	ReleaseDC(hwnd, PaintDC);
	return 0;
}

//====================================================================//