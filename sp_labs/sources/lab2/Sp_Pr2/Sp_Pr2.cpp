#include <windows.h>
//-- Prototypes -------------------
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR     pCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wc;
	MSG msg;
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
		MessageBox(NULL, L"������ ����������� ������ ����!",
			L"������", MB_OK | MB_ICONERROR);
		return FALSE;
	}
	HWND hwnd = CreateWindowEx(NULL, L"SimpleClassName",
		L"Simple Application with Message handling",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, // ��������� ���� (�� �����������)
		CW_USEDEFAULT, // ��������� ���� (�� ���������)
		CW_USEDEFAULT, // ������� ���� (������)
		CW_USEDEFAULT, // ������� ���� (������)
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hwnd)
	{
		MessageBox(NULL, L"���� �� �������!",
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
	switch (uMsg)
	{
		//=====================================
	case WM_LBUTTONDOWN:
		{
			const wchar_t mesText[] = L"������ ����� ������ ����";
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			HDC hdc = GetDC(hwnd);
			TextOut(hdc, x, y, mesText, lstrlen(mesText)); // ����� � ��������
			ReleaseDC(hwnd, hdc);
		}
		return 0;

	//=========================================
	case WM_PAINT: // ����� ��� ���������� ����
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hwnd, &ps); // ��������� ��������� ��� ���������� ���� 
			TextOut(hDC, 10, 10, L"Hello, World!", 13); // ����� � ��������
			EndPaint(hwnd, &ps); // ���������� ���������� ����
		}
		return 0;

	case WM_DESTROY: // ���������� ������ ����������
		PostQuitMessage(0); // ������� WM_QUIT ����������
		return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}