// Lab #3
// task #2
// variant #4
#include <iostream>
#include <Windows.h>
using namespace std;

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool isSpace = true;
	int n{};
	cout << "Введите число от 0 до 20: ";
	cin >> n;
	if (n < 0 || n > 20)
	{
		cout << "Число должно быть в диапозоне от 0 до 20" << endl;
		system("pause");
		return;
	}
	int count = n;

	for (int i = 0, k = 0; i < n; i++, k++)
	{
        
		for (int j = 0; j < n; j++)
		{
			count--;
			if (!count) isSpace = false;
			if (isSpace) cout << ' ';
			else cout << '*';
		}
		count = n - k - 1;
		isSpace = true;
		cout << "\n";
	}

	system("pause");	
}