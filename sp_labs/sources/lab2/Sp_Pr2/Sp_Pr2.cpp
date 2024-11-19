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
	wc.hIcon = LoadIcon(wc.hInstance, IDI_APPLICATION); // значок окна с использованием системных значков
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // форма курсора с использованием системных курсоров
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // цвет фона окна с использованием системных кистей
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Ошибка регистрации класса окна!",
			L"Ошибка", MB_OK | MB_ICONERROR);
		return FALSE;
	}
	HWND hwnd = CreateWindowEx(NULL, L"SimpleClassName",
		L"Simple Application with Message handling",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, // положение окна (по горизонтали)
		CW_USEDEFAULT, // положение окна (по вертикали)
		CW_USEDEFAULT, // размеры окна (ширина)
		CW_USEDEFAULT, // размеры окна (высота)
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hwnd)
	{
		MessageBox(NULL, L"Окно не создано!",
			L"Ошибка", MB_OK | MB_ICONERROR);
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
// Оконная процедура
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		//=====================================
	case WM_LBUTTONDOWN:
		{
			const wchar_t mesText[] = L"Нажата левая кнопка мыши";
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			HDC hdc = GetDC(hwnd);
			TextOut(hdc, x, y, mesText, lstrlen(mesText)); // Вывод в контекст
			ReleaseDC(hwnd, hdc);
		}
		return 0;

	//=========================================
	case WM_PAINT: // Вывод при обновлении окна
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hwnd, &ps); // Получение контекста для обновления окна 
			TextOut(hDC, 10, 10, L"Hello, World!", 13); // Вывод в контекст
			EndPaint(hwnd, &ps); // Завершение обновления окна
		}
		return 0;

	case WM_DESTROY: // Завершение работы приложения
		PostQuitMessage(0); // Посылка WM_QUIT приложению
		return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}