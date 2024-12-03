#include "Sp_Pr3.h"

void WindowProc_OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags)
{
	HDC hdc1;
	const WCHAR lpszMsgSpace[] = L"ШШШШШШШШШШШШШШШШШШШШШШШШШШ";
	WCHAR Buf[300];
	static HINSTANCE hInst;
	hInst = (HINSTANCE)GetWindowLongW(hwnd, GWL_HINSTANCE);
	static int size;
	size = LoadStringW(hInst, item, Buf, 300);
	hdc1 = GetDC(hwnd);
	static RECT rc;
	GetClientRect(hwnd, &rc);
	TextOut(hdc1, rc.left + 10, rc.bottom - 30,
		lpszMsgSpace, lstrlen(lpszMsgSpace));
	TextOut(hdc1, rc.left + 10, rc.bottom - 30, Buf, lstrlen(Buf));
	ReleaseDC(hwnd, hdc1);
}

void WindowProc_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	const wchar_t mesText[] = L"Нажата левая кнопка мыши";
	HDC hdc = GetDC(hwnd);
	TextOutW(hdc, x, y, mesText, lstrlenW(mesText)); // Вывод в контекст
	ReleaseDC(hwnd, hdc);
}

void WindowProc_OnRButtonUp(HWND hwnd, int x, int y, UINT flags)
{
	POINT pt = {};
	pt.x = x;
	pt.y = y;
	HMENU hMenu = CreatePopupMenu();

	ClientToScreen(hwnd, &pt);

	UINT CopyState = GetMenuState(GetSubMenu(GetMenu(hwnd), 1), 2, MF_BYPOSITION);
	UINT SelState = GetMenuState(GetSubMenu(GetMenu(hwnd), 1), 0, MF_BYPOSITION);

	AppendMenuW(hMenu, SelState, IDM_EDIT_SEL, L"Выделить");
	AppendMenuW(hMenu, CopyState, IDM_EDIT_COPY, L"Копировать");

	TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
	DestroyMenu(hMenu);
}

BOOL WindowProc_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	if (!(hEdit = CreateWindowExW(0L, L"Edit", L"Редактор",
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		20, 50, 160, 40, hwnd, (HMENU)(IDC_EDIT1),
		g_hInst, NULL))) return (-1);

	if (!(hListBox = CreateWindowExW(0L, L"ListBox",
		L"Список", WS_CHILD | WS_BORDER | WS_VISIBLE,
		200, 50, 160, 180, hwnd, (HMENU)(IDC_LISTBOX),
		g_hInst, NULL))) return (FALSE);

	if (!(hButtonSave = CreateWindowExW(0L, L"Button", L"В буфер",
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		20, 240, 80, 24, hwnd, (HMENU)(IDC_BTN_SAVE),
		g_hInst, NULL))) return (FALSE);

	if (!(hButtonAdd = CreateWindowExW(0L, L"Button", L"В список",
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		120, 240, 80, 24, hwnd, (HMENU)(IDC_BTN_ADD),
		g_hInst, NULL))) return (FALSE);

	if (!(hButtonExit = CreateWindowExW(0L, L"Button", L"Выход",
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		220, 240, 80, 24, hwnd, (HMENU)(IDCANCEL),
		g_hInst, NULL))) return (FALSE);

	HMENU hmFile = GetSubMenu(GetMenu(hwnd), 0);
	AppendMenuW(hmFile, MF_STRING | MF_ENABLED, IDM_FILE_CLOSE, L"Закрыть документ");
	return TRUE;
}

void WindowProc_OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hwnd, &ps); // Получение контекста для обновления окна 
	TextOutW(hDC, 10, 10, L"Hello, World!", 13); // Вывод в контекст
	EndPaint(hwnd, &ps); // Завершение обновления окна
}

void WindowProc_OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}