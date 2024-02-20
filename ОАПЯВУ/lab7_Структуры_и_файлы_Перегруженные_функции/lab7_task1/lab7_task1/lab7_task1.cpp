// Lab #7
// task #1
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <Windows.h>
using namespace std;

const int MAX = 20;

struct Circle
{
	int x, y, radius;
	bool isDefined{ false };
} circle;

struct Cube
{
	double vertexes[8][3] =
	{
		{NULL, NULL, NULL}, // A
		{NULL, NULL, NULL}, // B
		{NULL, NULL, NULL}, // C
		{NULL, NULL, NULL}, // D
		{NULL, NULL, NULL}, // E
		{NULL, NULL, NULL}, // F
		{NULL, NULL, NULL}, // G
		{NULL, NULL, NULL}  // H
	};
	double edgeLength;
	bool isDefined{ false };
} cube;

void drawCube()
{
	printf("%25s\n", "      H-------------G");
	printf("%25s\n", "     /'            /|");
	printf("%25s\n", "    / '           / |");
	printf("%25s\n", "   /  '          /  |");
	printf("%25s\n", "  E---+---------F   |");
	printf("%25s\n", "  |   '         |   |");
	printf("%25s\n", "  |   D -  -  - | - C");
	printf("%25s\n", "  |  '          |  / ");
	printf("%25s\n", "  | '           | /  ");
	printf("%25s\n", "  |'            |/   ");
	printf("%25s\n\n", "A-------------B    ");
}

//Circle circle;
//Cube cube;

double absEpsilon{ 1e-12 };
double relEpsilon{ 1e-8 };
bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
	double diff = fabs(a - b);
	if (diff <= absEpsilon)
		return true;

	return diff <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * relEpsilon);
}

bool isFigure(const Circle& circle)
{
	if (circle.radius > 0) return true;

	cout << "Окружность не создана: "
		<< "значение радиуса должно быть больше нуля" << endl;
	system("pause");	
	return false;	
}

double twoPointsDistance(int x1, int y1, int z1, int x2, int y2, int z2)
{
	return sqrt(
		pow(x2 - x1, 2) +
		pow(y2 - y1, 2) +
		pow(z2 - z1, 2)
	);
}

// Проверка все ли ребра куба равны
bool isCubeEdgesEqual(const Cube& cube)
{	
	double tempCubeEdgeLength{};
	bool isEdgesEqual{ true };
    int count{};
	int offset{1};
	
	for (int i = 0; i < 8; i++)
	{
		// Ребра AB, BC, CD, EF, FG, GH
		tempCubeEdgeLength = twoPointsDistance(
			cube.vertexes[i][0],
			cube.vertexes[i][1],
			cube.vertexes[i][2],
			cube.vertexes[i + offset][0],
			cube.vertexes[i + offset][1],
			cube.vertexes[i + offset][2]
		);
		cout << '\n' << tempCubeEdgeLength << ' ' << cube.edgeLength << endl;
		if (!approximatelyEqualAbsRel(
			tempCubeEdgeLength,
			cube.edgeLength,
			absEpsilon,
			relEpsilon)
			)
		{
			cout << "in false" << endl;
			isEdgesEqual = false;
			break;
		}
	
		if (count < 2)
		{
			count++;
			continue;
		}

		i++;

		// Ребра AD, EH
		offset = -3;
		tempCubeEdgeLength = twoPointsDistance(
			cube.vertexes[i][0],
			cube.vertexes[i][1],
			cube.vertexes[i][2],
			cube.vertexes[i + offset][0],
			cube.vertexes[i + offset][1],
			cube.vertexes[i + offset][2]
		);

		if (!approximatelyEqualAbsRel(
			tempCubeEdgeLength,
			cube.edgeLength,
			absEpsilon,
			relEpsilon)
			)
		{
			isEdgesEqual = false;
			break;
		}
		count = 0;
		offset = 1;
	}

	// Ребра AE, BF, CG, DH
	offset = 4;
	for (int i = 0; i < 4; i++)
	{
		tempCubeEdgeLength = twoPointsDistance(
			cube.vertexes[i][0],
			cube.vertexes[i][1],
			cube.vertexes[i][2],
			cube.vertexes[i + offset][0],
			cube.vertexes[i + offset][1],
			cube.vertexes[i + offset][2]
		);

		if (!approximatelyEqualAbsRel(
			tempCubeEdgeLength,
			cube.edgeLength,
			absEpsilon,
			relEpsilon)
			)
		{
			isEdgesEqual = false;
			break;
		}
	}
	
	if (isEdgesEqual) return true;
	return false;
}

