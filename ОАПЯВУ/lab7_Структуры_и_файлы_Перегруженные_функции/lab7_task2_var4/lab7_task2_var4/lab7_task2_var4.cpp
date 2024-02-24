// Lab #7
// task #2
// variant #4
#define _USE_MATH_DEFINES
#include <iostream>
#include <cstring>
#include <cmath>
#include <Windows.h>
#include <limits>
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
	bool isDefined{};
};


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

	system("cls");
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
	int num{};

	while (true)
	{
		system("cls");
		employeesList(employees);

		printf("\nДля просмотра информации о сотруднике: \n");
		printf("Введите номер сотрудника из списка: \n");
		printf("0 для выхода\n");
		cin >> num;

		if (!cin)
		{			
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Неверный ввод" << endl;
			system("pause");
			continue;
		}

		if (num < 0 || num > countDefinedEmployees)
		{
			cout << "Неверный ввод" << endl;
			system("pause");
			continue;
		}

		if (!num) return;

		system("cls");
		employeeData(employees[num - 1]);
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

	while (true)
	{
		system("cls");
		printf("Вывод данных\n");
		printf("****************\n");
		printf("1. Вывести список сотрудников\n");
		printf("2. Вывести все данные\n");
		printf("0. В главное меню\n");
		
		char menu[80];
		cin >> menu;
		switch (menu[0])
		{
		case '1': 
			showEmployeeList(employees);
			break;
		case '2':			
			showAllData(employees);
			break;
		case '0': return;
		default:
			printf("Неправильный пункт меню\n");
			system("pause");
		}
	}
}
//----------------------------------------------

// Добавление данных ---------------------------
void addData(Employee* employees)
{
	int i = countDefinedEmployees;
	system("cls");
	printf("Добавить нового сотрудника\n");
	printf("**************************\n");	

	bool continueAdd{true};
	while (continueAdd)
	{
		printf("1. Ввести данные\n");
		printf("0. В главное меню\n");
		char menu[80];
		cin >> menu;
		switch (menu[0])
		{
		case '1': continueAdd = false; break;
		case '0': return;
		default:
			printf("Неправильный пункт меню\n");
			system("pause");
			system("cls");
			printf("Добавить нового сотрудника\n");
			printf("**************************\n");
		}
	}

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
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("pause");
			return;
		case 2:
			printf("Введено не число\n");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("pause");
			return;
		}		
	}

	if (!employees[0].isDefined)
	{
		employees[i].employeeID = 1;
	}
	else
	{
		employees[i].employeeID =
			employees[i - 1].employeeID++;
	}
	employees[i].isDefined = true;
	countDefinedEmployees++;
	printf("Данные введены\n");
	system("pause");
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Employee* employees = new Employee[20];

	while (true)
	{
		system("cls");
		printf("Главное меню\n");
		printf("************\n");
		printf("1. Вывести данные на экран\n");
		printf("2. Добавить данные\n");
		printf("3. Удалить данные\n");
		printf("4. Редактировать данные\n");
		printf("5. Записать массив в файл (бинарный\n");
		printf("6. Считать массив из файла\n");
		printf("7. Выполнение задачи\n");
		printf("0. Выход\n");
		char menu[80];
		cin >> menu;
		switch (menu[0])
		{
		case '1': showData(employees); break;
		case '2': addData(employees); break;
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