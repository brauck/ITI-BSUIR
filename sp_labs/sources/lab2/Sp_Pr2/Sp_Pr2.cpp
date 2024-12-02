#include <windows.h>
//-- Prototypes -------------------
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//-- Global Variables ------------
const WCHAR g_lpszClassName[] = L"sp_pr2_class";
const WCHAR g_lpszAplicationTitle[] = L"Главное окно приложения. Программист Калевич Сергей";
const WCHAR g_lpszDestroyMessage[] =
L"Поступило сообщение WM_DESTROY, из обработчика которого и выполнен данный вывод. "
"Сообщение поступило в связи с разрушением окна приложения";
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
	wc.lpszClassName = g_lpszClassName;
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIconW(wc.hInstance, IDI_APPLICATION); // значок окна с использованием системных значков
	wc.hCursor = LoadCursorW(NULL, IDC_ARROW); // форма курсора с использованием системных курсоров
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 127)); // цвет фона окна с использованием системных кистей
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBoxW(NULL, L"Ошибка регистрации класса окна!",
			L"Ошибка", MB_OK | MB_ICONERROR);
		return FALSE;
	}
	HWND hwnd = CreateWindowExW(NULL, g_lpszClassName,
		g_lpszAplicationTitle,
		WS_OVERLAPPEDWINDOW,
		500, // положение окна (по горизонтали)
		150, // положение окна (по вертикали)
		800, // размеры окна (ширина)
		300, // размеры окна (высота)
		NULL,
		NULL,
		hInstance,
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
	case WM_CREATE:
	{
		MessageBoxW(NULL, L"Выполняется обработка WM_CREATE", L"Создание окна", MB_OK);
		if (!hwnd) return -1;		
		HWND hButtonExit;
		if (!(hButtonExit = CreateWindowExW(0L, L"Button", L"Выход",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			680, 130, 80, 24, hwnd, (HMENU)(IDCANCEL),
			g_hInst, NULL))) return (-1);
	} return 0;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDCANCEL:
		{
			DestroyWindow(hwnd);
			return 0;
		}
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
		} 
	} return 0; // end WM_COMMAND
	
	case WM_LBUTTONDOWN:
	{
		const WCHAR mesText[] = L"Обработка сообщения WM_LBUTTONDOWN, "
			"которое посылается в окно при щелчке левой кнопки мыши";
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		HDC hdc = GetDC(hwnd);
		TextOutW(hdc, 50, 200, mesText, lstrlenW(mesText));
		RECT rect = {};
		rect.left = (long)LOWORD(lParam);
		rect.bottom = CW_USEDEFAULT;
		rect.right = CW_USEDEFAULT;
		rect.top = (long)HIWORD(lParam);
		DrawText(hdc, mesText, lstrlen(mesText), &rect, DT_LEFT);
		ReleaseDC(hwnd, hdc);
	} return 0;

	case WM_PAINT: // Вывод при обновлении окна
	{
		const WCHAR mesText[] = L"Обработка сообщения WM_PAINT. "
			"Это соообщение окно получает после того, "
			"как оно было закрыто другим окном и затем открыто.";
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hwnd, &ps); // Получение контекста для обновления окна
		TextOutW(hDC, 20, 100, mesText, lstrlen(mesText)); // Вывод в контекст
		EndPaint(hwnd, &ps); // Завершение обновления окна
	} return 0;

	case WM_DESTROY: // Завершение работы приложения
		MessageBoxW(hwnd, g_lpszDestroyMessage, L"Завершение работы", MB_OK);
		PostQuitMessage(5); // Посылка WM_QUIT приложению
		return 0;

	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}