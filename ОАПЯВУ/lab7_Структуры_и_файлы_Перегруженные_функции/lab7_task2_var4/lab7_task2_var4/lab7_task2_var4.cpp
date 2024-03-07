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

const int MAX{ 20 };              // Размер массива
const int overWork{ 144 };		  // Порог сверхурочного времени
const int incomeTax{ 10 };		  // Подоходный налог
const char extension[] =  ".bin";
const int cinFilenameLength{ 5 }; // Допустимый размер вводимого имени файла
const int getlineFilenameBuffer{ cinFilenameLength + 1 }; // + '\0'
const int fullFileNameBuffer{ cinFilenameLength + sizeof(extension) }; // + .bin
int countDefinedEmployees{};	  // Счетчик существующих сотрудников

struct Employee
{
	// Допустимый размер вводимой строки
	const static int cinLineLength{ 30 }; // без '\0'
	// Допустимый размер строки
	const static int lineLength = cinLineLength + 1; // +'\0'

	char lastName[lineLength]{};
	char name[lineLength]{};
	char patronymic[lineLength]{};
	int employeeID{};
	int workedHoursPerMonth{};
	int hourlyRate{};
	double salary{};
};

// Расчет заработной платы
double salary(int workedHours, int hourlyRate)
{
	double salary{};

	if (workedHours > overWork)
	{
		salary = overWork * hourlyRate +
			(workedHours - overWork) * hourlyRate * 2;
	}
	else
	{
		salary = workedHours * hourlyRate;
	}

	return (salary / 100) * (100 - incomeTax);
}

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
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
// Вывод всех данных о сотруднике
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
	printf("Заработная плата: %.2f\n", employee.salary);
}

// Вывод списка сотрудников (ФИО, табельный номер)
void employeesList(Employee* employees)
{
	printf("Список сотрудников\n");
	printf("******************\n");

	for (int i = 0; i < countDefinedEmployees; i++)
	{		
		printf("%3d. %s %s %s, табельный номер: %d\n",
			i + 1,
			employees[i].lastName,
			employees[i].name,
			employees[i].patronymic,
			employees[i].employeeID);
	}
}

// Вывод списка сотрудников
// с возможностью просмотра данных о сотруднике
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

// Показать всех сотрудников с подробными данными
void showAllData(Employee* employees)
{
	system("cls");
	printf("Все данные\n");
	printf("**********\n");

	for (int i = 0; i < countDefinedEmployees; i++)
	{
		printf("\n%d. \n", i + 1);
		employeeData(employees[i]);
	}
	system("pause");
}

// Меню вывода данных
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
// Меню добавления данных
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

// Добавление данных
void addData(Employee* employees)
{
	if (countDefinedEmployees == MAX)
	{
		printf("Штат заполнен\n");
		printf("Невозможно добавить нового сотрудника\n");
		system("pause");
		return;
	}

	const int i = countDefinedEmployees;	
	
	if (!addDataMenu()) return;
	
	printf("Допустимое количество вводимых символов: %d\n\n", Employee::cinLineLength);

	try
	{
		// cin.ignore();
		printf("Введите фамилию: ");
		cin.getline(employees[i].lastName, Employee::lineLength);
		if (!cin && cin.gcount() == Employee::cinLineLength) throw 1;

		printf("\nВведите имя: ");
		cin.getline(employees[i].name, Employee::lineLength);
		if (!cin && cin.gcount() == Employee::cinLineLength) throw 1;

		printf("\nВведите отчество: ");
		cin.getline(employees[i].patronymic, Employee::lineLength);
		if (!cin && cin.gcount() == Employee::cinLineLength) throw 1;

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
				Employee::cinLineLength);
			cinClear();
			system("pause");
			break;
		case 2:
			printf("Введено не число\n");
			cinClear();
			system("pause");
			break;
		}		
	}

	employees[i].salary =
		salary(employees[i].workedHoursPerMonth, employees[i].hourlyRate);

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