// Проверка все ли грани куба являются квадратами
bool isAllFacesSquares(const Cube& cube)
{
	double isoscelesRightTriangleHypotenuse = sqrt(
		2 * pow(cube.edgeLength, 2)
	);

	bool isDiagonalsEqual{ true };
	double tempFaceDiagonal{};
	int offset{5};
	// Диагонали AF, BG, CH
	for (int i = 0; i < 3; i++)
	{
		tempFaceDiagonal = twoPointsDistance(
			cube.vertexes[i][0],
			cube.vertexes[i][1],
			cube.vertexes[i][2],
			cube.vertexes[i + offset][0],
			cube.vertexes[i + offset][1],
			cube.vertexes[i + offset][2]
		);

		if (!approximatelyEqualAbsRel(
			tempFaceDiagonal,
			isoscelesRightTriangleHypotenuse,
			absEpsilon,
			relEpsilon)
			)
		{
			isDiagonalsEqual = false;
			break;
		}
	}

	// грань DE
	tempFaceDiagonal = twoPointsDistance(
		cube.vertexes[3][0],
		cube.vertexes[3][1],
		cube.vertexes[3][2],
		cube.vertexes[4][0],
		cube.vertexes[4][1],
		cube.vertexes[4][2]
	);

	if (!approximatelyEqualAbsRel(
		tempFaceDiagonal,
		isoscelesRightTriangleHypotenuse,
		absEpsilon,
		relEpsilon)
		)
	{
		isDiagonalsEqual = false;
	}
	
	// Диагонали AC, EG
	offset = 2;	
	for (int i = 0; i < 5; i +=4)
	{
		tempFaceDiagonal = twoPointsDistance(
			cube.vertexes[i][0],
			cube.vertexes[i][1],
			cube.vertexes[i][2],
			cube.vertexes[i + offset][0],
			cube.vertexes[i + offset][1],
			cube.vertexes[i + offset][2]
		);

		if (!approximatelyEqualAbsRel(
			tempFaceDiagonal,
			isoscelesRightTriangleHypotenuse,
			absEpsilon,
			relEpsilon)
			)
		{
			isDiagonalsEqual = false;
			break;
		}
	}

	if (isDiagonalsEqual) return true;
	return false;
}

bool isFigure(const Cube& cube)
{
	if (!isCubeEdgesEqual(cube))
	{
		cout << "Куб не создан: " << "все ребра должны быть равны" << endl;
		system("pause");
		return false;
	}

	if (!isAllFacesSquares(cube))
	{
		cout << "Куб не создан: " << "все грани должны быть квадратами" << endl;
		system("pause");		
		return false;
	}

	return true;
}

void createFigure(Circle& circle)
{
	circle.isDefined = false;
	cout << "Введите координаты центра окружности (x y): ";
	cin >> circle.x >> circle.y;
	cout << "Введите радиус: ";
	cin >> circle.radius;
	
	if (isFigure(circle)) circle.isDefined = true;
}

void createFigure(Cube& cube)
{
	/*0 0 0
	11 0 0
	11 0 11
	0 0 11
	0 11 0
	11 11 0
	11 11 11
	0 11 11*/

	/*0 0 0
	11 0 0
	11 0 11
	0 0 11
	0 110 0
	11 110 0
	11 110 11
	0 110 11*/

	cube.isDefined = false;
	char vertex{ 'A' };
	drawCube();	
	for (int i = 0; i < 8; i++)
	{
		cout << "Введите координаты вершины " << vertex++ << " (x y z): ";
		cin >> cube.vertexes[i][0] >> cube.vertexes[i][1] >> cube.vertexes[i][2];
	}

	// Ребро AB
	cube.edgeLength = twoPointsDistance(
		cube.vertexes[0][0],
		cube.vertexes[0][1],
		cube.vertexes[0][2],
		cube.vertexes[1][0],
		cube.vertexes[1][1],
		cube.vertexes[1][2]
	);

	if (isFigure(cube))  cube.isDefined = true;
}

