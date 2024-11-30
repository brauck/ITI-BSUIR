#include <Windows.h>
#include "Sp_Pr1.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	/*
	LPCTSTR lpszHelloText = MESSAGE_TEXT;
	LPCTSTR lpszHeloWndTitle = MESSAGE_TITLE;
	MessageBox(NULL, MESSAGE_TEXT, MESSAGE_TITLE, MB_OK);
	*/

	/*
	SYSTEMTIME st;
	GetLocalTime(&st);
	TCHAR buf[200];
	LPCTSTR lpszHelloWndTitle = MESSAGE_TITLE;
	LPCTSTR lpszMsgText = TEXT("Привет из Win32 приложения с графическим интерфейсом.");
	LPCTSTR lpszAuthor = TEXT("Калевич Сергей");
	LPCTSTR designTime = TEXT("Design time = <09.10.2024 15:51>");
	wsprintf(buf, TEXT("%s\n%s\n%s\nRun time = <%2.2u.%2.2u.%u %2.2u:%2.2u"), lpszMsgText, lpszAuthor, designTime, st.wDay,
		st.wMonth, st.wYear, st.wHour, st.wMinute);

	MessageBox(NULL, buf, lpszHelloWndTitle, MB_OK);
	*/
	
	int iRetValue1, iRetValue2;
	LPCTSTR lpszMesBoxTitle = TEXT("Вариант 6");
	LPCTSTR lpszResponce;
	do {
		iRetValue1 = MessageBox(NULL, TEXT("The message box contains two push buttons: Yes and No."),
			lpszMesBoxTitle, MB_YESNO | MB_DEFBUTTON1 | MB_ICONERROR | MB_SETFOREGROUND);
		switch (iRetValue1)
		{
		case IDYES:
			lpszResponce = TEXT("Нажата кнопка Да (YES)");
			break;
		case IDNO:
			lpszResponce = TEXT("Нажата кнопка Нет (NO)");
			break;
		default: lpszResponce = TEXT("Ответ мне не понятен.");
		}
		TCHAR buf[200] = TEXT("");
		lstrcat(buf, lpszResponce);
		lstrcat(buf, TEXT("\nПродолжить изучение возвращаемых значений?"));
		iRetValue2 = MessageBox(NULL, buf, lpszMesBoxTitle,
			MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND);
	} while (iRetValue2 != IDNO);


	return 0;
}
