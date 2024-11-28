#include "Sp_Pr3HMSG.h"

// ��������� ��������� WM_COMMAND
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
		MessageBoxW(hwnd, L"������� ������� ������� ����", L"������� ����", MB_OK);
	} return;

	case IDM_EDIT_SEL:
	{
		MessageBoxW(hwnd, L"������� ������� ��������", L"�������� �����", MB_OK);
	} return;

	case IDM_EDIT_COPY:
	{
		MessageBoxW(hwnd, L"������� ������� ����������", L"����������", MB_OK);
	} return;

	case IDM_HELP_ABOUT:
	{
		MessageBoxW(hwnd, L"������� ������� � ��������� �� ���� �������", L"� ���������", MB_OK);
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
			MessageBoxW(hwnd, L"������� �����", L"������ Edit", MB_OK);
			return;
		}
		else if (WM_GETTEXT > textBufferSize)
		{
			MessageBoxW(hwnd, L"��������� ������������ ����� ������", L"������ Edit", MB_OK | MB_ICONERROR);
			return;
		}
		else
		{
			wchar_t msgBuff[textBufferSize] = {};
			SYSTEMTIME st; GetSystemTime(&st);
			if (StringCchPrintfW(msgBuff, textBufferSize - 1, L"����� : %d � %d ��� %d ���\n",
				st.wHour, st.wMinute, st.wSecond) == S_OK)
			{
				if (StringCchCatW(msgBuff, textBufferSize - 1, L"����� � ������: ") == S_OK
					&& StringCchCatW(msgBuff, textBufferSize - 1, pszTextBuff) == S_OK)
				{
					MessageBoxW(hwnd, msgBuff, L"���������� ������", MB_OK);
				}
				else
				{
					MessageBoxW(hwnd, L"������ ��� ������������", L"���������� ������", MB_OK | MB_ICONERROR);
				}
			}
			else {
				MessageBoxW(hwnd, L"��������� ������������ ����� ������", L"���������� ������", MB_OK | MB_ICONERROR);
			}
		}
	} return; //IDC_BTN_SAVE
	case IDC_BTN_ADD:
	{
		int ind;
		ind = SendMessageW(hListBox, LB_ADDSTRING,
			(WPARAM)0, (LPARAM)pszTextBuff);
		if (ind == LB_ERR)
			MessageBoxW(hwnd, L"������ � ������", L"", MB_OK);
	} return; // end IDC_BTN_ADD
	//default: //��������� �� ��������� ��� WM_COMMAND
	//return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	// default: FORWARD_WM_COMMAND(hwnd, wmId, hwndCtl, wmEvFORWARD_WM_COMMAND(hwnd, id, hwndCtl, codeNotify, fn);
	}
	FORWARD_WM_COMMAND(hwnd, wmId, hwndCtl, wmEvent, DefWindowProcW);
	// end switch(wmId)
}