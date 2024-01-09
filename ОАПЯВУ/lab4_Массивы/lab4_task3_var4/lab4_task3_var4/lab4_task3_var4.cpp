// Lab #4
// task #3
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

	int array[10][10] = {};
	cout << "Введите два числа: ";
	cin >> A >> B;
	int range = B - A;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			array[i][j] = rand() % range + A;
		}
	}

	int count = 10;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%5d", array[i][j]);			
		}
		printf("\n");
	}

	printf("\nПоложительные строки:\n\n");	
	for (int i = 0; i < 10; i++)
	{   
		bool isNegative = false;		
		for (int j = 0; j < 10; j++)
		{
			if (array[i][j] < 0)
			{
				isNegative = true;
				break;
			}						
		}

		if (isNegative) continue;

		long long accumulator{ 1 };
		cout << "Строка " << i << ":";
		for (int j = 0; j < 10; j++)
		{	
			accumulator *= array[i][j];
			printf("%4d", array[i][j]);
		}
		printf("\n");	
		cout << "Произведение элементов строки " << i
			<< ": " << accumulator << "\n\n";
	}

	system("pause");
}