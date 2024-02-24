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
using namespace std;

const int MAX{ 20 };
int ID{ 1 };
int countDefinedEmployees{};

struct Employee
{
	char lastName[30]{"sdfsfd"};
	char name[30]{"kjkj"};
	char patronymic[30]{"hjkl"};
	int employeeID{11};
	int workedHoursPerMonth{160};
	int hourlyRate{10};
	bool isDefined{true};
};

void employeeData(const Employee& employee)
{
	printf("%s %s %s\n", employee.lastName, employee.name, employee.patronymic);
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

	for (int i = 0; i < MAX; i++)
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

void showDetailEmployeeData(Employee* employees)
{
	int num{};

	while (true)
	{
		printf("\nПоказать подробную информацию о сотруднике\n");
		printf("Введите номер сотрудника из списка(0 для выхода): ");
		cin >> num;

		if (!cin || num < 0 || num > MAX)
		{			
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Неверный ввод" << endl;
			system("pause");
			system("cls");
			employeesList(employees);
			continue;
		}

		if (num == 0) return;

		system("cls");
		employeeData(employees[num - 1]);
		system("pause");

		system("cls");
		employeesList(employees);
	}
}

void showEmployeeList(Employee* employees)
{
	while (true)
	{
		employeesList(employees);
		showDetailEmployeeData(employees);
		return;
	}	
}

void showAllData(Employee* employees)
{
	int count{ 1 };

	system("cls");
	printf("Все данные\n");
	printf("****************\n");

	for (int i = 0; i < MAX; i++)
	{
		printf("%d. ",count);
		employeeData(employees[i]);
		cout << endl;
		count++;
	}
}

void showData(Employee* employees)
{
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
			system("pause");
			break;
		case '0': return;
		default:
			printf("Неправильный пункт меню\n");
			system("pause");
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Employee* employees = new Employee[20];
	/*showDetailEmployeeData(employees);
	system("pause");*/
	/*employeeData(employees[1]);
	system("pause");*/
	/*employeesList(employees);
	system("pause");*/

	while (true)
	{
		system("cls");
		printf("Главное меню\n");
		printf("****************\n");
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