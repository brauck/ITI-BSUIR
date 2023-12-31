// Lab #2
// Task #3
// Variant #4
#define _USE_MATH_DEFINES
#include <iostream>
#include <Windows.h>

using namespace std;

double xEdge{ 1.0 };
double yBottom{ 2.0 };
double yTop{ 4.0 };

double numX{};
double numY{};

void test()
{
	cout << "Ожидаются плюсы" << endl;
	double array[][2] =
	{
		{1.0, 2.0},
		{1.0, 4.0},
		{2.0, 2.0},
		{1.0, 3.0},
		{2.7, 3.1},
		{100.2, 3.5},
		{0.0, 0.0},
		{0.9, 1.3},
		{1.2, 1.2},
		{1.2, 4.5}
	};
	double x{};
	double y{};

	int length = sizeof(array) / sizeof(array[0]);
	for (int i = 0; i < length; i++)
	{
		x = array[i][0];
		y = array[i][1];
		cout << x << ' ' << y << ' ';
		x < xEdge ? printf("МИНУС X\n")
			: y < yBottom ? printf("МИНУС yBottom\n")
			: y > yTop ? printf("МИНУС yTop\n") : printf("ПЛЮС\n");

		if (i == 5) cout << "\nОжидаются минусы" << endl;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);	

	test();

	cout << "\nВведите два числа" << endl;
	cin >> numX >> numY;
	numX < xEdge ? printf("")
		: numY < yBottom ? printf("")
		: numY > yTop ? printf("") : printf("ПЛЮС\n");
	
	system("pause");
	return 0;
}
