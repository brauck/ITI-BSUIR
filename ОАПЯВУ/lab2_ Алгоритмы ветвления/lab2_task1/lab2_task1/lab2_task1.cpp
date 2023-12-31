// Lab #2
// task #1, #2
#include <iostream>
#include <Windows.h>
#include <cmath>

using namespace std;

void periodOfYear(int y1)
{
	const int current_year = 2023;
	if (y1 == current_year)
		cout << "current" << endl;
	else if (y1 < current_year)
		cout << "past" << endl;
	else
		cout << "future" << endl;
}
void evenYear(int y2)
{
	// a ? b : c
	cout << ((y2 % 2 == 0) ? "even" : "odd") << endl;
}
void leapYear(int y3)
{
	/*
	if (y3 % 400 == 0)
	cout << " leap " << endl;
	else
	if (y3 % 100 == 0)
	cout << " not leap " << endl;
	else
	if (y3 % 4 == 0)
	cout << " leap " << endl;
	else
	cout << "not leap" << endl;
	*/
	if ((y3 % 400 == 0) || ((y3 % 4 == 0) && !(y3 % 100 == 0)))
		cout << " leap " << endl;
	else
		cout << " not leap " << endl;
}
void horoscope(int y4)
{
	int x = y4 % 12;
	switch (x)
	{
	case 0: cout << " Monkey " << endl; break;
	case 1: cout << " Rooster " << endl; break;
	case 2: cout << " Dog " << endl; break;
	case 3: cout << " Boar " << endl; break;
	case 4: cout << " Rat " << endl; break;
	case 5: cout << " Ox " << endl; break;
	case 6: cout << " Tiger " << endl; break;
	case 7: cout << " Rabits " << endl; break;
	case 8: cout << " Dragon " << endl; break;
	case 9: cout << " Snake " << endl; break;
	case 10: cout << " Horse " << endl; break;
	case 11: cout << " Sheep " << endl; break;
	default: cout << " unknown year " << endl;
	}
}

void test()
{
	int array[] = {1932, 1921, 2018, 1972, 2021, 1926,
				  1947, 1963, 2000, 2025, 1942, 2027};
	const int length = sizeof(array) / sizeof(array[0]);
	for (int i = 0; i < length; i++)
	{
		cout << array[i] << ' ';
		horoscope(array[i]);		
	}
}

void main()
{
	cout << "Lab 2 is start!" << endl;
	test();
	int year = 0;
	char q = 0;
	while (q != 'y')
	{
		cout << "Input year ";
		cin >> year;
		cout << "This year is "; periodOfYear(year);
		cout << "This year is "; evenYear(year);
		cout << "This year is "; leapYear(year);
		cout << "This year is "; horoscope(year);

		cout << endl << "Break program ? [y/n]";
		cin >> q;
	}
}