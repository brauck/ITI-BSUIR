#include <windows.h>
#include <tchar.h>
//-- Prototypes -------------------
LRESULT CALLBACK SimWndProc(HWND, UINT, WPARAM, LPARAM);
//-- Global Variables ------------
// Стартовая функция
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd;
	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = TEXT("SimpleClassName");
	wc.lpfnWndProc = SimWndProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_INFORMATION)); // значок окна с использованием системных значков
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_CROSS)); // форма курсора с использованием системных курсоров
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME + 1); // цвет фона окна с использованием системных кистей
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Ошибка регистрации класса окна!"),
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	hWnd = CreateWindowEx(NULL, TEXT("SimpleClassName"),
		TEXT("Simple Application with Message handling"),
		WS_OVERLAPPEDWINDOW,
		200, // положение окна (по горизонтали)
		100, // положение окна (по вертикали)
		500, // размеры окна (ширина)
		150, // размеры окна (высота)
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd)
	{
		MessageBox(NULL, TEXT("Окно не создано!"),
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
// Оконная процедура
LRESULT CALLBACK SimWndProc(HWND hWnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	switch (msg)
	{
	case WM_PAINT: // Вывод при обновлении окна
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps); // Получение контекста для
		// обновления окна 
		TextOut(hDC, 10, 10, TEXT("Hello, World!"), 13); // Вывод в контекст
		EndPaint(hWnd, &ps); // Завершение обновления окна
		break;

	case WM_DESTROY: // Завершение работы приложения
		PostQuitMessage(0); // Посылка WM_QUIT приложению
		break;

	default: // Вызов "Обработчика по умолчанию"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return FALSE;// Для ветвей с "break"
}
