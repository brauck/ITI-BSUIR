#include "Sp_Pr3HMSG.h"

void WindowProc_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	const wchar_t mesText[] = L"������ ����� ������ ����";
	// int x = LOWORD(lParam);
	// int y = HIWORD(lParam);

	HDC hdc = GetDC(hwnd);
	TextOutW(hdc, x, y, mesText, lstrlenW(mesText)); // ����� � ��������
	ReleaseDC(hwnd, hdc);
}



BOOL WindowProc_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	if (!(hEdit = CreateWindowExW(0L, L"Edit", L"��������",
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		20, 50, 160, 40, hwnd, (HMENU)(IDC_EDIT1),
		g_hInst, NULL))) return (FALSE);

	if (!(hListBox = CreateWindowExW(0L, L"ListBox",
		L"������", WS_CHILD | WS_BORDER | WS_VISIBLE,
		200, 50, 160, 180, hwnd, (HMENU)(IDC_LISTBOX),
		g_hInst, NULL))) return (FALSE);

	if (!(hButtonSave = CreateWindowExW(0L, L"Button", L"� �����",
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		20, 240, 80, 24, hwnd, (HMENU)(IDC_BTN_SAVE),
		g_hInst, NULL))) return (FALSE);

	if (!(hButtonAdd = CreateWindowExW(0L, L"Button", L"� ������",
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		120, 240, 80, 24, hwnd, (HMENU)(IDC_BTN_ADD),
		g_hInst, NULL))) return (FALSE);

	if (!(hButtonExit = CreateWindowExW(0L, L"Button", L"�����",
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		220, 240, 80, 24, hwnd, (HMENU)(IDCANCEL),
		g_hInst, NULL))) return (FALSE);
	return TRUE;
}

void WindowProc_OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hwnd, &ps); // ��������� ��������� ��� ���������� ���� 
	TextOutW(hDC, 10, 10, L"Hello, World!", 13); // ����� � ��������
	EndPaint(hwnd, &ps); // ���������� ���������� ����
}

void WindowProc_OnDestroy(HWND hwnd)
{
	PostQuitMessage(0); // ������� WM_QUIT ����������
}