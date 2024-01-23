// Lab #5
// task #2
#include <iostream>
#include <Windows.h> 
using namespace std;

const int offset = 48;

char S[241] = {};         // Если все вводимые значения цифры: 80 * 3 + '\0'
char codeStr[241]{};
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
	//char stringBuffer[241];
	//if (strlen(codeStr)) strcpy_s(codeStr, "");
	//strcpy_s(codeStr, _countof(stringBuffer), "");
	cout << strlen(codeStr) << ' ' << "yes" << endl;

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
		else if (S[i] > 47 && S[i] < 58) // Если вводимое значение цифра
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
	cout << strlen(codeStr) << endl;
	//codeStr[strlen(codeStr)] = '\0'; 
	strcpy_s(S, codeStr);
	cout << "Строка зашифрована" << endl;
	system("pause");
}

void decode()
{
	
}

void save()
{
	
}

void load()
{
	
}
void main()
{
	strcpy_s(codeStr, "");
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

