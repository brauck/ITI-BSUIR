//приложение, запускающее через 15 секунд после старта
//программу Notepad.exe, в окне которой отображается номер срабатывания
//таймера : «Запуск № i», i = 1, 2, …10.Через 10 секунд после запуска программа
//Notepad закрывается.

#define _WIN32_WINDOWS 0x0410  
#define WINVER 0x0400

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void main(void)
{
	const int nTimerUnitsPerSecond = 10000000;
	int cAbrasionCount = 0;
	SYSTEMTIME st;
	LARGE_INTEGER li;
	char buffer[50];
	const char* fileName = "555.txt";
	FILE* file;
	wchar_t path[50] = L"C:\\Windows\\notepad.exe 555.txt";
	
	HANDLE procHandle = GetCurrentProcess();

	SECURITY_ATTRIBUTES sap, sat;//стр. атр. безоп. проц. и потока
	sap.nLength = sizeof(SECURITY_ATTRIBUTES);
	sap.lpSecurityDescriptor = nullptr;
	sap.bInheritHandle = FALSE;

	sat.nLength = sizeof(SECURITY_ATTRIBUTES);
	sat.lpSecurityDescriptor = nullptr;
	sat.bInheritHandle = FALSE;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	
	if (fopen_s(&file, fileName, "w"))
	{
		cout << "Ошибка открытия файла: " << fileName << endl;
		system("pause");
		return;
	}
	if (fclose(file))
	{
		cout << "Ошибка закрытия файла: " << fileName << endl;
		system("pause");
		return;
	}

	HANDLE hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	li.QuadPart = -(15 * nTimerUnitsPerSecond);
	if (SetWaitableTimer(hTimer, &li, 25 * 1000, NULL, NULL, FALSE)) {
		while (TRUE) {
			WaitForSingleObject(hTimer, INFINITE);

			if (!CreateProcess(NULL,   // No module name (use command line)
				path,        // Command line
				&sap,           // Process handle not inheritable
				&sat,           // Thread handle not inheritable
				FALSE,          // Set handle inheritance to FALSE
				0,              // No creation flags
				NULL,           // Use parent's environment block
				NULL,           // Use parent's starting directory 
				&si,            // Pointer to STARTUPINFO structure
				&pi)           // Pointer to PROCESS_INFORMATION structure
				)
			{
				printf("CreateProcess failed (%d).\n", GetLastError());
				return;
			}

			GetLocalTime(&st);
			cAbrasionCount++;
			int j = snprintf(buffer, 51, "Запуск №: %d \tВремя: %.2d:%.2d:%.2d\n", cAbrasionCount, st.wHour, st.wMinute, st.wSecond);
						

			if (fopen_s(&file, fileName, "a"))
			{
				cout << "Ошибка открытия файла: " << fileName << endl;
				system("pause");
				return;
			}
			fprintf(file, "%s \n", buffer);
			if (fclose(file))
			{
				cout << "Ошибка закрытия файла: " << fileName << endl;
				system("pause");
				return;
			}

			this_thread::sleep_for(chrono::seconds(10));
			system("taskkill /F /IM notepad.exe >nul");
		}
	}
}