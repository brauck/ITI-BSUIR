// Lab #3
// Task #3
// Variant #4
#include <iostream>
#include <cmath>
using namespace std;

const int lineLength = 85;
const double a{ 0.1 };
const double b{ 1.0 };
const double h{ 0.1 };
const int n{ 20 };

void printLine()
{
	printf("  ");
	for (int i = 0; i < lineLength; i++)
		printf("-");
	printf("\n");
}

void printData(double x, double s, double y, double ys)
{
	printf("  |%11.1f%9c|%13.4f%7c|%13.4f%7c|%13.4f%7c|\n",
		x, ' ', s, ' ', y, ' ', ys, ' ');
	printLine();
}

long long factorial(int k)
{
	if (k == 1 || k == 0)
	{
		return 1;
	}
	else
	{
		return k * factorial(k - 1);
	}
}

double yX(double x) { return cos(x); }

double sX(double x)
{
	double accumulator{};
	double temp{};
	for (int k = 0; k <= n; k++)
	{
		temp = pow(-1, k) * pow(x, 2 * k) / (factorial(2 * k));
		accumulator += temp;
	}
	return accumulator;
}

int main()
{
	printLine();
	printf("  |%10c%10c|%12s%8c|%12s%8c|%16s%4c|\n",
		'x', ' ', "S(x)", ' ', "Y(x)", ' ', "| Y(x)-S(x) |", ' ');
	printLine();
    double s{};
	double y{};	
	double yXAbs{};
	for (double x = a; x <= b; x += h)
	{		
		s = sX(x);
		y = yX(x);
		yXAbs = fabs(y - s);
		printData(x, s, y, yXAbs);
	}
	system("pause");
	return 0;
}