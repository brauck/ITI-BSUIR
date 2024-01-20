// Lab #5
// task #2
#include <iostream>
#include <Windows.h>
 
using namespace std;

char str[80];

void input()
{
	cout << "Введите строку: ";
	cin.ignore();
	gets_s(str, 79);
}

void output()
{
	cout << "Результирующая строка: ";
	cout << str << endl;
	system("pause");
}

void code()
{
	int Q = 256;
	int k = 13;
	char c1 = '\0';
	for (int i = 0; i < strlen(str); i++)
	{
		str[i] = c1 + (str[i] + k) % Q;
	}
	cout << "Строка зашифрована" << endl;
	system("pause");
}

void decode()
{
	int Q = 256;
	int k = 13;
	char c1 = '\0';
	for (int i = 0; i < strlen(str); i++)
	{
		str[i] = c1 + (str[i] - k) % Q;
	}
	cout << "Строка расшифрована" << endl;
	system("pause");
}

void save()
{
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
	fputs(str, file);
	fclose(file);
	cout << "Строка записана в файл" << endl;
	system("pause");
}

void load()
{
	FILE* file;
	char filename[50];
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
	system("pause");
}
void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int pr;

	while (true)
	{
		system("cls");
		cout << "( 1 ) ввод строки с клавиатуры" << endl;
		cout << "( 2 ) вывод строки на экран" << endl;
		cout << "( 3 ) зашифровать строку" << endl;
		cout << "( 4 ) расшифровать строку" << endl;
		cout << "( 5 ) записать строку в текстовый файл (имя файла задает пользователь)" << endl;
		cout << "( 6 ) считать строку из текстового файла (имя файла задает пользователь)" << endl;
		cout << "( 0 ) завершить работу" << endl;
		cin >> pr;
		
		switch (pr)
		{
		case 1: input(); break;
		case 2: output(); break;
		case 3: code(); break;
		case 4: decode(); break;
		case 5: save(); break;
		case 6: load(); break;
		case 0: return; 
		default: cout << "Команда неизвестна" << endl; break;			
		}

	}
}