double perimeter(const Circle& circle)
{
	return 2 * M_PI * circle.radius;
}

double perimeter(const Cube& cube)
{
	return cube.edgeLength * 12;
}

double square(const Circle& circle)
{
	return M_PI * pow(circle.radius, 2);
}

double square(const Cube& cube)
{
	return pow(cube.edgeLength, 2) * 6;
}

double volume(const Cube& cube)
{
	return pow(cube.edgeLength, 3);
}

void info(const Circle& circle)
{
	if (!circle.isDefined)
	{
		cout << "Окружность неопределена" << endl;
		cout << "Создайте окружность" << endl;
		system("pause");
		return;
	}
	cout << "Координаты центра окружности: "
		<< '(' << circle.x << ", " << circle.y << ')' << endl;
	cout << "Радиус окружности: " << circle.radius << endl;
	cout << "Длина окружности: " << perimeter(circle) << endl;
	cout << "Площадь круга: " << square(circle) << endl;

	system("pause");
}

void info(const Cube& cube)
{
	if (!cube.isDefined)
	{
		cout << "Куб неопределен" << endl;
		cout << "Создайте куб" << endl;
		system("pause");
		return;
	}
	drawCube();
	char vertex = 'A';
	cout << "Координаты вершин куба: " << endl;	
	for (int i = 0; i < 8; i++)
	{
		cout << "Координаты вершины " << vertex++ << ": ";
	    cout << '(' << cube.vertexes[i][0] << ", "
			<< cube.vertexes[i][1] << ", "
			<< cube.vertexes[i][2] << ')';
		cout << endl;
	}

	cout << "Длина ребра куба: " << cube.edgeLength << endl;
	cout << "Периметр ребер куба: " << perimeter(cube) << endl;
	cout << "Площадь куба: " << square(cube) << endl;
	cout << "Объем куба: " << volume(cube) << endl;

	system("pause");
}

void showInfo()
{
	while (true)
	{
		system("cls");
		printf("1. Получить информацию об окружности\n");
		printf("2. Получить информацию о кубе\n");
		printf("0. В главное меню\n");

		char menu[80];
		cin >> menu;
		switch (menu[0])
		{
		case '1': info(circle); break;
		case '2': info(cube); break;
		case '0': return;
		default:
			printf("Неправильный пункт меню\n");
			system("pause");
		}
	}
}

void setFigure()
{
	while (true)
	{
		system("cls");
		printf("1. Создать окружность\n");
		printf("2. Создать куб\n");
		printf("0. В главное меню\n");
		
		char menu[80];
		cin >> menu;
		switch (menu[0])
		{
		case '1': createFigure(circle); return;
		case '2': createFigure(cube); return;
		case '0': return;
		default:
			printf("Неправильный пункт меню\n");
			system("pause");
		}
	}
}

void save(Circle& circle)
{
	printf("Выбранная фигура: окружность\n");
	cout << "Введите имя файла для сохранения (без .bin): ";
	char* b{ nullptr };
	FILE* file;
	char filename[100];	
	cin >> filename;
	strcat_s(filename, 100, ".bin");
	if (fopen_s(&file, filename, "wb"))
	{
		cout << "Ошибка открытия файла: " << filename << endl;
		system("pause");
		return;
	}

	if (circle.isDefined)
	{
		b = (char*)&circle;

		for (int i = 0; i < sizeof(circle); i++)
		{
			fputc(*(b++), file);
		}
		printf("Данные сохранены\n");

		if (fclose(file))
		{
			cout << "Ошибка закрытия файла: " << filename << endl;
		}
		system("pause");
		return;
	}
	else
	{
		printf("Структура окружности не вводилась\n");
	}
	if (fclose(file))
	{
		cout << "Ошибка закрытия файла: " << filename << endl;
	}
	system("pause");
}

