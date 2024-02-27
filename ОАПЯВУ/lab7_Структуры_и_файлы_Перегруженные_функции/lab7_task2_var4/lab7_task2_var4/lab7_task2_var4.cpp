﻿// Lab #7
// task #2
// variant #4
#define _USE_MATH_DEFINES
#include <iostream>
#include <cstring>
#include <cmath>
#include <Windows.h>
#include <limits>
#include <string>
#define _USE_MATH_DEFINES 
#undef max
using namespace std;

const int MAX{ 20 };
int countDefinedEmployees{};

struct Employee
{
	char lastName[30]{};
	char name[30]{};
	char patronymic[30]{};
	int employeeID{};
	int workedHoursPerMonth{};
	int hourlyRate{};
};

// Очистка cin.fail
void cinClear()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Проверка корректности ввода пункта списка
bool cinOption(int& option)
{
	cin >> option;
	if (!cin)
	{
		printf("Неверный ввод\n");
		cinClear();
		system("pause");
		return false;
	}
	return true;
}

// Вывод данных ----------------------------------------
void employeeData(const Employee& employee)
{
	printf("ФИО: %s %s %s\n",
		employee.lastName,
		employee.name,
		employee.patronymic);
	printf("Табельный номер: %d\n", employee.employeeID);
	printf("Количество проработанных часов за месяц: %d\n",
		employee.workedHoursPerMonth);
	printf("Почасовой тариф: %d\n", employee.hourlyRate);
}

void employeesList(Employee* employees)
{
	int count{ 1 };

	printf("Список сотрудников\n");
	printf("******************\n");

	for (int i = 0; i < countDefinedEmployees; i++)
	{		
		printf("%3d. %s %s %s, табельный номер: %d",
			count, employees[i].lastName,
			employees[i].name,
			employees[i].patronymic,
			employees[i].employeeID);

		cout << endl;
		count++;
	}
}

void showEmployeeList(Employee* employees)
{
	int option{};
	while (true)
	{
		system("cls");
		printf("\nДля просмотра информации о сотруднике: \n");
		printf("Введите номер сотрудника из списка: \n");
		printf("0 для выхода\n\n");
		
		employeesList(employees);

		if (!cinOption(option)) continue;

		if (option < 0 || option > countDefinedEmployees)
		{
			printf("Неверный ввод\n");
			system("pause");
			continue;
		}

		if (!option) return;

		system("cls");
		employeeData(employees[option - 1]);
		system("pause");		
	}
}

void showAllData(Employee* employees)
{
	int count{ 1 };

	system("cls");
	printf("Все данные\n");
	printf("**********\n");

	for (int i = 0; i < countDefinedEmployees; i++)
	{
		printf("%d. ",count);
		employeeData(employees[i]);
		cout << endl;
		count++;
	}
	system("pause");
}

void showData(Employee* employees)
{
	if (!countDefinedEmployees)
	{
		printf("Данные не вводились\n");
		system("pause");
		return;
	}

	int option{};
	while (true)
	{
		system("cls");
		printf("Вывод данных\n");
		printf("****************\n");
		printf("1. Вывести список сотрудников\n");
		printf("2. Вывести все данные\n");
		printf("0. В главное меню\n");
		
		if (!cinOption(option)) continue;

		switch (option)
		{
		case 1: 
			showEmployeeList(employees);
			break;
		case 2:			
			showAllData(employees);
			break;
		case 0: return;
		default:
			printf("Неверный ввод\n");
			system("pause");
		}
	}
}
//----------------------------------------------

// Добавление данных ---------------------------

bool addDataMenu()
{
	int option{};
	while (true)
	{
		system("cls");
		printf("Добавить нового сотрудника\n");
		printf("**************************\n");

		printf("1. Ввести данные\n");
		printf("0. В главное меню\n");

		if (!cinOption(option)) continue;

		switch (option)
		{
		case 1: return true;
		case 0: return false;
		default:
			printf("Неверный ввод\n");
			system("pause");
		}
	}
}

void addData(Employee* employees)
{
	if (countDefinedEmployees == 20)
	{
		printf("Штат заполнен\n");
		printf("Невозможно добавить нового сотрудника\n");
		system("pause");
		return;
	}

	int i = countDefinedEmployees;
	
	if (!addDataMenu()) return;
	
	int lineLength { 29 };
	printf("Допустимое количество вводимых символов: %d\n\n", lineLength);

	try
	{
		cin.ignore();
		printf("Введите фамилию: ");
		cin.getline(employees[i].lastName, 30);
		if (!cin && cin.gcount() == lineLength) throw 1;

		printf("\nВведите имя: ");
		cin.getline(employees[i].name, 30);
		if (!cin && cin.gcount() == lineLength) throw 1;

		printf("\nВведите отчество: ");
		cin.getline(employees[i].patronymic, 30);
		if (!cin && cin.gcount() == lineLength) throw 1;

		printf("\nВведите количество проработанных часов за месяц: ");
		cin >> employees[i].workedHoursPerMonth;
		if (!cin) throw 2;

		printf("Введите почасовой тариф: ");
		cin >> employees[i].hourlyRate;
		if (!cin) throw 2;
	}
	catch (int i)
	{
		switch (i)
		{
		case 1:
			printf("Превышено допустимое количество вводимых символов: %d\n", lineLength);
			cinClear();
			system("pause");
			return;
		case 2:
			printf("Введено не число\n");
			cinClear();
			system("pause");
			return;
		}		
	}

	if (employees[0].employeeID)
	{
		employees[i].employeeID = employees[i - 1].employeeID++;		
	}
	else
	{
		employees[i].employeeID = 1;
	}

	countDefinedEmployees++;
	printf("Данные введены\n");
	system("pause");
}

