// Обработка ввода мыши и клавиатуры 
// Справочная информация
// Platform SDK/User Interface Services/User Input/Keyboard Input/
// Keyboard Input Reference/Keyboard Input Messages

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <string.h>
#include <stdio.h>
//#include <wingdi.h>

// Глобальные переменные
int     nPosX = 10;
int     nPosY = 0;
LPCTSTR  lpszAppName = TEXT("Демонстрация обработки ввода мыши и клавиатуры");
LPCTSTR lpszClassName = TEXT("Key And Mause Demo Class");
HWND    hMainWnd;
BOOL fDraw = FALSE; // флаг рисовать, если нажата левая кнопка мыши
BOOL fStart = TRUE; // флаг - приложение только загрузилось
HDC drawDC; // контекст для рисования


int x0 = 60;
int y0 = 160;
int cx = 100;
int cy = 300;
const int d = 4;
const int n = 10;
//BOOL OnPaint = FALSE;
int count = 0;
POINT ptPrevious;

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
/*--- WM_CHAR --------------------------------------------------------*/
void  km_OnChar(HWND hwnd, UINT ch, int cRepeat);
/*--- WM_KEYUP,WM_KEYDOWN --------------------------------------------*/
void  km_OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);
/*--- WM_SYSKEYDOWN, WM_SYSKEYUP  ------------------------------------*/
//void  km_OnSysKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);
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
		HANDLE_MSG(hwnd, WM_CHAR, km_OnChar);
		HANDLE_MSG(hwnd, WM_KEYDOWN, km_OnKey);
		//HANDLE_MSG(hwnd, WM_KEYUP, km_OnKey);
		HANDLE_MSG(hwnd, WM_MOUSEMOVE, km_OnMouseMove);
		HANDLE_MSG(hwnd, WM_LBUTTONDBLCLK, km_OnLButtonDown);
		HANDLE_MSG(hwnd, WM_LBUTTONDOWN, km_OnLButtonDown);
		HANDLE_MSG(hwnd, WM_LBUTTONUP, km_OnLButtonUp);
		HANDLE_MSG(hwnd, WM_PAINT, km_OnPaint);
		//HANDLE_MSG(hwnd, WM_SYSKEYUP, km_OnSysKey);
		//HANDLE_MSG(hwnd, WM_SYSKEYDOWN, km_OnSysKey);
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

//=== Обработчик сообщения WM_TCHAR ===================================//
void km_OnChar(HWND hwnd, UINT ch, int cRepeat)
{
	TCHAR S[100];//Буфер для формирования выводимой строки(100 байт)
	HDC DC = GetDC(hwnd);//Получаем контекст устройства графического вывода

	wsprintf(S, TEXT("WM_CHAR ==> Ch = %c   cRepeat = %d    "), ch, cRepeat);
	SetBkColor(DC, GetSysColor(COLOR_WINDOW));//Задаем цвет фона
	TextOut(DC, nPosX, nPosY + 20, S, lstrlen(S));//Выводим строку

	ReleaseDC(hwnd, DC);//Освобождаем контекст
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
		//MessageBox(hwnd, L"button G", L"btn", MB_OK);
	} return;

	case 0x48: // H
	{
		x0 += d;
		SetWindowPos(hwnd, NULL, x0, y0, 0, 0, SWP_NOSIZE);
		//MessageBox(hwnd, L"button H", L"btn", MB_OK);
	} return;

	case 0x42: // B
	{
		y0 -= d;
		SetWindowPos(hwnd, NULL, x0, y0, 0, 0, SWP_NOSIZE);
		//MessageBox(hwnd, L"button B", L"btn", MB_OK);
	} return;

	case 0x4E: // N
	{
		y0 += d;
		SetWindowPos(hwnd, NULL, x0, y0, 0, 0, SWP_NOSIZE);
		//MessageBox(hwnd, L"button N", L"btn", MB_OK);
	} return;

	case VK_F2:
	{
		fDraw = TRUE;
		//MessageBox(hwnd, L"button F", L"btn", MB_OK);
	} return;

	case VK_F3:
	{
		fDraw = FALSE;
		//MessageBox(hwnd, L"button F3", L"btn", MB_OK);
	} return;
	}

	/*
	TCHAR S[100];//Буфер для формирования выводимой строки(100 байт)
	HDC DC = GetDC(hwnd);//Получаем контекст устройства графического вывода

	if (fDown) { //Клавиша нажата
		wsprintf(S, TEXT("WM_KEYDOWN ==> vk = %d fDown = %d cRepeat = %d flags = %d    "),
			vk, fDown, cRepeat, flags);
	}
	else {//Клавиша отпущена
		wsprintf(S, TEXT("WM_KEYUP ==> vk = %d fDown = %d cRepeat = %d flags = %d      "),
			vk, fDown, cRepeat, flags);
	}
	SetBkColor(DC, GetSysColor(COLOR_WINDOW));//Задаем цвет фона
	TextOut(DC, nPosX, nPosY + 40, S, lstrlen(S));//Выводим строку
	ReleaseDC(hwnd, DC);//Освобождаем контекст
	*/
}


