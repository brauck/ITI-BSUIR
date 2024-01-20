// letters.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //char t[80] = { 'А', 'Б', 'В', ' ', '+', 'Г' };
    //char t[80];
    //strcpy_s(t, "\0");
   
    
    //cout << "before" << t << endl;
    //t[0] = 's';
    //t[1] = '\0';
    //cout << t << endl;
    //printf("% s \n", t);
    //cout << ('А' + 1) << ' ' << char(-64) << endl;
    char S[160] = { '$', 'А', 'Б', 's', ' ', '+', 'Г', 'я', 'Я' };
    char codeStr[160] = {};

    cout << S << endl;
    
    
    int base{};
    int tens{};
    int ones{};
    int shift{};

    for (int i = 0; i < strlen(S); i++)
    {
        //if (!str[i]) break;
        //cout << "iteration" << endl;

        if (S[i] < 0)
        {
            //cout << "less" << endl;
            base = (S[i]) + 65;

            if (base > 9)
            {
                tens = base / 10;
                ones = base % 10;
            }
            else
            {
                tens = 0;
                ones = base;
            }

            codeStr[shift] = char(tens + 48);
            codeStr[shift + 1] = char(ones + 48);

            shift += 2;
        }
        else
        {
            codeStr[shift] = S[i];
            shift++;
        }
            
    }

    cout << codeStr << ' ' << strlen(codeStr) << endl;
    strcpy_s(S, codeStr);
    cout << S << endl;

    int toTens{};
    int toOnes{};
    char letter{};
    
    strcpy_s(S, "");
    shift = 1;
    int Sindex{};

    for (int i = 0; i < strlen(codeStr); i += shift)
    {
        if (codeStr[i] > 47 && codeStr[i] < 58)
        {
            shift = 2;
            cout << i << endl;
            toTens = int(codeStr[i]) - 48;
            toOnes = int(codeStr[i + 1]) - 48;
            letter = char(toTens * 10 + toOnes - 65);
            S[Sindex] = letter;
        }
        else
        {
            shift = 1;
            S[Sindex] = codeStr[i];
        }
        Sindex++;
    }
    S[Sindex] = '\0';
    cout << S << endl;
    
       
   /* FILE* file;
    char filename[50];
    cout << "Введите имя файла: ";
    cin >> filename;
    if (fopen_s(&file, filename, "w"))
    {
        cout << "Ошибка открытия файла: " << filename << endl;
        return 1;
    }

   

    for (int i = 0; i < 152; i++)
    {
        fprintf(file, "%d %c \n", i, char(i));
        cout << i << ' ' << char(i) << endl;
    }
    for (int i = 153; i < 256; i++)
    {
       fprintf(file, "%d %c \n", i, char(i));
       cout << i << ' ' << char(i) << endl;
    }
    fclose(file);*/

    return 0;
}

//The quick brown fox jumps over the lazy dog
// Быстрая коричневая лиса прыгает через ленивую собаку!