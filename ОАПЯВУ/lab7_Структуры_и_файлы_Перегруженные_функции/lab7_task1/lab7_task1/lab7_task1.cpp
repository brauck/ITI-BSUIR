// Lab #7
// task #1
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <Windows.h>
using namespace std;

const int MAX = 20;

struct circle
{
	int x1, y1, r;
	bool isFilled = false;
	bool valume = false;
};

struct triangle
{
	int x1, y1, x2, y2, x3, y3;
	bool isFilled = false;
	bool valume = false;
};

void clearAll(circle* c, triangle* t)
{
	c->isFilled = false;
	t->isFilled = false;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	circle listCircle[MAX];
	triangle listTriangle[MAX];
	/*clearAll(listCircle, listTriangle);
	listCircle->r = 25;
	cout << listCircle[0].r << endl;
	double a = 5;
	int b = 2;
	cout << a / b << endl;*/

	circle c;
	cout << sizeof c << endl;
	int l{};
	l = round(7.123456789 * 1'000'000);
	cout << l << endl;
	unsigned int i = pow(2, 31);
	cout << i << endl;
	
	printf("%25s", " H______________G\n");
	printf("%25s", "   /'            /|\n");
	printf("%25s", "  / '           / |\n");	
	printf("%25s", " E/  '          /F |\n");
	printf("%25s", "  ----+----------   |\n");
	printf("%25s", "  |   '         |   |\n");
	printf("%25s", "  |  D'. . . . .|. .C\n");
	printf("%25s", "  |  '          |  / \n");
	printf("%25s", "  | '           | /  \n");
	printf("%25s", "  |'            |/   \n");
	printf("%25s", " A-------------B    \n");
	//system("pause");
	return 0;
}