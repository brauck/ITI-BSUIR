// Lab #5
// task #1
#include <iostream>
#include <Windows.h>
using namespace std;

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char str[80];
	FILE* file;
	char filename[50];
	cout << "Введите имя файла: ";
	cin >> filename;
	cin.ignore();
	if (fopen_s(&file, filename, "w"))
	{
		cout << "Ошибка открытия файла: " << filename << endl;
		return; //???????????????????
	}

	int i = 1;
	while (true)
	{
		cout << i << ": ";
		gets_s(str, 79);
		if (strlen(str) == 0)
			break;
		fprintf(file, "%d %s \n", i, str); 
		i++;
	}

	fclose(file);

	system("pause");
}