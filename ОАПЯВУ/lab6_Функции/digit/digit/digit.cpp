// Lab #5
// task #1
#include <iostream>
#include <Windows.h>
using namespace std;

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int num[] = {17, 22, 35, 1, 2, 97};
	
	char str[80];
	FILE* file;
	char filename[50];
	cout << "Введите имя файла: ";
	cin >> filename;
	cin.ignore();
	if (fopen_s(&file, filename, "w"))
	{
		cout << "Ошибка открытия файла: " << filename << endl;
		return;
	}

	int length = sizeof num / sizeof num[0];
	cout << length << endl;

	for (int i = 0; i < length; i++)
	{
		fprintf(file, "%d\n", num[i]);
	}

	fclose(file);

	//FILE* file;
	//char filename[50];
	cout << "Введите имя файла: ";
	cin >> filename;
	cin.ignore();
	if (fopen_s(&file, filename, "r"))
	{
		cout << "Ошибка открытия файла: " << filename << endl;
		return;
	}
	fgets(str, 79, file);
	fclose(file);
	cout << "Строка считана" << endl;

	cout << str[1];
	/*int i = 1;
	while (true)
	{
		cout << i << ": ";
		gets_s(str, 79);
		if (strlen(str) == 2 && str[0] == '0' && str[1] == '0')
			break;
		fprintf(file, "%d %s \n", i, str);
		i++;
	}

	fclose(file);*/

	system("pause");
}