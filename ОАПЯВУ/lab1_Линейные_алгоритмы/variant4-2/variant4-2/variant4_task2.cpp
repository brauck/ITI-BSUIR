// Lab #1
// task #2
// Variant #4
#include <iostream>
#include <Windows.h>
#include <cmath>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

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