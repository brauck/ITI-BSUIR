// Change ACP value to 1251 in the registry (reget) by address:
// Computer\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Nls\CodePage

#define _USE_MATH_DEFINES
#include <iostream>
//#include <locale>
#include <math.h>
#include <Windows.h>
#include <math.h>
using namespace std;

int main() {
	// setlocale(LC_CTYPE, "Russian");	// ����������� ������� ��� ������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int x, y, z; 	// ���������� ����������
	cout << "������� ����� 2 �����: ";	// ����� �� ����� ���������
	cout << endl; 	// ������� ������ �� ������
	cin >> x >> y;	// ���� �������� ���������� ���������� � ����������
	z = M_PI * x * y; 	// ������ ������� � ������������� ����� ��
	cout << "��������� = " << z << endl;
	system("pause");	// �������� ������ �������� ������������
	// ��� ����� ������������ ������� getchar();

	return 0;
}
