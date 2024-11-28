#include "Sp_Pr3HMSG.h"

// Global variables
// Дескрипторы дочерних окон
HWND hButtonSave;
HWND hButtonAdd;
HWND hButtonExit;
HWND hEdit;
HWND hListBox;

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
	// g_hInst = hInstance;

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"SimpleClassName";
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIconW(wc.hInstance, MAKEINTRESOURCEW(IDI_ICON1)); // значок окна с использованием системных значков
	wc.hCursor = LoadCursorW(NULL, /*MAKEINTRESOURCEW*/(IDC_ARROW)); // форма курсора с использованием системных курсоров
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
		L"Simple Application with Message handling",
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

	// BEGIN второе окно
	/*HWND hwnd2 = CreateWindowExW(NULL, L"SimpleClassName",
		L"2-е окно Simple Application with Message handling",
		WS_OVERLAPPEDWINDOW,
		600, // положение окна (по горизонтали)
		200, // положение окна (по вертикали)
		600, // размеры окна (ширина)
		500, // размеры окна (высота)
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
	ShowWindow(hwnd2, nCmdShow);
	UpdateWindow(hwnd2);*/
	// END второе окно

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
	/*int wmId, wmEvent;
	HDC hdc;*/

//	static HWND hButtonSave;
//	static HWND hButtonAdd;
//	static HWND hButtonExit;
//	static HWND hEdit;
//	static HWND hListBox;
//	#define IDC_BTN_SAVE	150
//	#define IDC_BTN_ADD		151
//	#define IDC_EDIT1		152
//	#define IDC_LISTBOX		153		
		
	switch (uMsg)
	{
		HANDLE_MSG(hwnd, WM_CREATE, WindowProc_OnCreate);
	/*case WM_CREATE:
	{
		if (!(hEdit = CreateWindowExW(0L, L"Edit", L"Редактор",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			20, 50, 160, 40, hwnd, (HMENU)(IDC_EDIT1),
			g_hInst, NULL))) return (-1);

		if (!(hListBox = CreateWindowExW(0L, L"ListBox",
			L"Список", WS_CHILD | WS_BORDER | WS_VISIBLE,
			200, 50, 160, 180, hwnd, (HMENU)(IDC_LISTBOX),
			g_hInst, NULL))) return (-1);

		if (!(hButtonSave = CreateWindowExW(0L, L"Button", L"В буфер",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			20, 240, 80, 24, hwnd, (HMENU)(IDC_BTN_SAVE),
			g_hInst, NULL))) return (-1);

		if (!(hButtonAdd = CreateWindowExW(0L, L"Button", L"В список",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			120, 240, 80, 24, hwnd, (HMENU)(IDC_BTN_ADD),
			g_hInst, NULL))) return (-1);

		if (!(hButtonExit = CreateWindowExW(0L, L"Button", L"Выход",
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			220, 240, 80, 24, hwnd, (HMENU)(IDCANCEL),
			g_hInst, NULL))) return (-1);
	} return 0;*/

	HANDLE_MSG(hwnd, WM_COMMAND, WindowProc_OnCommand);

	/*case WM_COMMAND:
	{
		const UINT32 textBufferSize = 500;
		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		static wchar_t pszTextBuff[textBufferSize] = {};
		switch (wmId)
		{
			// MENU BEGIN
		case IDM_FILE_OPEN:
		{
			MessageBoxW(hwnd, L"Выбрана команда открыть файл", L"Открыть файл", MB_OK);
		} return 0;

		case IDM_EDIT_SEL:
		{
			MessageBoxW(hwnd, L"Выбрана команда Выделить", L"Выделить текст", MB_OK);
		} return 0;

		case IDM_EDIT_COPY:
		{
			MessageBoxW(hwnd, L"Выбрана команда Копировать", L"Копировать", MB_OK);
		} return 0;

		case IDM_HELP_ABOUT:
		{
			MessageBoxW(hwnd, L"Выбрана команда О программе из меню Справка", L"О программе", MB_OK);
		} return 0;
			// MENU END

		case IDCANCEL:
			DestroyWindow(hwnd);
			return 0;
		case IDC_BTN_SAVE:
		{
			int cch;
			cch = SendMessageW(hEdit, WM_GETTEXT, (WPARAM)textBufferSize, (LPARAM)pszTextBuff);
			if (cch == 0)
			{
				MessageBoxW(hwnd, L"Введите текст", L"Читаем Edit", MB_OK);
				return 0;
			}
			else if (WM_GETTEXT > textBufferSize)
			{
				MessageBoxW(hwnd, L"Превышена максимальная длина текста", L"Читаем Edit", MB_OK | MB_ICONERROR);
				return 0;
			}
			else
			{
				wchar_t msgBuff[textBufferSize] = {};
				SYSTEMTIME st; GetSystemTime(&st);
				if (StringCchPrintfW(msgBuff, textBufferSize - 1, L"Время : %d ч %d мин %d сек\n",
					st.wHour, st.wMinute, st.wSecond) == S_OK)
				{
					if (StringCchCatW(msgBuff, textBufferSize - 1, L"Текст в памяти: ") == S_OK
						&& StringCchCatW(msgBuff, textBufferSize - 1, pszTextBuff) == S_OK)
					{
						MessageBoxW(hwnd, msgBuff, L"Содержимое буфера", MB_OK);
					}
					else
					{
						MessageBoxW(hwnd, L"Ошибка при конкатенации", L"Содержимое буфера", MB_OK | MB_ICONERROR);
					}					
				}
				else {
					MessageBoxW(hwnd, L"Превышена максимальная длина текста", L"Содержимое буфера", MB_OK | MB_ICONERROR);
				}
			}
		} return 0; //IDC_BTN_SAVE
		case IDC_BTN_ADD:
		{
			int ind;
			ind = SendMessageW(hListBox, LB_ADDSTRING,
				(WPARAM)0, (LPARAM)pszTextBuff);
			if (ind == LB_ERR)
				MessageBoxW(hwnd, L"Ошибка в списке", L"", MB_OK);
		} return 0; // end IDC_BTN_ADD
		default: //обработка по умолчанию для WM_COMMAND
			return DefWindowProcW(hwnd, uMsg, wParam, lParam);
		} // end switch(wmId)
	} return 0; // end WM_COMMAND*/
	
	HANDLE_MSG(hwnd, WM_LBUTTONDOWN, WindowProc_OnLButtonDown);

	/*
	case WM_LBUTTONDOWN:
	{
		const wchar_t mesText[] = L"Нажата левая кнопка мыши";
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		HDC hdc = GetDC(hwnd);
		TextOutW(hdc, x, y, mesText, lstrlenW(mesText)); // Вывод в контекст
		ReleaseDC(hwnd, hdc);
	} return 0;
	*/

	//=========================================
	HANDLE_MSG(hwnd, WM_PAINT, WindowProc_OnPaint);
	/*case WM_PAINT: // Вывод при обновлении окна
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hwnd, &ps); // Получение контекста для обновления окна 
		TextOutW(hDC, 10, 10, L"Hello, World!", 13); // Вывод в контекст
		EndPaint(hwnd, &ps); // Завершение обновления окна
	} return 0;*/

	HANDLE_MSG(hwnd, WM_DESTROY, WindowProc_OnDestroy);
	/*case WM_DESTROY: // Завершение работы приложения
		PostQuitMessage(0); // Посылка WM_QUIT приложению
		return 0;*/

	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}
