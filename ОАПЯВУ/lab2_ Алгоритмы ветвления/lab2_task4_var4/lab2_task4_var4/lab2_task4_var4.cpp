// Lab #2
// Task #4
// Variant #4
#define _USE_MATH_DEFINES
#include <iostream>
#include <Windows.h>
#include <cmath>

using namespace std;

double zLess1(double z)
{
	cout << "\nВычисление при z меньше единицы" << endl;
		
	return pow(z, 3) + 0.2;
}

double zEqualGreater1(double z)
{
	cout << "\nВычисление при z равной или больше единицы" << endl;
	return z + log10(z);
}

double yFormula(double z)
{	
	double x{};
	double y{};
	if (z < 1) x = zLess1(z);
	else x = zEqualGreater1(z);
	y = pow(cos(x * x), 3) + pow(sin(x * x * x), 2);
	cout << "при z = " << z << " y = " << y << endl;
	return y;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	double z{};

	yFormula(0.99);
	yFormula(0.0);
	yFormula(-0.52);
	yFormula(1.0);
	yFormula(1.57);
	yFormula(100.35);

	cout << "\nВведите число " << endl;
	cin >> z;
	yFormula(z);

	system("pause");
	return 0;
}
