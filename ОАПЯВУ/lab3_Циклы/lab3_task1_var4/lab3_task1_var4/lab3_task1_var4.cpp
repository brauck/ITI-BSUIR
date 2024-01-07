// Lab #3
// Task #1
// Variant #4
#include <stdio.h>
#include <Windows.h>
#include <cmath>
using namespace std;

bool isZero = false;
double absEpsilon = 1e-12;
double relEpsilon = 1e-8;
bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon);
void isZeroDivision(double num);

double fXPlusPointFiveLessZeroAndCEquZero(double a, double b, double x)
{
	isZeroDivision(a * x);
	if (isZero) return 0;
	return 1 / (a * x) - b;
}

double fXPlusPointFiveGtrZeroAndCNotZero(double a, double x)
{
	isZeroDivision(x);
	if (isZero) return 0;
	return (x - a) / x;
}

double fDefault(double c, double x)
{
	isZeroDivision(c - 4);
	if (isZero) return 0;
	return (10 * x) / (c - 4);
}

double fFunc(double a, double b, double c, double x)
{
	if (x + 0.5 < 0 && c == 0)
		return fXPlusPointFiveLessZeroAndCEquZero(a, b, x);
	if (x + 0.5 > 0 && c != 0)
		return fXPlusPointFiveGtrZeroAndCNotZero(a, x);
	return fDefault(c, x);	
}

void printLine(int lineLength)
{
	for (int i = 0; i < lineLength; i++)
		printf("-");
    printf("\n");
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	float a{};
	float b{};
	float c{};

	double x{ -1 };
	printf("Введите три числа\n");
	scanf_s("%f%f%f", &a, &b, &c);
	printLine(25);
	printf("|     x     |     F     |\n");
	printLine(25);

	while (x < 1.000001)
	{		
		printf("|%9.2f  |%9.2f  |\n", x, fFunc(a, b, c, x));
		if (isZero)
		{
			printf("Деление на ноль\n\n");
			isZero = false;
		}
		x += 0.05;
	}

	printLine(25);
	
	system("pause");
	return 0;
}

bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
	double diff = fabs(a - b);
	if (diff <= absEpsilon)
		return true;
	return diff <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * relEpsilon);
}

void isZeroDivision(double num)
{
	if (approximatelyEqualAbsRel(num, 0, absEpsilon, relEpsilon))
	{
        isZero = true;
	}	
}