#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <vector>
#include <string>

#define MAX_PATH_LENGTH 260

// ������� ��� �������� ����������� ���� � ������ �����
bool OpenFileDialog(char* filename) {
    OPENFILENAME ofn;       // ���������� ����
    char szFile[MAX_PATH] = ""; // ����� ��� ����� �����

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Text files\0*.TXT\0All files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE) {
        strcpy_s(filename, MAX_PATH, ofn.lpstrFile);
        return true;
    }
    return false;
}

// ������� ��� ������ ������ �� ����� � �������������� �������������
std::vector<std::string> ReadFileWithMemoryMapping(const char* filename) {
    HANDLE hFile = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening file.\n";
        return {};
    }

    // �������� ������ �����
    DWORD fileSize = GetFileSize(hFile, NULL);
    if (fileSize == INVALID_FILE_SIZE) {
        std::cerr << "Error getting file size.\n";
        CloseHandle(hFile);
        return {};
    }

    // ������� ����������� ����� � ������
    HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, fileSize, NULL);
    if (hMapping == NULL) {
        std::cerr << "Error creating file mapping.\n";
        CloseHandle(hFile);
        return {};
    }

    // ���������� ���������� ����� � ������
    char* pMap = (char*)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, fileSize);
    if (pMap == NULL) {
        std::cerr << "Error mapping view of file.\n";
        CloseHandle(hMapping);
        CloseHandle(hFile);
        return {};
    }

    // ������ ����� �� �����
    std::vector<std::string> names;
    std::string currentName;
    for (DWORD i = 0; i < fileSize; ++i) {
        if (pMap[i] == '\n') {
            if (!currentName.empty()) {
                names.push_back(currentName);
                currentName.clear();
            }
        }
        else {
            currentName += pMap[i];
        }
    }

    // ������� ��������
    UnmapViewOfFile(pMap);
    CloseHandle(hMapping);
    CloseHandle(hFile);

    return names;
}

// ������� ��� ������ ����� ������� � ����
void AppendNameToFile(const char* filename, const std::string& newName) {
    HANDLE hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening file.\n";
        return;
    }

    // ���������� ������ � ����� �����
    SetFilePointer(hFile, 0, NULL, FILE_END);

    // ���������� ������� � ����
    DWORD bytesWritten;
    WriteFile(hFile, newName.c_str(), newName.size(), &bytesWritten, NULL);
    WriteFile(hFile, "\n", 1, &bytesWritten, NULL);

    CloseHandle(hFile);
}

// �������� �������
int main() {
    char filename[MAX_PATH_LENGTH];

    // �������� ����� � ���������
    if (!OpenFileDialog(filename)) {
        std::cerr << "No file selected.\n";
        return -1;
    }

    // ������ ������� �� �����
    std::vector<std::string> names = ReadFileWithMemoryMapping(filename);

    // ����� ������� �� ����� (����� �������� �� ListBox � GUI)
    std::cout << "Current names in file:\n";
    for (const auto& name : names) {
        std::cout << name << "\n";
    }

    // ���������� ����� �������
    std::string newName;
    std::cout << "Enter a new name to add: ";
    std::getline(std::cin, newName);

    // ��������� ������� � ListBox (��� �� �����)
    std::cout << "Adding name: " << newName << "\n";

    // ���������� ������� � ����
    AppendNameToFile(filename, newName);

    return 0;
}
