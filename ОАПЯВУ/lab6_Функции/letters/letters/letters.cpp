﻿// Lab #5
// task #2
// variant #4
#include <iostream>
#include <cstring>
#include <Windows.h> 
using namespace std;

const int offset = 48;

char S[241] = {};         // Если все вводимые значения цифры: 80 * 3 + '\0'
char codeStr[241] = {};
char decodeStr[81] = {};


void input()
{
	cout << "Введите строку: ";
	cin.ignore();
	gets_s(S, 80);
}

void output()
{
	cout << "Результирующая строка: ";
	cout << S << endl;
	system("pause");
}

// Вариант 4: Буквы заменяются на их номер в алфавите
// Условно считаем: Прописные буквы: (А - Я) -> (01 - 32)
//                  Строчные буквы:  (а - я) -> (33 - 64)
void code()
{
	memset(codeStr, 0, sizeof(codeStr)); // обнуление строки

	int base{};
	int tens{};
	int ones{};
	int shift{};

	for (int i = 0; i < strlen(S); i++)
	{
		if (S[i] < 0)           // int('А') -> -64, int('я') -> -1
		{
			base = (S[i]) + 65;
			tens = base / 10;
			ones = base % 10;

			codeStr[shift] = char(tens + offset);
			codeStr[shift + 1] = char(ones + offset);

			shift += 2;
		}
		// Если вводимое значение цифра,
		// для индикации добавляем два нуля
		else if (S[i] > 47 && S[i] < 58)
		{
			codeStr[shift] = '0';
			codeStr[shift + 1] = '0';
			codeStr[shift + 2] = S[i];

			shift += 3;
		}
		else
		{
			codeStr[shift] = S[i];
			shift++;
		}
	}
	strcpy_s(S, codeStr);
	cout << "Строка зашифрована" << endl;
	system("pause");
}

void decode()
{
	int shift{};
	int decodeIndex{};
	int toTens{};
	int toOnes{};
	char letter{};

	for (int i = 0; i < strlen(S); i += shift)
	{
		if (S[i] == '0' && S[i + 1] == '0')
		{
			shift = 3;
			decodeStr[decodeIndex] = S[i + 2];
		}
		else if (S[i] > 47 && S[i] < 58)
		{
			shift = 2;
			toTens = int(S[i]) - offset;
			toOnes = int(S[i + 1]) - offset;
			letter = char(toTens * 10 + toOnes - 65);
			decodeStr[decodeIndex] = letter;
		}
		else
		{
			shift = 1;
			decodeStr[decodeIndex] = S[i];
		}
		decodeIndex++;
	}
	decodeStr[decodeIndex] = '\0';
	strcpy_s(S, decodeStr);
	cout << "Строка расшифрована" << endl;
	system("pause");
}

void save()
{
	errno_t err;

	FILE* file;
	char filename[50];
	cout << "Введите имя файла: ";
	cin >> filename;
	cin.ignore();
	strcat_s(filename, 50, ".txt");
	err = fopen_s(&file, filename, "w");
	if (err == 0)
	{
		printf("Файл %s открыт\n", filename);
	}
	else
	{
		printf("Ошибка открытия файла: %s\n", filename);
		system("pause");
		return;
	}
	fputs(S, file);
	if (file)
	{
		err = fclose(file);
		if (err == 0)
		{
			printf("Файл %s закрыт\n", filename);
		}
		else
		{
			printf("Ошибка закрытия файла: %s\n", filename);
		}
	}
	cout << "Файл успешно сохранен" << endl;
	system("pause");
}

void load()
{
	errno_t err;

	FILE* file;
	char filename[50];
	cout << "Введите имя файла: ";
	cin >> filename;
	cin.ignore();
	err = fopen_s(&file, filename, "r");
	if (err == 0)
	{
		printf("Файл %s открыт\n", filename);
	}
	else
	{
		printf("Ошибка открытия файла: %s\n", filename);
		system("pause");
		return;
	}
	fgets(S, 240, file);
	if (file)
	{
		err = fclose(file);
		if (err == 0)
		{
			printf("Файл %s закрыт\n", filename);
		}
		else
		{
			printf("Ошибка закрытия файла: %s\n", filename);
		}
	}
	cout << "Файл успешно прочитан" << endl;
	system("pause");
}
void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int option;

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
		cin >> option;

		switch (option)
		{
		case 1: input(); break;
		case 2: output(); break;
		case 3: code(); break;
		case 4: decode(); break;
		case 5: save(); break;
		case 6: load(); break;
		case 0: cout << "Сеанс окончен!" << endl; return;
		default: cout << "Команда неизвестна" << endl;
			system("pause");
			break;
		}
	}
}

