// Lab #4
// task #1
#include <iostream>
#include <Windows.h>
using namespace std;

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	double temperature[] = {
		19.1, 28.7, 17.2, 25.3, 25.3, 24.0, 1.5,
		0.0, -2.5, 1.0, -5.1, 2.3, 28.7, 25.3,
		27.1, 27.1, 27.1, 28.7, 26.0 , 25.3 , 25.3
	};
	
	//  Средняя температура за весь период
	int N = sizeof temperature / sizeof temperature[0];
	
	double sumAllTemperatures{};	
	for (int i = 0; i < N; i++)
	{
		sumAllTemperatures += temperature[i];
	}	
	printf("Средняя температура за весь период: %.1f\n",
		sumAllTemperatures / N);
	// Максимальная температура за период
	// Минимальная температура за период
	double maxTemperature = temperature[0];
	double minTemperature = temperature[0];
	for (int i = 0; i < N - 1; i++)
	{
		if (temperature[i + 1] > maxTemperature)
			maxTemperature = temperature[i + 1];
		if (temperature[i + 1] < minTemperature)
			minTemperature = temperature[i + 1];
	}
	cout << "Максимальная температура за период: "
		<< maxTemperature << '\n'
		<< "Минимальная температура за период: "
		<< minTemperature << endl;

	// Количество дней, когда были заморозки
	// (значение температуры ниже 0)
	int temperatureBelowZero{};
	for (int i = 0; i < N; i++)
	{
		if (temperature[i] < 0) temperatureBelowZero++;
	}
	cout << "Количество дней, когда были заморозки: "
		<< temperatureBelowZero << endl;

	//Количество дней, когда было потепление
	//(значение температуры больше предыдущего)
	int countWarmer{};
	for (int i = 0; i < N - 1; i++)
	{
		if (temperature[i + 1] > temperature[i])
			countWarmer++;		
	}
	cout << "Количество дней, когда было потепление: "
		<< countWarmer << endl;

	//Количество дней с максимальной температурой
	int countWarmestDays{};
	for (int i = 0; i < N; i++)
	{
		if (temperature[i] == maxTemperature) countWarmestDays++;
	}
	cout << "Количество дней с максимальной температурой: "
		<< countWarmestDays << endl;

	// В какой день периода была максимальная температура
	// Будем считать первое значение понедельником
	cout << "максимальная температура была ";
	bool isFirstString = true;
	for (int i = 0; i < N; i++)
	{
		if (temperature[i] == maxTemperature)
		{
			int day = i % 7;
			if (isFirstString)
			{
				switch (day)
				{
				case 0: cout << "в понедельник "
					<< i + 1 << " день " << endl; break;
				case 1: cout << "во вторник "
					<< i + 1 << " день" << endl; break;
				case 2: cout << "в среду "
					<< i + 1 << " день" << endl; break;
				case 3: cout << "в четверг "
					<< i + 1 << " день" << endl; break;
				case 4: cout << "в пятницу "
					<< i + 1 << " день" << endl; break;
				case 5: cout << "в субботу "
					<< i + 1 << " день" << endl; break;
				case 6: cout << "в воскресенье "
					<< i + 1 << " день" << endl; break;
				}
			}
			if (isFirstString)
			{
				isFirstString = false;
				continue;
			}
			switch (day)
			{
			case 0: printf("%30c%s%d день\n",
				' ', "в понедельник ", i + 1); break;
			case 1: printf("%30c%s%d день\n",
				' ', "во вторник ", i + 1); break;
			case 2: printf("%30c%s%d день\n",
				' ', "в среду ", i + 1); break;
			case 3: printf("%30c%s%d день\n",
				' ', "в четверг ", i + 1); break;
			case 4: printf("%30c%s%d день\n",
				' ', "в пятницу ", i + 1); break;
			case 5: printf("%30c%s%d день\n",
				' ', "в субботу ", i + 1); break;
			case 6: printf("%30c%s%d день\n",
				' ', "в воскресенье ", i + 1); break;
			}
		}
	}

	//В какой день периода началось оттепель (первый, если таких несколько)
	int plusAfterMinus{};
	for (int i = 0; i < N - 1; i++)
	{
		if (temperature[i] < 0 && temperature[i + 1] > 0)
		{
			plusAfterMinus = i + 1 + 1;
			break;
		}
	}
	cout << "Оттепель началась в день номер "
		<< plusAfterMinus << " периода" << endl;
		
	// Самая длинная последовательность дней с одинаковой температурой
	int maxLength{};
	int count{1};
	int sequenceTempereture;
	for (int i = 0; i < N - 1; i++)
	{
		if (temperature[i + 1] == temperature[i])
		{
			count++;
		}
		else
		{
			maxLength = count;
			count = 1;
		}		
	}
	cout << "Самая длинная последовательность дней с одинаковой температурой: "
		<< 


	system("pause");
}