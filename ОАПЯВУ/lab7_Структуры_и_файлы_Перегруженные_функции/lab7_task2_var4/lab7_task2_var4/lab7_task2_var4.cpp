// Lab #7
// task #2
// variant #4
#define _USE_MATH_DEFINES
#include <iostream>
#include <Windows.h>
#include <limits>
#include <string>
#undef max
using namespace std;

const int MAX{ 20 };
const int overWork{ 144 };
const int maxFilenameLength{ 100 };
int countDefinedEmployees{};

struct Employee
{
	const static int lineLength{ 30 };

	char lastName[lineLength + 1]{};
	char name[lineLength + 1]{};
	char patronymic[lineLength + 1]{};
	int employeeID{};
	int workedHoursPerMonth{};
	int hourlyRate{};
};

// Очистка failbit
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

bool noData()
{
	if (!countDefinedEmployees)
	{
		printf("Данные не вводились\n");
		system("pause");
		return true;
	}
	return false;
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
			count,
			employees[i].lastName,
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
	int option{};
	while (true)
	{
		system("cls");
		printf("Вывод данных\n");
		printf("************\n");
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
	if (countDefinedEmployees == MAX)
	{
		printf("Штат заполнен\n");
		printf("Невозможно добавить нового сотрудника\n");
		system("pause");
		return;
	}

	int i = countDefinedEmployees;
	
	if (!addDataMenu()) return;
	
	printf("Допустимое количество вводимых символов: %d\n\n", Employee::lineLength);

	try
	{
		cin.ignore();
		printf("Введите фамилию: ");
		cin.getline(employees[i].lastName, 30);
		if (!cin && cin.gcount() == Employee::lineLength) throw 1;

		printf("\nВведите имя: ");
		cin.getline(employees[i].name, 30);
		if (!cin && cin.gcount() == Employee::lineLength) throw 1;

		printf("\nВведите отчество: ");
		cin.getline(employees[i].patronymic, 30);
		if (!cin && cin.gcount() == Employee::lineLength) throw 1;

		printf("\nВведите количество проработанных часов за месяц: ");
		cin >> employees[i].workedHoursPerMonth;
		if (!cin) throw 2;

		printf("\nВведите почасовой тариф: ");
		cin >> employees[i].hourlyRate;
		if (!cin) throw 2;
	}
	catch (int i)
	{
		switch (i)
		{
		case 1:
			printf("Превышено допустимое количество вводимых символов: %d\n",
				Employee::lineLength);
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
		employees[i].employeeID = employees[i - 1].employeeID + 1;		
	}
	else
	{
		employees[i].employeeID = 1;
	}

	countDefinedEmployees++;
	printf("\nСотрудник добавлен\n");
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
	Employee* tempEmployees{ nullptr };
	try
	{
		tempEmployees = new Employee[MAX];
	}
	catch (const bad_alloc& e)
	{
		cout << "Выделение памяти не удалось: " << e.what() << '\n';
		system("pause");
		exit(1);
	}

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
		if (!countDefinedEmployees)
		{
			printf("\nДанных больше не существует\n");
			system("pause");
			return employees;
		}
			
		system("cls");
		printf("Удаление сотрудника\n");
		printf("*******************\n");
		printf("\nДля удаления сотрудника: \n");
		printf("Введите номер сотрудника из списка\n");
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
// --------------------------------------------------

// Редактирование данных ----------------------------
void editData(Employee& employee)
{
	int lineLength{ 29 };
	int option{};

	while (true)
	{	
		system("cls");
		employeeData(employee);
		cout << endl;

		printf("1. Изменить фамилию\n");
		printf("2. Изменить имя\n");
		printf("3. Изменить отчество\n");
		printf("4. Изменить количество проработанных часов за месяц\n");
		printf("5. Изменить почасовой тариф\n");
		printf("0. Выход\n");
		
		if (!cinOption(option)) continue;

		try
		{
			cin.ignore();
;			switch (option)
			{
			case 1:
				printf("Введите новую фамилию (не более %d символов): ",
					Employee::lineLength);
				cin.getline(employee.lastName, 30);
				if (!cin && cin.gcount() == lineLength) throw 1;
				printf("Фамилия изменена\n");
				system("pause");
				break;
			case 2:
				printf("Введите новое имя (не более %d символов): ",
					Employee::lineLength);
				cin.getline(employee.name, 30);
				if (!cin && cin.gcount() == lineLength) throw 1;
				printf("Имя изменено\n");
				system("pause");
				break;
			case 3:
				printf("Введите новое отчество (не более %d символов): ",
					Employee::lineLength);
				cin.getline(employee.patronymic, 30);
				if (!cin && cin.gcount() == lineLength) throw 1;
				printf("Отчество изменено\n");
				system("pause");
				break;
			case 4:
				printf("Введите количество проработанных часов: ");
				cin >> employee.workedHoursPerMonth;
				if (!cin) throw 2;
				printf("Количество проработанных часов изменено\n");
				system("pause");
				break;
			case 5:
				printf("Введите новый почасовой тариф: ");
				cin >> employee.hourlyRate;
				if (!cin) throw 2;
				printf("Почасовой тариф изменен\n");
				system("pause");
				break;
			case 0:	return;
			default:
				printf("Неверный ввод\n");
				system("pause");
			}
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
	}

}

void editData(Employee* employees)
{
	int option{};
	int index{};
	while (true)
	{
		system("cls");
		printf("Редактирование данных сотрудника\n");
		printf("********************************\n");
		printf("\nДля редактирования данных сотрудника: \n");
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

		index = option - 1;
		editData(employees[index]);
	}
}
// ----------------------------------------

// Запись массива в файл (бинарный) -------
void save(Employee* employees)
{
	char filename[maxFilenameLength + 5]{}; // +(.bin + '\0')
	printf("Максимальная длина имени файла: %d\n", maxFilenameLength);
	printf("Введите имя файла для сохранения: ");
	cin.ignore();
	cin.getline(filename, maxFilenameLength + 1);

	if (!cin) cinClear();

	if (strlen(filename) > maxFilenameLength)
	{
		printf("Превышена максимальная длина имени файла\n");
		printf("Файл не сохранен\n");
		system("pause");
		return;
	}

	strcat_s(filename, maxFilenameLength + 5, ".bin");

	char* b{ nullptr };
	FILE* file;

	if (fopen_s(&file, filename, "wb"))
	{
		cout << "Ошибка открытия файла: " << filename << endl;
		system("pause");
		return;
	}

	for (int i = 0; i < MAX; i++)
	{
		b = (char*)&employees[i];

		for (int i = 0; i < sizeof(Employee); i++)
		{
			if (fputc(*(b++), file) == EOF)
			{
				printf("Ошибка записи в файл\n");
				if (fclose(file))
				{
					cout << "Ошибка закрытия файла: " << filename << endl;
				}
				system("pause");
				return;
			}
		}
	}
		
	printf("Данные сохранены в: %s\n", filename);

	if (fclose(file))
	{
		cout << "Ошибка закрытия файла: " << filename << endl;
	}
	system("pause");
}
// ----------------------------------------------------------

// Считывание массива из файла ------------------------------
bool load(Employee* employees)
{
	char filename[maxFilenameLength + 5]{}; // +(.bin + '\0')
	printf("Максимальная длина имени файла: %d\n", maxFilenameLength);
	printf("Введите имя файла для загрузки: ");
	cin.ignore();
	cin.getline(filename, maxFilenameLength + 1);

	if (!cin) cinClear();

	if (strlen(filename) > maxFilenameLength)
	{
		printf("Превышена максимальная длина имени файла\n");
		printf("Файл не считан\n");
		system("pause");
		return false;
	}

	strcat_s(filename, maxFilenameLength + 5, ".bin");

	FILE* file;

	if (fopen_s(&file, filename, "rb"))
	{
		cout << "Ошибка открытия файла: " << filename << endl;
		system("pause");
		return false;
	}
	if (
		fread_s(
			employees,
			sizeof(Employee) * MAX,
			sizeof(Employee),
			MAX,
			file) < MAX)
	{
		printf("Данные считаны неверно\n");
		if (fclose(file))
		{
			cout << "Ошибка закрытия файла: " << filename << endl;
		}
		system("pause");
		return false;
	}

	printf("Данные загружены\n");

	if (fclose(file))
	{
		cout << "Ошибка закрытия файла: " << filename << endl;
	}

	system("pause");
	return true;
}
// ----------------------------------------------------------

// Выполнение задачи (варианте: 4) --------------------------

/* Рабочее время свыше 144 часов
считается сверхурочным и оплачивается в двойном размере.
ВЫВЕСТИ РАЗМЕР ЗАРАБОТНОЙ ПЛАТЫ
КАЖДОГО СОТРУДНИКА ФИРМЫ ЗА ВЫЧЕТОМ
ПОДОХОДНОГО НАЛОГА, КОТОРЫЙ СОСТАВЛЯЕТ
10 % ОТ СУММЫ ЗАРАБОТНОЙ ПЛАТЫ
(сортировать по убыванию заработной платы). */


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	Employee* employees{ nullptr };
	Employee* tempEmployees{ nullptr };
	try
	{
		employees = new Employee[MAX];
		tempEmployees = new Employee[MAX];
	}
	catch (const bad_alloc& e)
	{
		cout << "Выделение памяти не удалось: " << e.what() << '\n';
		system("pause");
		return 1;
	}

	while (true)
	{		
		system("cls");
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
		case 1:
			if (noData()) break;
			showData(employees); break;
		case 2:	addData(employees); break;
		case 3:
			if (noData()) break;
			tempEmployees = deleteData(employees);
			if (tempEmployees == employees) break;
			delete[] employees;
			employees = tempEmployees;
			break;
		case 4:
			if (noData()) break;
			editData(employees);
			break;
		case 5:
			if (noData()) break;
			save(employees);
			break;
		case 6:
			if (load(employees))
			{
				for (int i = MAX - 1; i >= 0; i--)
				{
					if (employees[i].employeeID)
					{
						countDefinedEmployees = i + 1;
						break;
					}
				}
			}			
			break;
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