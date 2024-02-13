﻿// Lab #7
// task #1
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <Windows.h>
using namespace std;

const int MAX = 20;

struct Circle
{
	int x1, y1, radius;
	bool isDefined{ false };
};

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

	bool isDefined{ false };
};

void drawCube()
{
	printf("\n%25s\n", "    H-------------G");
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

Circle circle;
Cube cube;

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
	// Ребро AB
	double cubeEdgeLength = twoPointsDistance(
		cube.vertexes[0][0],
		cube.vertexes[0][1],
		cube.vertexes[0][2],
		cube.vertexes[1][0],
		cube.vertexes[1][1],
		cube.vertexes[1][2]
	);

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
		cout << '\n' << tempCubeEdgeLength << ' ' << cubeEdgeLength << endl;
		if (!approximatelyEqualAbsRel(
			tempCubeEdgeLength,
			cubeEdgeLength,
			absEpsilon,
			relEpsilon)
			)
		{
			cout << "in false" << endl;
			isEdgesEqual = false;
			break;
		}
	/*0 0 0
	11 0 0
	11 0 11
	0 0 11
	0 110 0
	11 110 0
	11 110 11
	0 110 11*/
		cout << "count: " << count << ' ' << "i: " << i << endl;
		if (count < 2)
		{
			count++;
			continue;
		}

		i++;
		cout << "in AD" << endl;
		cout << "count: " << count << ' ' << "i: " << i << endl;
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

		cout << '\n' << tempCubeEdgeLength << ' ' << cubeEdgeLength << endl;

		if (!approximatelyEqualAbsRel(
			tempCubeEdgeLength,
			cubeEdgeLength,
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
		cout << "i: " << i << endl;
		cout << '\n' << tempCubeEdgeLength << ' ' << cubeEdgeLength << endl;
		if (!approximatelyEqualAbsRel(
			tempCubeEdgeLength,
			cubeEdgeLength,
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
	// Ребро AB
	double cubeEdgeLength = twoPointsDistance(
		cube.vertexes[0][0],
		cube.vertexes[0][1],
		cube.vertexes[0][2],
		cube.vertexes[1][0],
		cube.vertexes[1][1],
		cube.vertexes[1][2]
	);

	double isoscelesRightTriangleHypotenuse = sqrt(
		2 * pow(cubeEdgeLength, 2)
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

		cout << '\n' << tempFaceDiagonal << ' ' << isoscelesRightTriangleHypotenuse << endl;
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
	cin >> circle.x1 >> circle.y1;
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


	cube.isDefined = false;

	drawCube();
	char vertex{ 'A' };
	for (int i = 0; i < 8; i++)
	{
		cout << "Введите координаты вершины " << vertex++ << " (x y z): ";
		cin >> cube.vertexes[i][0] >> cube.vertexes[i][1] >> cube.vertexes[i][2];
	}

	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << cube.vertexes[i][j] << ' ';
		}
	}*/

	if (isFigure(cube))  cube.isDefined = true;

	system("pause");
}

void setFigure()
{
	while (true)
	{
		system("cls");
		printf("1. Создать окружность\n");
		printf("2. Создать куб\n");
		printf("0. Выход\n");
		
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

void getPerimeter()
{

}

void showInfo()
{

}

void save()
{

}

void load()
{

}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	

	while (true)
	{
		system("cls");
		printf("****************\n");
		printf("Главное меню\n");
		printf("****************\n");
		printf("1. Ввести значения фигур\n");
		printf("2. Расчет периметра\n");
		printf("3. Расчет площади\n");
		printf("4. Расчет объема\n");
		printf("5. Вывод информации о фигуре\n");
		printf("6. Сохранение структуры в файл\n");
		printf("7. Чтение структуры из файла\n");
		printf("0. Выход\n");
		char menu[80];
		cin >> menu;
		switch (menu[0])
		{
		case '1': setFigure(); break;
		case '2': getPerimeter(); break;
		case '3': break;
		case '4': break;
		case '5': showInfo(); break;
		case '6': save(); break;
		case '7': load(); break;
		case '0':
			system("pause");
			return 0;
		default:
			printf("Неправильный пункт меню\n");
			system("pause");
		}
	}	
}