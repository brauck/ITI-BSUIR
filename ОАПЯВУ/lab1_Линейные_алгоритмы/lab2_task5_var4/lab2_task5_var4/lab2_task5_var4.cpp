// Lab #2
// Task #5
// Variant #4
#include <iostream>
#include <Windows.h>
#include <cmath>

using namespace std;

double divident(double x, double y, double z)
{
	return fmax(x + y + z, x * y * z);
}

double divisor(double x, double y, double z)
{
	return fmin(x + y + z, x * y * z);
}

double qFormula()
{
	bool isFirstIteration = true;
	bool isWrite = false;
	double x{};
	double y{};
	double z{};
	double q{};
	cout << "Введите три разных числа" << endl;
	while (!isWrite)
	{
		if (isFirstIteration) isFirstIteration = false;
		else cout << "Введите другие числа" << endl;
		cin >> x >> y >> z;		
		divisor(x, y, z) == 0 ? printf("Делитель равняется нулю\n")
			: isWrite = true;
		if (!isWrite) continue;
		x == y ? printf("Числа должны быть разными\n", isWrite = false)
			: x == z ? printf("Числа должны быть разными\n", isWrite = false)
			: y == z ? printf("Числа должны быть разными\n", isWrite = false)
			: isWrite = true;
	}
	q = divident(x, y, z) / divisor(x, y, z);
	cout << "q = " << q << endl;
	return q;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	qFormula();

	system("pause");
	return 0;
}
