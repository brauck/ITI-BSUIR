// Lab #7
// task #2
// variant #4
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <Windows.h>
using namespace std;

struct Employee
{
	char name[30]{};
	char lastName[30]{};
	char patronymic[30]{};
	int employeeID{};
	int workedHoursPerMonth{};
	int hourlyRate{};
};



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	while (true)
	{
		system("cls");
		printf("Главное меню\n");
		printf("****************\n");
		printf("1. Вывести данные на экран\n");
		printf("2. Добавить данные\n");
		printf("3. Удалить данные\n");
		printf("4. редактировать данные\n");
		printf("5. Записать массив в файл (бинарный\n");
		printf("6. Считать массив из файла\n");
		printf("7. Выполнение задачи\n");
		printf("0. Выход\n");
		char menu[80];
		cin >> menu;
		switch (menu[0])
		{
		case '1': break;
		case '2': break;
		case '3': break;
		case '4': break;
		case '5': break;
		case '6': break;
		case '7': break;
		case '0':
			system("pause");
			return 0;
		default:
			printf("Неправильный пункт меню\n");
			system("pause");
		}
	}
	
}