void fillEmloyeesArray(Employee* employees, int size)
{
	srand(time(0));
	int minHour{ 130 };
	int maxHour{ 160 };
	int minRate{ 10 };
	int maxRate{ 20 };	

	string names[20][3] =
	{
		{"Борисова", "Александра", "Артёмовна"},
		{"Королева", "Анна", "Михайловна"},
		{"Яковлев", "Лев", "Михайлович"},
		{"Киселев", "Михаил", "Лукич" },
		{"Калашникова", "Алёна", "Богдановна"},
		{"Платонова", "Анна", "Филипповна"},
		{"Кузнецова", "Анна", "Фёдоровна"},
		{"Зеленина", "Мария", "Фёдоровна"},
		{"Соболева", "Екатерина", "Арсентьевна"},
		{"Беляева", "Анна", "Алексеевна"},
		{"Ермаков", "Артём", "Борисович"},
		{"Корнилов", "Владимир", "Иванович"},
		{"Бобров", "Матвей", "Мирославович"},
		{"Усова", "Олеся", "Андреевна"},
		{"Раков", "Артём", "Даниилович"},
		{"Васильев", "Даниил", "Вячеславович"},
		{"Крылов", "Егор", "Георгиевич"},
		{"Журавлев", "Андрей", "Денисович"},
		{"Федотова", "Оливия", "Дмитриевна"},
		{"Дубровин", "Александр", "Ярославович"}
	};

	for (int i = 0; i < size; i++)
	{
		strcpy_s(employees[i].lastName, names[i][0].c_str());
		strcpy_s(employees[i].name, names[i][1].c_str());
		strcpy_s(employees[i].patronymic, names[i][2].c_str());		
		employees[i].employeeID = i + 1;
		employees[i].workedHoursPerMonth =
			minHour + rand() % (maxHour - minHour + 1);
		employees[i].hourlyRate =
			minRate + rand() % (maxRate - minRate + 1);

		countDefinedEmployees++;
	}
}
// ---------------------------------------

// Удаленее данных -----------------------
Employee* deleteData(Employee* employees, int index)
{
	Employee* tempEmployees = new Employee[20];

	for (int i = 0; i < index; i++)
	{
		tempEmployees[i] = employees[i];
	}

	for (int i = 0; i < countDefinedEmployees - index - 1; index++)
	{
		tempEmployees[index] = employees[index + 1];
	}

	countDefinedEmployees--;
	
	return tempEmployees;
}

Employee* deleteData(Employee* employees)
{
	int option{};
	int index{};
	while (true)
	{		
		system("cls");
		printf("\nДля удаления сотрудника: \n");
		printf("Введите номер сотрудника из списка: \n");
		printf("0 для выхода\n\n");

		employeesList(employees);
		
		if (!cinOption(option)) continue;

		if (option < 0 || option > countDefinedEmployees)
		{
			printf("Неверный ввод\n");
			system("pause");
			continue;
		}

		index = option - 1;
		if (!option) return employees;

		printf("Вы собираетесь удалить сотрудника:\n%s %s %s\n",
			employees[index].lastName,
			employees[index].name,
			employees[index].patronymic);
		printf("Для подтверждения нажмите 1\n");

		if (!cinOption(option)) continue;

		if (option == 1)
		{
			employees = deleteData(employees, index);
			printf("Сотрудник удален\n");
			system("pause");
		}
	}	
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Employee* employees = new Employee[20];
	Employee* tempEmployees = new Employee[20];
	fillEmloyeesArray(employees, 0);

	while (true)
	{		
		system("cls");
		cout << employees << endl;
		printf("Главное меню\n");
		printf("************\n");
		printf("1. Вывести данные на экран\n");
		printf("2. Добавить данные\n");
		printf("3. Удалить данные\n");
		printf("4. Редактировать данные\n");
		printf("5. Записать массив в файл (бинарный)\n");
		printf("6. Считать массив из файла\n");
		printf("7. Выполнение задачи\n");
		printf("0. Выход\n");

		int option{};
		if (!cinOption(option)) continue;

		switch (option)
		{
		case 1: showData(employees); break;
		case 2: addData(employees); break;
		case 3:
			if (!countDefinedEmployees)
			{
				printf("Данные не вводились\n");
				system("pause");
				break;
			}
			tempEmployees = deleteData(employees);
			delete[] employees;
			employees = tempEmployees;
			break;
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: break;
		case 0:
			system("pause");
			return 0;
		default:
			printf("Неверный ввод\n");			
			system("pause");
		}
	}
}