// Заполнение массива начальными данными
void fillEmloyeesArray(Employee* employees, int size)
{
	if (size > MAX)
	{
		printf("size > MAX\n");
		system("pause");
		return;
	}
	if (size < 0)
	{
		printf("size < 0\n");
		system("pause");
		return;
	}
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
		employees[i].salary =
			salary(employees[i].workedHoursPerMonth, employees[i].hourlyRate);

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
		printf("Выделение памяти не удалось: %s\n", e.what());
		printf("Данные не удалены\n");
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
		printf("Для подтверждения введите: 1\n");
		printf("Отмена: любой другой символ\n");

		cin >> option;
		if (!cin)
		{
			cinClear();
			continue;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
	Employee baseEmployee = employee;
	int option{};

	while (true)
	{	
		system("cls");
		employeeData(employee);

		printf("\n1. Изменить фамилию\n");
		printf("2. Изменить имя\n");
		printf("3. Изменить отчество\n");
		printf("4. Изменить количество проработанных часов за месяц\n");
		printf("5. Изменить почасовой тариф\n");
		printf("0. Выход\n");
		
		if (!cinOption(option)) continue;

		try
		{
			// cin.ignore();
;			switch (option)
			{
			case 1:
				printf("Введите новую фамилию (не более %d символов): ",
					Employee::cinLineLength);
				cin.getline(employee.lastName, Employee::lineLength);
				if (!cin && cin.gcount() == Employee::cinLineLength)
				{
					strcpy_s(employee.lastName, baseEmployee.lastName);
					throw 1;
				}
				printf("Фамилия изменена\n");
				system("pause");
				break;
			case 2:
				printf("Введите новое имя (не более %d символов): ",
					Employee::cinLineLength);
				cin.getline(employee.name, Employee::lineLength);
				if (!cin && cin.gcount() == Employee::cinLineLength)
				{
					strcpy_s(employee.name, baseEmployee.name);
					throw 1;
				}
				printf("Имя изменено\n");
				system("pause");
				break;
			case 3:
				printf("Введите новое отчество (не более %d символов): ",
					Employee::cinLineLength);
				cin.getline(employee.patronymic, Employee::lineLength);
				if (!cin && cin.gcount() == Employee::cinLineLength)
				{
					strcpy_s(employee.patronymic, baseEmployee.patronymic);
					throw 1;
				}
				printf("Отчество изменено\n");
				system("pause");
				break;
			case 4:
				printf("Введите количество проработанных часов: ");
				cin >> employee.workedHoursPerMonth;
				if (!cin)
				{
					employee.workedHoursPerMonth = baseEmployee.workedHoursPerMonth;
					throw 2;
				}
				printf("Количество проработанных часов изменено\n");
				employee.salary =
					salary(employee.workedHoursPerMonth, employee.hourlyRate);
				system("pause");
				break;
			case 5:
				printf("Введите новый почасовой тариф: ");
				cin >> employee.hourlyRate;
				if (!cin)
				{
					employee.hourlyRate = baseEmployee.hourlyRate;
					throw 2;
				}
				printf("Почасовой тариф изменен\n");
				employee.salary =
					salary(employee.workedHoursPerMonth, employee.hourlyRate);
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
				printf("Превышено допустимое количество вводимых символов: %d\n", Employee::cinLineLength);
				cinClear();
				system("pause");
				break;
			case 2:
				printf("Введено не число\n");
				cinClear();
				system("pause");
				break;
			}
		}
		baseEmployee = employee;
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

// Проверка корректности ввода имени файла
// Допустимо вводить с расширением ('.' и следующие за ней символы игнорируются)
bool filenameInput(char* filename)
{
	printf("Максимальная длина имени файла: %d\n", cinFilenameLength);
	char ch{};
	int i{};
	for (; i < getlineFilenameBuffer; i++)
	{
		cin.get(ch);
		if (ch == '\n')
		{
			filename[i] = '\0';
			strcat_s(filename, fullFileNameBuffer, extension);
			return true;
		}
		if (ch == '.')
		{
			filename[i] = '\0';
			strcat_s(filename, fullFileNameBuffer, extension);
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return true;
		}
		if (ch == '\\'
			|| ch == '/'
			|| ch == ':'
			|| ch == '*'
			|| ch == '?'
			|| ch == '\"'
			|| ch == '<'
			|| ch == '>'
			|| ch == '|')
		{
			printf("Имя файла не может содержать символы: \\ / : * ? \" < > |\n");
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return false;
		}
		
		filename[i] = ch;
	}
	printf("Превышена максимальная длина имени файла\n");
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return false;
}

// Запись массива в файл (бинарный) -------
void save(Employee* employees)
{
	char filename[fullFileNameBuffer]{};
	printf("Введите имя файла для сохранения: ");
	if (!filenameInput(filename))
	{
		printf("Данные не сохранены\n");
		system("pause");
		return;
	}

	char* b{ nullptr };
	FILE* file;

	if (fopen_s(&file, filename, "rb+"))
	{
		if (fopen_s(&file, filename, "wb"))
		{
			printf("Ошибка открытия файла: %s\n", filename);
			system("pause");
			return;
		}
	}
	else
	{
		printf("Файл с таким именем уже существует: %s\n", filename);
		printf("Перезаписать?:\n");
		printf("Да: введите 1\n");
		printf("Нет: любой другой символ\n");

		int option{};
		cin >> option;
		if (!cin)
		{
			cinClear();
			if (fclose(file))
			{
				printf("Ошибка закрытия файла: %s\n", filename);
				system("pause");
			}
			return;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (option != 1)
		{
			if (fclose(file))
			{
				printf("Ошибка закрытия файла: %s\n", filename);
				system("pause");				
			}
			return;
		}			
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
					printf("Ошибка закрытия файла: %s\n", filename);
				}
				system("pause");
				return;
			}
		}
	}
		
	printf("Данные сохранены в: %s\n", filename);

	if (fclose(file))
	{
		printf("Ошибка закрытия файла: %s\n", filename);
	}
	system("pause");
}
// ----------------------------------------------------------

// Считывание массива из файла ------------------------------
bool load(Employee* employees)
{	
	char filename[fullFileNameBuffer]{};
	printf("Введите имя файла для загрузки: ");
	if (!filenameInput(filename))
	{
		printf("Данные не загружены\n");
		system("pause");
		return false;
	}

	FILE* file;

	if (fopen_s(&file, filename, "rb"))
	{
		printf("Ошибка открытия файла: %s\n", filename);
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
			printf("Ошибка закрытия файла: %s\n", filename);
		}
		system("pause");
		return false;
	}

	printf("Данные загружены\n");

	if (fclose(file))
	{
		printf("Ошибка закрытия файла: %s\n", filename);
	}

	system("pause");
	return true;
}
// ----------------------------------------------------------

