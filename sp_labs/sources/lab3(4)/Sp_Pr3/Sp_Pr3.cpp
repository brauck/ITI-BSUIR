#include "Sp_Pr3.h"

// -- Global Variables-------------
HINSTANCE g_hInst = nullptr;
// Дескрипторы дочерних окон
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
	wc.hIcon = LoadIconW(wc.hInstance, MAKEINTRESOURCEW(IDI_ICON1)); // значок окна с использованием системных значков
	wc.hCursor = LoadCursorW(wc.hInstance, MAKEINTRESOURCEW(IDC_CURSOR1)); // форма курсора с использованием системных курсоров
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // цвет фона окна с использованием системных кистей
	wc.lpszMenuName = NULL; // MAKEINTRESOURCEW(IDR_MENU1);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBoxW(NULL, L"Ошибка регистрации класса окна!",
			L"Ошибка", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	HMENU hmenu = LoadMenuW(wc.hInstance, MAKEINTRESOURCEW(IDR_MENU1));

	HWND hwnd = CreateWindowExW(NULL, L"SimpleClassName",
		L"Главное окно приложения. Программист Калевич Сергей",
		WS_OVERLAPPEDWINDOW,
		500, // положение окна (по горизонтали)
		150, // положение окна (по вертикали)
		600, // размеры окна (ширина)
		500, // размеры окна (высота)
		NULL,
		hmenu,
		wc.hInstance,
		NULL
	);
	if (!hwnd)
	{
		MessageBoxW(NULL, L"Окно не создано!",
			L"Ошибка", MB_OK | MB_ICONERROR);
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
// Оконная процедура
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