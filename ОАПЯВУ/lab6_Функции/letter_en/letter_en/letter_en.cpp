// letters.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // cout << int(' ');
    char str[81] = { 'A', 'B', 'C', 'D', 'E', 'Z' };
    char codeStr[161] = {};

    cout << str << endl;


    int base{};
    int tens{};
    int ones{};
    int shift{};

    for (int i = 0; i < strlen(str); i++)
    {
        if (!str[i]) break;
        //cout << "iteration" << endl;
        base = int(str[i]) - 64;

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

    cout << codeStr << endl;

    //char str2[81] = {};

    int toTens{};
    int toOnes{};
    char letter{};

    for (int i = 0; i < strlen(codeStr); i += 2)
    {
        toTens = int(codeStr[i]) - 48;
        toOnes = int(codeStr[i + 1]) - 48;
        letter = char(toTens * 10 + toOnes + 64);
        str[i / 2] = letter;
    }

    cout << str << endl;

    //lower

    char str2[81] = { 'a', 'b', 'c', 'd', 'f', 'z' };
    char codeStr2[161] = {};

    cout << str2 << endl;


    
    shift = 0;

    for (int i = 0; i < strlen(str2); i++)
    {
        if (!str2[i]) break;
        //cout << "iteration" << endl;
        base = int(str2[i]) - 70;
        cout << base << endl;
        
        tens = base / 10;
        ones = base % 10;
       

        codeStr2[shift] = char(tens + 48);
        codeStr2[shift + 1] = char(ones + 48);

        shift += 2;
    }

    cout << codeStr2 << endl;

    //char str2[81] = {};

    

    for (int i = 0; i < strlen(codeStr); i += 2)
    {
        toTens = int(codeStr[i]) - 48;
        toOnes = int(codeStr[i + 1]) - 48;
        letter = char(toTens * 10 + toOnes + 70);
        str[i / 2] = letter;
    }

    cout << str2 << endl;




    for (int i = 0; i < 152; i++)
    {
        cout << i << ' ' << char(i) << endl;
    }
    for (int i = 153; i < 256; i++)
    {
       cout << i << ' ' << char(i) << endl;
    }
}

//The quick brown fox jumps over the lazy dog