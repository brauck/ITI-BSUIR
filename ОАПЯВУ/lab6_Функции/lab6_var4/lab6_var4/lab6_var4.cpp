// Lab #6
// task #2
#include <iostream>
#include <Windows.h>
using namespace std;

void noArguments();
bool byValue(int, int);
void byReference(int&, int, int);

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Функция 1 без аргументов" << endl;
	noArguments();

	cout << "\nФункция 2 принимает аргументы (по значению)" << endl;
	cout << "Введите два числа" << endl;
	int a{};
	int b{};
	int c{};
	cin >> a >> b;
	cout << "Проверить, имеют ли два аргумента разные знаки: "
		<< (byValue(a, b) ? "Да" : "Нет") << endl;	

	cout << "\nФункция 3 получает аргументы, "
		<< "вычисляет значение выражения "
		<< "и значение первого аргумента заменяет на полученный результат(по ссылке)."
		<< endl;
	cout << "Введите три числа" << endl;
	cin >> a >> b >> c;
	cout << "Начальное значение первого аргумента: " << a << endl;
	byReference(a, b, c);
	cout << "Максимум из 3-х чисел: " << a << endl;
	cout << "Конечное значение первого аргумента: " << a << endl;


	system("pause");
}

void noArguments()
{
	int sum{};
	for (int i = 24; i < 516; i++)
	{
		if (i % 2)
		{
			sum += i;
		}
	}
	cout << "Сумма всех нечетных чисел в диапазоне от 24 до 516: "
		<< sum << endl;
}

bool byValue(int a, int b) {
	/*
	* Предложенный способ: return a * b < 0; не работает,
	* если один из аргументов равен 0.
	*
	* Например:
	* Функция 2 принимает аргументы(по значению)
	* 	Введите два числа
	* 	-1 0
	* 	Проверить, имеют ли два аргумента разные знаки : Нет
	*/

	return (a < 0 || b < 0) && !(a < 0 && b < 0);
}

void byReference(int& a, int b, int c)
{
	int max{ a };
	if (b > max)
	{
		max = b;
	}
	if (c > max)
	{
		max = c;
	}
	a = max;
}