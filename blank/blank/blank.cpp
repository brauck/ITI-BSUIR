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
	// setlocale(LC_CTYPE, "Russian");	// русификации консоли для ВЫВОДА
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int x, y, z; 	// объявление переменных
	cout << "Введите целых 2 числа: ";	// вывод на экран сообщения
	cout << endl; 	// перевод строки на экране
	cin >> x >> y;	// ввод значений нескольких переменных с клавиатуры
	z = M_PI * x * y; 	// расчет формулы с использование числа Пи
	cout << "Результат = " << z << endl;
	system("pause");	// ожидание любого действия пользователя
	// Или можно использовать функцию getchar();

	return 0;
}