//=== Обработчик сообщения WM_LBUTTONDOWN, WM_LBUTTONDBLCLK ==========//
void km_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x,
	int y, UINT keyFlags)
{
	/*if (count != n)
	{
		count++;
		return;
	}
	count = 0;*/

	/*TCHAR S[100];//Буфер для формирования выводимой строки(100 байт)
	HDC DC = GetDC(hwnd);//Получаем контекст устройства графического вывода

	if (fDoubleClick) //Двойной щелчек
		wsprintf(S, TEXT("WM_LBUTTONDBLCLK ==> Db = %d x = %d y = %d Flags = %d "),
			fDoubleClick, x, y, keyFlags);
	else // Одиночный щелчек 
		wsprintf(S, TEXT("WM_LBUTTONDOWN ==> Db = %d x = %d y = %d Flags = %d "),
			fDoubleClick, x, y, keyFlags);

	SetBkColor(DC, GetSysColor(COLOR_WINDOW));//Задаем цвет фона
	TextOut(DC, nPosX, nPosY + 100, S, lstrlen(S));//Выводим строку
	ReleaseDC(hwnd, DC);//Освобождаем контекст*/

	if (!fDraw) return;
	drawDC = GetDC(hMainWnd); // определение контекста для рисования	
	SelectObject(drawDC, hpen1);
	MoveToEx(drawDC, x, y, NULL); // начальные координаты рисования
	SetCapture(hwnd); // захват окна для корректной отрисовки линии, если курсор вышел за границы окна
}

//=== Обработчик сообщения WM_LBUTTONUP ==============================//
void km_OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{


	/*TCHAR S[100];//Буфер для формирования выводимой строки(100 байт)
	HDC  DC = GetDC(hwnd);//Получаем контекст устройства графического вывода

	wsprintf(S, TEXT("MM LBUTTONUP ==> x = %d y = %d F = %d   "),
		x, y, keyFlags);

	SetBkColor(DC, GetSysColor(COLOR_WINDOW));
	TextOut(DC, nPosX, nPosY + 120, S, lstrlen(S));
	ReleaseDC(hwnd, DC);//Освобождаем контекст
	//fDraw = FALSE;*/
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
	/*TCHAR S[100];//Буфер для формирования выводимой строки(100 байт)
	HDC DC = GetDC(hwnd);//Получаем контекст устройства графического вывода

	wsprintf(S, TEXT("WM_MOUSEMOVE ==> x = %d y = %d keyFlags = %d    "),
		x, y, keyFlags);
	//Задаем цвет в зависимости от нажатых клавиш мыши и клавиатуры 
	if ((keyFlags & MK_CONTROL) == MK_CONTROL) SetTextColor(DC, RGB(0, 0, 255));
	if ((keyFlags & MK_LBUTTON) == MK_LBUTTON) SetTextColor(DC, RGB(0, 255, 0));
	if ((keyFlags & MK_RBUTTON) == MK_RBUTTON) SetTextColor(DC, RGB(255, 0, 0));
	if ((keyFlags & MK_SHIFT) == MK_SHIFT)   SetTextColor(DC, RGB(255, 0, 255));


	SetBkColor(DC, GetSysColor(COLOR_WINDOW)); //Устанавливаем цвет фона
	TextOut(DC, nPosX, nPosY + 80, S, lstrlen(S));// Выводим строку текста
	ReleaseDC(hwnd, DC);  // Освобождение контекста*/
	if (fDraw)  Ellipse(drawDC, x - n, y + n, x + n, y - n); // рисование круга, если нажата левая кнопка мыши (курсор в центре)
}



