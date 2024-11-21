#include <windows.h>
#include <strsafe.h>
//-- Prototypes -------------------
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInst = nullptr;
int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR     pCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wc;
	MSG msg;
	g_hInst = hInstance;

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"SimpleClassName";
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(wc.hInstance, IDI_APPLICATION); // ������ ���� � �������������� ��������� �������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // ����� ������� � �������������� ��������� ��������
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ���� ���� ���� � �������������� ��������� ������
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBoxW(NULL, L"������ ����������� ������ ����!",
			L"������", MB_OK | MB_ICONERROR);
		return FALSE;
	}
	HWND hwnd = CreateWindowExW(NULL, L"SimpleClassName",
		L"Simple Application with Message handling",
		WS_OVERLAPPEDWINDOW,
		500, // ��������� ���� (�� �����������)
		150, // ��������� ���� (�� ���������)
		600, // ������� ���� (������)
		500, // ������� ���� (������)
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hwnd)
	{
		MessageBoxW(NULL, L"���� �� �������!",
			L"������", MB_OK | MB_ICONERROR);
		return FALSE;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
// ������� ���������
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	/*int wmId, wmEvent;
	HDC hdc;*/

	static HWND hButtonSave;
	static HWND hButtonAdd;
	static HWND hButtonExit;
	static HWND hEdit;
	static HWND hListBox;
	#define IDC_BTN_SAVE	150
	#define IDC_BTN_ADD		151
	#define IDC_EDIT1		152
	#define IDC_LISTBOX		153		
		
	switch (uMsg)
	{
	case WM_CREATE:
	{
		if (!(hEdit = CreateWindowExW(0L, L"Edit", L"��������",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			20, 50, 160, 40, hwnd, (HMENU)(IDC_EDIT1),
			g_hInst, NULL))) return (-1);

		if (!(hListBox = CreateWindowExW(0L, L"ListBox",
			L"������", WS_CHILD | WS_BORDER | WS_VISIBLE,
			200, 50, 160, 180, hwnd, (HMENU)(IDC_LISTBOX),
			g_hInst, NULL))) return (-1);

		if (!(hButtonSave = CreateWindowExW(0L, L"Button", L"� �����",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			20, 240, 80, 24, hwnd, (HMENU)(IDC_BTN_SAVE),
			g_hInst, NULL))) return (-1);

		if (!(hButtonAdd = CreateWindowExW(0L, L"Button", L"� ������",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			120, 240, 80, 24, hwnd, (HMENU)(IDC_BTN_ADD),
			g_hInst, NULL))) return (-1);

		if (!(hButtonExit = CreateWindowExW(0L, L"Button", L"�����",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			220, 240, 80, 24, hwnd, (HMENU)(IDCANCEL),
			g_hInst, NULL))) return (-1);
	} return 0;

	case WM_COMMAND:
	{
		const UINT32 textBufferSize = 500;
		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		static wchar_t pszTextBuff[textBufferSize] = {};
		switch (wmId)
		{
		case IDCANCEL:
			DestroyWindow(hwnd);
			return 0;
		case IDC_BTN_SAVE:
		{
			int cch;
			cch = SendMessageW(hEdit, WM_GETTEXT, (WPARAM)textBufferSize, (LPARAM)pszTextBuff);
			if (cch == 0)
			{
				MessageBoxW(hwnd, L"������� �����", L"������ Edit", MB_OK);
				return 0;
			}
			else if (WM_GETTEXT > textBufferSize)
			{
				MessageBoxW(hwnd, L"��������� ������������ ����� ������", L"������ Edit", MB_OK | MB_ICONERROR);
				return 0;
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
		} return 0; //IDC_BTN_SAVE
		case IDC_BTN_ADD:
		{
			int ind;
			ind = SendMessageW(hListBox, LB_ADDSTRING,
				(WPARAM)0, (LPARAM)pszTextBuff);
			if (ind == LB_ERR)
				MessageBoxW(hwnd, L"������ � ������", L"", MB_OK);
		} return 0; // end IDC_BTN_ADD
		default: //��������� �� ��������� ��� WM_COMMAND
			return DefWindowProcW(hwnd, uMsg, wParam, lParam);
		} // end switch(wmId)
	} return 0; // end WM_COMMAND
	
	case WM_LBUTTONDOWN:
	{
		const wchar_t mesText[] = L"������ ����� ������ ����";
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		HDC hdc = GetDC(hwnd);
		TextOutW(hdc, x, y, mesText, lstrlenW(mesText)); // ����� � ��������
		ReleaseDC(hwnd, hdc);
	} return 0;

	//=========================================
	case WM_PAINT: // ����� ��� ���������� ����
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hwnd, &ps); // ��������� ��������� ��� ���������� ���� 
		TextOutW(hDC, 10, 10, L"Hello, World!", 13); // ����� � ��������
		EndPaint(hwnd, &ps); // ���������� ���������� ����
	} return 0;

	case WM_DESTROY: // ���������� ������ ����������
		PostQuitMessage(0); // ������� WM_QUIT ����������
		return 0;

	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}