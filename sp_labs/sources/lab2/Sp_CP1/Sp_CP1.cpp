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
	wc.hIcon = LoadIconW(wc.hInstance, IDI_APPLICATION); // значок окна с использованием системных значков
	wc.hCursor = LoadCursorW(NULL, IDC_ARROW); // форма курсора с использованием системных курсоров
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // цвет фона окна с использованием системных кистей
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBoxW(NULL, L"Ошибка регистрации класса окна!",
			L"Ошибка", MB_OK | MB_ICONERROR);
		return FALSE;
	}
	HWND hwnd = CreateWindowExW(NULL, L"SimpleClassName",
		L"Главное окно приложения. Программист Калевич Сергей",
		WS_OVERLAPPEDWINDOW,
		500, // положение окна (по горизонтали)
		150, // положение окна (по вертикали)
		600, // размеры окна (ширина)
		320, // размеры окна (высота)
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
	static HWND hButtonGetInstance;
	static HWND hButtonClearEditor;
	static HWND hButtonExit;
	static HWND hEdit;
	#define IDC_BTN_GET			150 // получение и отображение значения дескриптора экземпляра приложения (hInstance)
	#define IDC_BTN_CLEAN		151 // очистка поля Edit
	#define IDC_EDIT1			152

	switch (uMsg)
	{
	case WM_CREATE:
	{
		if (!(hEdit = CreateWindowExW(0L, L"Edit", L"",
			WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VISIBLE,
			20, 50, 320, 100, hwnd, (HMENU)(IDC_EDIT1),
			g_hInst, NULL))) return (-1);

		if (!(hButtonGetInstance = CreateWindowExW(0L, L"Button", L"Получить hInstance",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			20, 240, 150, 24, hwnd, (HMENU)(IDC_BTN_GET),
			g_hInst, NULL))) return (-1);

		if (!(hButtonClearEditor = CreateWindowExW(0L, L"Button", L"Очистить редактор",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			190, 240, 150, 24, hwnd, (HMENU)(IDC_BTN_CLEAN),
			g_hInst, NULL))) return (-1);

		if (!(hButtonExit = CreateWindowExW(0L, L"Button", L"Выход",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			400, 240, 80, 24, hwnd, (HMENU)(IDCANCEL),
			g_hInst, NULL))) return (-1);
	} return 0;

	case WM_COMMAND:
	{
		const UINT32 textBufferSize = 500;				// размер сообщения в Edit
		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		static WCHAR msgBuff[textBufferSize] = {};		// выводимое сообщение в Edit
		static BOOL firstClick = FALSE;					// флаг первого клика
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
			LONG hinst = GetWindowLongW(hwnd, GWL_HINSTANCE); // значение дескриптора экземпляра приложения (hInstance)

			if (firstClick == FALSE)
			{
				if (msgBuff[0]) return 0; // если сообщение не пустое - значит первый клик уже был
				if (StringCchPrintfW(msgBuff, textBufferSize - 1, L"DEC: %d, HEX: %x",
					hinst, hinst) != S_OK)
				{				
					MessageBoxW(hwnd, L"NOT OK", L"Читаем hInstance",
						MB_OK | MB_ICONERROR);
					return 0;
				}
				firstClick = TRUE;
			}
			else
			{
				if (StringCchCatW(msgBuff, textBufferSize - 1, idc_btn_getToWchar) != S_OK)
				{
					MessageBoxW(hwnd, L"NOT OK", L"Добавить в hInstance",
						MB_OK | MB_ICONERROR);
					return 0;
				}
				firstClick = FALSE;
			}

			SendMessageW(hEdit, WM_SETTEXT, NULL, (LPARAM)msgBuff); // сообщение для заполнения поля Edit
			
		} return 0; 
		case IDC_BTN_CLEAN:
		{
			SendMessageW(hEdit, WM_SETTEXT, NULL, (LPARAM)L""); // очистка поля Edit
			if (StringCchPrintfW(msgBuff, textBufferSize - 1, L"") != S_OK) // сброс выводимого сообщения
			{
				MessageBoxW(hwnd, L"NOT OK", L"CLEAR", MB_OK | MB_ICONERROR);
			}
		} return 0; 

		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
		} // end switch(wmId)
	} return 0; // end WM_COMMAND	

	case WM_PAINT: // Вывод при обновлении окна
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hwnd, &ps); // Получение контекста для обновления окна 
		EndPaint(hwnd, &ps); // Завершение обновления окна
	} return 0;

	case WM_DESTROY: // Завершение работы приложения
		PostQuitMessage(0); // Посылка WM_QUIT приложению
		return 0;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}