#include "DlgTextViewMsgs.h"

BOOL DlgTextView_OnInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam)
{
    return TRUE;
}

void DlgTextView_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
    int wmId = id;
    int wmEvent = codeNotify;

    switch (wmId)
    {
    case IDCANCEL:
    {
        EndDialog(hDlg, id);
    } return;

    case IDOK:
    { // здесь сохраняем данные
        //GetDlgItemTextW(hDlg, IDC_EDIT1, retMessage, textBufferSize);
        EndDialog(hDlg, id);
    } return;

    // =========== Загрузка текста в поле Edit ==============
    case IDC_BTN_LOAD:
    {
        wchar_t pszFileName[300] = {};
        //StringCchCopyW(pszFileName, 299, L"D:\\lb5testUTF16LE.txt"); // L"D:\\lb5testUTF8.txt" lb5testUTF16LE
        //StringCchCopyW(pszFileTextBuff, fileBufferSize, pszFileName);

        //=======OPENFILENAME===================================
        OPENFILENAME ofn;   // структура для common dialog box

        //TCHAR lpszFileSpec[260];   // массив для имени файла

        //HWND hwnd;          // дескриптор окна–влвдельца

        //HANDLE hFile;       // дескриптор файла

//#define MAX_BYTES  10000

            //ТCHAR Buffer[MAX_BYTES] // буфер для текста



                //Иницализация OPENFILENAME

        ZeroMemory(&ofn, sizeof(OPENFILENAME));

        ofn.lStructSize = sizeof(OPENFILENAME);

        ofn.hwndOwner = hDlg;  // hwnd – дескриптор окна–влвдельца

        ofn.lpstrFile = pszFileName;

        ofn.lpstrFile[0] = '\0';

        ofn.nMaxFile = sizeof(pszFileName);

        // Формирование массива строк шаблонов фильтра

        ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";

        ofn.nFilterIndex = 1; // Индекс для текущего шаблона фильтра

        ofn.lpstrFileTitle = NULL; // Без заголовка

        ofn.nMaxFileTitle = 0;

        ofn.lpstrInitialDir = NULL; // В качестве начального текущий каталог

        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;



        // Отображение диалогового окна

        BOOL fRet = GetOpenFileName(&ofn);

        if (fRet == FALSE) return;//ошибка в далоге


        //==========================================
        HANDLE hFile;
        hFile = CreateFileW(pszFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        //hFile = CreateFileW(pszFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (hFile == INVALID_HANDLE_VALUE)
            return;
        DWORD cbReaded;
        BOOL f = ReadFile(hFile, pszFileTextBuff, fileBufferSize, &cbReaded, nullptr);
        SetDlgItemTextW(hDlg, IDC_EDIT_FILE, pszFileTextBuff);
    } return; //IDC_BTN_SAVE


    }
}