#include "Sp_Pr3.h"

// -- Global Variables-------------
HINSTANCE g_hInst = nullptr;
// ����������� �������� ����
HWND hEdit;
HWND hListBox;
HWND hButtonSave;
HWND hButtonAdd;
HWND hButtonExit;

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR     pCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wc;
	MSG msg;
	// g_hInst = hInstance;

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"SimpleClassName";
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIconW(wc.hInstance, MAKEINTRESOURCEW(IDI_ICON1)); // ������ ���� � �������������� ��������� �������
	wc.hCursor = LoadCursorW(wc.hInstance, MAKEINTRESOURCEW(IDC_CURSOR1)); // ����� ������� � �������������� ��������� ��������
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ���� ���� ���� � �������������� ��������� ������
	wc.lpszMenuName = NULL; // MAKEINTRESOURCEW(IDR_MENU1);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBoxW(NULL, L"������ ����������� ������ ����!",
			L"������", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	HMENU hmenu = LoadMenuW(wc.hInstance, MAKEINTRESOURCEW(IDR_MENU1));

	HWND hwnd = CreateWindowExW(NULL, L"SimpleClassName",
		L"������� ���� ����������. ����������� ������� ������",
		WS_OVERLAPPEDWINDOW,
		500, // ��������� ���� (�� �����������)
		150, // ��������� ���� (�� ���������)
		600, // ������� ���� (������)
		500, // ������� ���� (������)
		NULL,
		hmenu,
		wc.hInstance,
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

	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCEL1));
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hwnd, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}
// ������� ���������
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{		
	switch (uMsg)
	{
	HANDLE_MSG(hwnd, WM_PAINT, WindowProc_OnPaint);
	HANDLE_MSG(hwnd, WM_CREATE, WindowProc_OnCreate);
	HANDLE_MSG(hwnd, WM_COMMAND, WindowProc_OnCommand);
	HANDLE_MSG(hwnd, WM_DESTROY, WindowProc_OnDestroy);
	HANDLE_MSG(hwnd, WM_RBUTTONUP, WindowProc_OnRButtonUp);
	HANDLE_MSG(hwnd, WM_MENUSELECT, WindowProc_OnMenuSelect);
	HANDLE_MSG(hwnd, WM_LBUTTONDOWN, WindowProc_OnLButtonDown);	
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}