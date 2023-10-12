#define _USE_MATH_DEFINES
#include <iostream>
//#include <locale>
#include <Windows.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

int main() {
	// setlocale(LC_CTYPE, "Russian");	// русификации консоли для ВЫВОДА
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand((unsigned)time(NULL));

	double a = rand() % 60 / 10.0;
	double  z1 = 0.0;
	double z2 = 0.0;

	// single sin(), cos()
	double ssin = sin(3 * M_PI - 2 * a);
	double scos = cos(5 * M_PI + 2 * a);

	z1 = 2 * ssin * ssin * scos * scos;
	z2 = (1 / 4.0) - (1 / 4.0) * sin((5 / 2.0) * M_PI - 8 * a);

	cout << z1 << '\n' << z2;
	
	return 0;
}