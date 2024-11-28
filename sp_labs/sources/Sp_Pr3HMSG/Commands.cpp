#include "Sp_Pr3HMSG.h"

// Обработка сообщения WM_COMMAND
void  WindowProc_OnCommand(HWND hwnd, int wmId, HWND hwndCtl, UINT wmEvent)
{
	const UINT32 textBufferSize = 500;
	// int wmId = LOWORD(wParam);
	// int wmEvent = HIWORD(wParam);
	static wchar_t pszTextBuff[textBufferSize] = {};
	switch (wmId)
	{
		// MENU BEGIN
	case IDM_FILE_OPEN:
	{
		MessageBoxW(hwnd, L"Выбрана команда открыть файл", L"Открыть файл", MB_OK);
	} return;

	case IDM_EDIT_SEL:
	{
		MessageBoxW(hwnd, L"Выбрана команда Выделить", L"Выделить текст", MB_OK);
	} return;

	case IDM_EDIT_COPY:
	{
		MessageBoxW(hwnd, L"Выбрана команда Копировать", L"Копировать", MB_OK);
	} return;

	case IDM_HELP_ABOUT:
	{
		MessageBoxW(hwnd, L"Выбрана команда О программе из меню Справка", L"О программе", MB_OK);
	} return;
	// MENU END

	case IDCANCEL:
		DestroyWindow(hwnd);
		return;
	case IDC_BTN_SAVE:
	{
		int cch;
		cch = SendMessageW(hEdit, WM_GETTEXT, (WPARAM)textBufferSize, (LPARAM)pszTextBuff);
		if (cch == 0)
		{
			MessageBoxW(hwnd, L"Введите текст", L"Читаем Edit", MB_OK);
			return;
		}
		else if (WM_GETTEXT > textBufferSize)
		{
			MessageBoxW(hwnd, L"Превышена максимальная длина текста", L"Читаем Edit", MB_OK | MB_ICONERROR);
			return;
		}
		else
		{
			wchar_t msgBuff[textBufferSize] = {};
			SYSTEMTIME st; GetSystemTime(&st);
			if (StringCchPrintfW(msgBuff, textBufferSize - 1, L"Время : %d ч %d мин %d сек\n",
				st.wHour, st.wMinute, st.wSecond) == S_OK)
			{
				if (StringCchCatW(msgBuff, textBufferSize - 1, L"Текст в памяти: ") == S_OK
					&& StringCchCatW(msgBuff, textBufferSize - 1, pszTextBuff) == S_OK)
				{
					MessageBoxW(hwnd, msgBuff, L"Содержимое буфера", MB_OK);
				}
				else
				{
					MessageBoxW(hwnd, L"Ошибка при конкатенации", L"Содержимое буфера", MB_OK | MB_ICONERROR);
				}
			}
			else {
				MessageBoxW(hwnd, L"Превышена максимальная длина текста", L"Содержимое буфера", MB_OK | MB_ICONERROR);
			}
		}
	} return; //IDC_BTN_SAVE
	case IDC_BTN_ADD:
	{
		int ind;
		ind = SendMessageW(hListBox, LB_ADDSTRING,
			(WPARAM)0, (LPARAM)pszTextBuff);
		if (ind == LB_ERR)
			MessageBoxW(hwnd, L"Ошибка в списке", L"", MB_OK);
	} return; // end IDC_BTN_ADD
	//default: //обработка по умолчанию для WM_COMMAND
	//return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	// default: FORWARD_WM_COMMAND(hwnd, wmId, hwndCtl, wmEvFORWARD_WM_COMMAND(hwnd, id, hwndCtl, codeNotify, fn);
	}
	FORWARD_WM_COMMAND(hwnd, wmId, hwndCtl, wmEvent, DefWindowProcW);
	// end switch(wmId)
}