//=== Обработчик сообщений WM_SYSKEYDOWN и WM_SYSKEYUP ===============//
/*void km_OnSysKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
	TCHAR S[100];//Буфер для формирования выводимой строки(100 байт)
	HDC DC = GetDC(hwnd); //Получаем контекст устройства графического вывода
	SetBkColor(DC, GetSysColor(COLOR_WINDOW)); //Задаем цвет

	if (fDown)
	{// Системная клавиша нажата
		wsprintf(S, TEXT("WM_SYSKEYDOWN ==> vk = %d fDown = %d cRepeat = %d flags = %d     "),
			vk, fDown, cRepeat, flags);
		TextOut(DC, nPosX, nPosY + 60, S, lstrlen(S));
		FORWARD_WM_SYSKEYDOWN(hwnd, vk, cRepeat, flags, DefWindowProc);
	}
	else
	{// Системная клавиша отпущена
		wsprintf(S, TEXT("WM_SYSKEYUP == > vk = %d fDown = %d cRepeat = %d flags = %d      "),
			vk, fDown, cRepeat, flags);
		TextOut(DC, nPosX, nPosY + 60, S, lstrlen(S));
		FORWARD_WM_SYSKEYUP(hwnd, vk, cRepeat, flags, DefWindowProc);
	}
	ReleaseDC(hwnd, DC);//Освобождаем контекст устройства
}*/

//=== Обработчик сообщения WM_PAINT ==================================//
void km_OnPaint(HWND hwnd)
{
	PAINTSTRUCT PaintStruct;	



	HDC PaintDC = BeginPaint(hwnd, &PaintStruct);//Получаем контекст

	UpdateWindow(hwnd);
	//MessageBox(hwnd, L"buttonsfadsfa", L"paint", MB_OK);
	TCHAR S[45];
	RECT CRect;
	GetClientRect(hwnd, &CRect);
	RECT WRect;
	GetWindowRect(hwnd, &WRect);
	//HDC PaintDC = GetDC(hwnd);
	SetTextColor(PaintDC, color);
	wsprintf(S, L"x0: %d, y0: %d   ", x0, y0);
	TextOut(PaintDC, CRect.right - 105, CRect.bottom - 20, S, 45);
	ReleaseDC(hwnd, PaintDC);
	EndPaint(hwnd, &PaintStruct);//Освобождаем контекст устройства

}

BOOL km_OnWindowPosChanged(HWND hwnd, LPWINDOWPOS lpwpos)
{
	//UpdateWindow(hwnd);
	/*if (fStart)
	{
		lpwpos->x = x0;
		lpwpos->y = y0;
		fStart = FALSE;
		//lpwpos->flags = SWP_NOMOVE;
		//MessageBox(hwnd, L"buttonsfadsfasf F3", L"start", MB_OK);
		return 0;
	}*/
	//MessageBox(hwnd, L"buttonsfadsfasf F3", L"start", MB_OK);
	//lpwpos->flags = SWP_DRAWFRAME;

	//lpwpos->x = x0;
	//lpwpos->y = y0;

	x0 = lpwpos->x;
	y0 = lpwpos->y;

	//static LPWINDOWPOS wp = lpwpos;

	static int x = lpwpos->x;

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
	//fStart = TRUE;
	return 0;
}

//====================================================================//