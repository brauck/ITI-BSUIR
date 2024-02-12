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
	int x1, y1, radius;
	bool isDefined{ false };
};

struct Cube
{
	double x1, y1, z1,
		   x2, y2, z2,
	  	   x3, y3, z3,
		   x4, y4, z4,
		   x5, y5, z5,
		   x6, y6, z6,
		   x7, y7, z7,
		   x8, y8, z8;
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

bool isFigure(Circle& circle)
{
	if (circle.radius > 0) return true;
	
	cout << "Окружность не создана: "
		<< "значение радиуса должно быть больше нуля" << endl;
	system("pause");
	circle.isDefined = false;
	return false;	
}

bool isFigure(Cube& cube)
{
	return false;
}

void createFigure(Circle& circle)
{
	cout << "Введите координаты центра окружности (x y): ";
	cin >> circle.x1 >> circle.y1;
	cout << "Введите радиус: ";
	cin >> circle.radius;
	
	if (isFigure(circle)) circle.isDefined = true;
}

void createFigure(Cube& cube)
{
	drawCube();
	char vertex{ 'A' };
	cout << "Введите координаты вершины " << vertex++ << "(x y z): ";
	cin >> cube.x1 >> cube.y1 >> cube.z1;
	cout << "Введите координаты вершины " << vertex++ << "(x y z): ";
	cin >> cube.x2 >> cube.y2 >> cube.z2;
	cout << "Введите координаты вершины " << vertex++ << "(x y z): ";
	cin >> cube.x3 >> cube.y3 >> cube.z3;
	cout << "Введите координаты вершины " << vertex++ << "(x y z): ";
	cin >> cube.x4 >> cube.y4 >> cube.z4;
	cout << "Введите координаты вершины " << vertex++ << "(x y z): ";
	cin >> cube.x5 >> cube.y5 >> cube.z5;
	cout << "Введите координаты вершины " << vertex++ << "(x y z): ";
	cin >> cube.x6 >> cube.y6 >> cube.z6;
	cout << "Введите координаты вершины " << vertex++ << "(x y z): ";
	cin >> cube.x7 >> cube.y7 >> cube.z7;
	cout << "Введите координаты вершины " << vertex << "(x y z): ";
	cin >> cube.x8 >> cube.y8 >> cube.z8;

	cube.isDefined = true;

	//system("pause");
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