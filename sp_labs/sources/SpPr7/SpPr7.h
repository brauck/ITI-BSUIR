#pragma once
#include "framework.h"
#include <commdlg.h>
#include "resource.h"
#include "strsafe.h"

extern HINSTANCE hInst;                                // текущий экземпляр
extern WCHAR szTitle[];                  // Текст строки заголовка
extern WCHAR szWindowClass[];            // имя класса главного окна

HFONT APIENTRY MyFontCreate(void);
HFONT APIENTRY MyFontCreate2(HWND, HDC);
void MyDraw(HWND);
void DraweImage(HWND);
LPCTSTR MetaDraw();