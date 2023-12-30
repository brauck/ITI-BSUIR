// Lab #1
// Task #1
// Variant #4
#define _USE_MATH_DEFINES
#include <iostream>
#include <Windows.h>
#include <cmath>

using namespace std;

double absEpsilon = 1e-12;
double relEpsilon = 1e-8;
int testNum {};
double a{};

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
			
	for (int i = 0; i < 4; i++)
	{
		double z1 = formulaZ1(a);
		double z2 = formulaZ2(a);
		test(z1, z2);
		srand((unsigned)time(NULL) * (i+1) % 100);
		a = rand() % 63 / 10.0;					// Покрытие 360 градусов
	}
	
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
		cout << "Тест " << testNum << ":\na = " << a
			 << ":\nz1 = " << z1 << "\nz2 = " << z2 << "\nOK\n\n";
		return;
	} 
	testNum++;
	cout << "Тест " << testNum << ":\na = " << a
		 << ":\nz1 = " << z1 << "\nz2 = " << z2 << "\nNOT OK\n\n";
}