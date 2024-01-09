// Lab #4
// task #2
// variant #4
#include <iostream>
#include <Windows.h>

using namespace std;

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int A{};
	int B{};

	int array[100] = {};
	cout << "Введите два числа: ";
	cin >> A >> B;
	int range = B - A;

	for (int i = 0; i < 100; i++)
	{
		array[i] = rand() % range + A;
	}

	int count = 10;
	for (int i = 0; i < 100; i++)
	{
		printf("%-6d", array[i]);
		if ((i + 1) % 10 == 0) printf("\n");
	}

	int min = array[0];
	int max = array[0];
	for (int i = 0; i < 99; i++)
	{
		if (array[i + 1] < min) min = array[i + 1];
		if (array[i + 1] > max) max = array[i + 1];
	}

	cout << "min: " << min << '\n' << "max: " << max
		<< "\nПроизведение min и max равно: " << min * max << endl;

	system("pause");
}