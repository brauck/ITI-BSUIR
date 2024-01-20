// Lab #5
// task #2
#include <iostream>
#include <Windows.h> 
using namespace std;

const int offset = 48;
char S[161] = {};
char codeStr[161] = {};

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
	strcpy_s(S, "");

	int shift{};
	int Sindex{};
	int toTens{};
	int toOnes{};
	char letter{};	

	for (int i = 0; i < strlen(codeStr); i += shift)
	{
		if (codeStr[i] > 47 && codeStr[i] < 58)
		{
			shift = 2;
			cout << i << endl;
			toTens = int(codeStr[i]) - offset;
			toOnes = int(codeStr[i + 1]) - offset;
			letter = char(toTens * 10 + toOnes - 65);
			S[Sindex] = letter;
		}
		else
		{
			shift = 1;
			S[Sindex] = codeStr[i];
		}
		Sindex++;
	}
	S[Sindex] = '\0';
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
	fputs(S, file);
	fclose(file);
	cout << "Файл успешно сохранен" << endl;
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
	fgets(S, 160, file);
	fclose(file);
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

