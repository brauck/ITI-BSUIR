#define _USE_MATH_DEFINES
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <stdlib.h>

using namespace std;

double absEpsilon = 1e-12;
double relEpsilon = 1e-8;
int testNum = 0;
bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon);
void test(double z1, double z2);

double formulaZ1(double a)
{
	return cos(a) + sin(a) + cos(3 * a) + sin(3 * a);
}

double formulaZ2(double a)
{
	return 2 * pow(2, 0.5) * cos(a) * sin(M_PI / 4 + 2 * a);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
		
	// Задание 1
	cout << "Задание 1" << endl;
	for (int i = 0; i < 10; i++)
	{
		srand((unsigned)time(NULL) + i + 10);
		double a = rand() % 60 / 9.0;

		double z1 = formulaZ1(a);
		double z2 = formulaZ2(a);
		test(z1, z2);
	}
	

	// Задание 2
	cout << "Задание 2" << endl;
	double x = 4e3;
	double y = -0.875;
	double z = -4.75e-4;
	double w = 1.9873;
	
	double step = fabs(cos(x) - cos(y));
	step = pow(step, 1 + 2 * pow(sin(y), 2));
	step = step * (1 + z + (pow(z, 2) / 2) + (pow(z, 3) / 3) + (pow(z, 4) / 4));
	//cout << typeid(x).name() << endl;
	printf("%-22s %.4f \n", "Ожидаемый результат:", w);
	printf("%-22s %.4f \n", "Полученный результат:", step);

	system("pause");
	return 0;
}

// Источник: https://ravesli.com/urok-42-operatory-sravneniya/
// Возвращаем true, если разница между a и b меньше absEpsilon или в пределах relEpsilon 
bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
	// Проверяем числа на равенство их друг другу - это нужно в тех случаях,
	// когда сравниваемые числа являются нулевыми или "около нуля"
	double diff = fabs(a - b);
	if (diff <= absEpsilon)
		return true;

	// В противном случае возвращаемся к алгоритму Кнута
	return diff <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * relEpsilon);
}

void test(double z1, double z2)
{
	if (approximatelyEqualAbsRel(z1, z2, absEpsilon, relEpsilon))
	{
		testNum++;
		cout << "Тест " << testNum << ":\nz1 = " << z1 << "\nz2 = " << z2 << "\nOK\n\n";
		return;
	}
	testNum++;
	cout << "Тест " << testNum << ":\nz1 = " << z1 << "\nz2 = " << z2 << "\nNOT OK\n\n";
}