// Выполнение задачи (вариант: 4) ---------------------------
/* Рабочее время свыше 144 часов
считается сверхурочным и оплачивается в двойном размере.
ВЫВЕСТИ РАЗМЕР ЗАРАБОТНОЙ ПЛАТЫ
КАЖДОГО СОТРУДНИКА ФИРМЫ ЗА ВЫЧЕТОМ
ПОДОХОДНОГО НАЛОГА, КОТОРЫЙ СОСТАВЛЯЕТ
10 % ОТ СУММЫ ЗАРАБОТНОЙ ПЛАТЫ
(сортировать по убыванию заработной платы). */

// Функция сортировки 
void selectionSort(Employee* salaries)
{
	int maxSalaryIndex{};
	Employee tempEmployee{};

	for (int i = 0; i < countDefinedEmployees - 1; i++)
	{
		maxSalaryIndex = i;
		for (int j = i + 1; j < countDefinedEmployees; j++)
		{
			if (salaries[j].salary > salaries[maxSalaryIndex].salary)
			{
				maxSalaryIndex = j;
			}				
		}

		if (maxSalaryIndex != i)
		{
			tempEmployee = salaries[i];
			salaries[i] = salaries[maxSalaryIndex];
			salaries[maxSalaryIndex] = tempEmployee;
		}
	}
}

void sortSalaries(Employee* employees)
{
	Employee* salaries{ nullptr };
	try
	{
		salaries = new Employee[countDefinedEmployees];
	}
	catch (const bad_alloc& e)
	{
		printf("Выделение памяти не удалось: %s\n", e.what());
		printf("Динамический массив не создан\n");
		system("pause");
		exit(1);
	}

	for (int i = 0; i < countDefinedEmployees; i++)
	{
		salaries[i] = employees[i];
	}

	selectionSort(salaries);

	system("cls");
	printf("Сортированный список заработных плат (по убыванию)\n");
	printf("**************************************************\n");

	for (int i = 0; i < countDefinedEmployees; i++)
	{
		printf("%s %s %s\n",
			salaries[i].lastName,
			salaries[i].name,
			salaries[i].patronymic);
		printf("Заработная плата: %.2f\n\n", salaries[i].salary);
	}

	delete[] salaries;
	system("pause");
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Employee* employees{ nullptr };
	Employee* tempEmployees{ nullptr };
	try
	{
		employees = new Employee[MAX];
	}
	catch (const bad_alloc& e)
	{
		printf("Выделение памяти не удалось: %s\n", e.what());
		printf("Динамический массив не создан\n");
		system("pause");
		return 1;
	}

	fillEmloyeesArray(employees, 4);

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
		case 7:
			if (noData()) break;
			sortSalaries(employees);
			break;
		case 0:
			system("pause");
			return 0;
		default:
			printf("Неверный ввод\n");			
			system("pause");
		}
	}
}