void save(Cube& cube)
{
	printf("Выбранная фигура: куб\n");
	cout << "Введите имя файла для сохранения (без .bin): ";
	char* b{ nullptr };
	FILE* file;
	char filename[100];
	cin >> filename;
	strcat_s(filename, 100, ".bin");
	if (fopen_s(&file, filename, "wb"))
	{
		cout << "Ошибка открытия файла: " << filename << endl;
		system("pause");
		return;
	}

	if (cube.isDefined)
	{
		printf("Выбранная фигура: куб\n");
		b = (char*)&cube;

		for (int i = 0; i < sizeof(cube); i++)
		{
			fputc(*(b++), file);
		}
		printf("Данные сохранены\n");

		if (fclose(file))
		{
			cout << "Ошибка закрытия файла: " << filename << endl;
		}
		system("pause");
		return;
	}
	else
	{
		printf("Структура куба не вводилась\n");
	}
	if (fclose(file))
	{
		cout << "Ошибка закрытия файла: " << filename << endl;
	}
	system("pause");
}

void save()
{
	while (true)
	{
		system("cls");
		printf("1. Сохранить окружность\n");
		printf("2. Сохранить куб\n");
		printf("0. В главное меню\n\n");
		
		char menu[80];
		cin >> menu;
		switch (menu[0])
		{
		case '1': save(circle); return;
		case '2': save(cube); return;
		case '0': return;
		default:
			printf("Неправильный пункт меню\n");
			system("pause");
		}
	}	
}

void load(Circle& circle)
{
	FILE* file;
	char filename[100];

	printf("Выбранная фигура: окружность\n");
	cout << "Введите имя файла для загрузки (без .bin): ";
	cin >> filename;
	strcat_s(filename, 100, ".bin");
	if (fopen_s(&file, filename, "rb"))
	{
		cout << "Ошибка открытия файла: " << filename << endl;
		system("pause");
		return;
	}

	fread_s(&circle, sizeof(circle), sizeof(circle), 1, file);

	if (circle.isDefined)
	{		
		printf("Данные загружены\n");
		system("pause");
		return;
	}
	else
	{
		printf("Структура окружности не вводилась\n");
	}
	if (fclose(file))
	{
		cout << "Ошибка закрытия файла: " << filename << endl;
	}
	system("pause");
}

void load(Cube& cube)
{
	FILE* file;
	char filename[100];

	printf("Выбранная фигура: куб\n");
	cout << "Введите имя файла для загрузки (без .bin): ";
	cin >> filename;
	strcat_s(filename, 100, ".bin");
	if (fopen_s(&file, filename, "rb"))
	{
		cout << "Ошибка открытия файла: " << filename << endl;
		system("pause");
		return;
	}

	fread_s(&cube, sizeof(cube), sizeof(cube), 1, file);

	if (cube.isDefined)
	{
		printf("Данные загружены\n");
		system("pause");
		return;
	}
	else
	{
		printf("Структура куба не вводилась\n");
	}
	if (fclose(file))
	{
		cout << "Ошибка закрытия файла: " << filename << endl;
	}
	system("pause");
}

void load()
{
	while (true)
	{
		system("cls");
		printf("1. Загрузить окружность\n");
		printf("2. Загрузить куб\n");
		printf("0. В главное меню\n\n");

		char menu[80];
		cin >> menu;
		switch (menu[0])
		{
		case '1': load(circle); return;
		case '2': load(cube); return;
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

	/*cout << sizeof cube << endl;
	system("pause");*/

	while (true)
	{
		system("cls");
		printf("Главное меню\n");
		printf("****************\n");
		printf("1. Ввести значения фигур\n");
		printf("2. Вывод информации о фигуре\n");
		printf("3. Сохранение структуры в файл\n");
		printf("4. Чтение структуры из файла\n");
		printf("0. Выход\n");
		char menu[80];
		cin >> menu;
		switch (menu[0])
		{
		case '1': setFigure(); break;
		case '2': showInfo(); break;
		case '3': save(); break;
		case '4': load(); break;
		case '0':
			system("pause");
			return 0;
		default:
			printf("Неправильный пункт меню\n");
			system("pause");
		}
	}	
}