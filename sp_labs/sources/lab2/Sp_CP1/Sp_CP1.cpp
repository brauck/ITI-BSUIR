#include <windows.h>
#include <strsafe.h>

//-- Prototypes -------------------
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
// -- Global variables ------------
HINSTANCE g_hInst = nullptr;

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR     pCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wc = {};
	MSG msg;
	g_hInst = hInstance;

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"SimpleClassName";
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIconW(wc.hInstance, IDI_APPLICATION); // ������ ���� � �������������� ��������� �������
	wc.hCursor = LoadCursorW(NULL, IDC_ARROW); // ����� ������� � �������������� ��������� ��������
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
		L"������� ���� ����������. ����������� ������� ������",
		WS_OVERLAPPEDWINDOW,
		500, // ��������� ���� (�� �����������)
		150, // ��������� ���� (�� ���������)
		600, // ������� ���� (������)
		320, // ������� ���� (������)
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
	static HWND hButtonGetInstance;
	static HWND hButtonClearEditor;
	static HWND hButtonExit;
	static HWND hEdit;
	#define IDC_BTN_GET			150 // ��������� � ����������� �������� ����������� ���������� ���������� (hInstance)
	#define IDC_BTN_CLEAN		151 // ������� ���� Edit
	#define IDC_EDIT1			152

	switch (uMsg)
	{
	case WM_CREATE:
	{
		if (!(hEdit = CreateWindowExW(0L, L"Edit", L"",
			WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VISIBLE,
			20, 50, 320, 100, hwnd, (HMENU)(IDC_EDIT1),
			g_hInst, NULL))) return (-1);

		if (!(hButtonGetInstance = CreateWindowExW(0L, L"Button", L"�������� hInstance",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			20, 240, 150, 24, hwnd, (HMENU)(IDC_BTN_GET),
			g_hInst, NULL))) return (-1);

		if (!(hButtonClearEditor = CreateWindowExW(0L, L"Button", L"�������� ��������",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			190, 240, 150, 24, hwnd, (HMENU)(IDC_BTN_CLEAN),
			g_hInst, NULL))) return (-1);

		if (!(hButtonExit = CreateWindowExW(0L, L"Button", L"�����",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			400, 240, 80, 24, hwnd, (HMENU)(IDCANCEL),
			g_hInst, NULL))) return (-1);
	} return 0;

	case WM_COMMAND:
	{
		const UINT32 textBufferSize = 500;				// ������ ��������� � Edit
		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		static WCHAR msgBuff[textBufferSize] = {};		// ��������� ��������� � Edit
		static BOOL firstClick = FALSE;					// ���� ������� �����
		WCHAR idc_btn_getToWchar[textBufferSize] = {};
		
		if (StringCchPrintfW(idc_btn_getToWchar, textBufferSize - 1,
			L"\r\n\r\nIDC_BTN_GET: %d", IDC_BTN_GET) != S_OK)
		{
			MessageBoxW(hwnd, L"NOT OK", L"IDC_BTN_GET", MB_OK | MB_ICONERROR);
		}

		switch (wmId)
		{
		case IDCANCEL:
			DestroyWindow(hwnd);
			return 0;
		case IDC_BTN_GET:
		{
			LONG hinst = GetWindowLongW(hwnd, GWL_HINSTANCE); // �������� ����������� ���������� ���������� (hInstance)

			if (firstClick == FALSE)
			{
				if (msgBuff[0]) return 0; // ���� ��������� �� ������ - ������ ������ ���� ��� ���
				if (StringCchPrintfW(msgBuff, textBufferSize - 1, L"DEC: %d, HEX: %x",
					hinst, hinst) != S_OK)
				{				
					MessageBoxW(hwnd, L"NOT OK", L"������ hInstance",
						MB_OK | MB_ICONERROR);
					return 0;
				}
				firstClick = TRUE;
			}
			else
			{
				if (StringCchCatW(msgBuff, textBufferSize - 1, idc_btn_getToWchar) != S_OK)
				{
					MessageBoxW(hwnd, L"NOT OK", L"�������� � hInstance",
						MB_OK | MB_ICONERROR);
					return 0;
				}
				firstClick = FALSE;
			}

			SendMessageW(hEdit, WM_SETTEXT, NULL, (LPARAM)msgBuff); // ��������� ��� ���������� ���� Edit
			
		} return 0; 
		case IDC_BTN_CLEAN:
		{
			SendMessageW(hEdit, WM_SETTEXT, NULL, (LPARAM)L""); // ������� ���� Edit
			if (StringCchPrintfW(msgBuff, textBufferSize - 1, L"") != S_OK) // ����� ���������� ���������
			{
				MessageBoxW(hwnd, L"NOT OK", L"CLEAR", MB_OK | MB_ICONERROR);
			}
		} return 0; 

		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
		} // end switch(wmId)
	} return 0; // end WM_COMMAND	

	case WM_PAINT: // ����� ��� ���������� ����
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hwnd, &ps); // ��������� ��������� ��� ���������� ���� 
		EndPaint(hwnd, &ps); // ���������� ���������� ����
	} return 0;

	case WM_DESTROY: // ���������� ������ ����������
		PostQuitMessage(0); // ������� WM_QUIT ����������
		return 0;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}