// letters.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //cout << int('A');
    char str[81] = { 'А', 'Б', 'В', 'Г', 'Й', 'Я'};
    char codeStr[161] = {};

    cout << str << endl;
    

    int base{};
    int tens{};
    int ones{};
    int shift{};

    for (int i = 0; i < strlen(str); i++)
    {
        if (!str[i]) break;
        cout << "iteration" << endl;
        base = int(str[i]) + 65;

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

    char str2[81] = {};

    int toTens{};
    int toOnes{};
    char letter{};
    
    for (int i = 0; i < strlen(codeStr); i += 2)
    {              
        toTens = int(codeStr[i]) - 48;        
        toOnes = int(codeStr[i + 1]) - 48;                
        letter = char(toTens * 10 + toOnes + 191);        
        str[i / 2] = letter;        
    }
    
    cout << str << endl;
    
       
   
    
   

    /*for (int i = 0; i < 152; i++)
    {
        cout << i << ' ' << char(i) << endl;
    }
    for (int i = 153; i < 256; i++)
    {
       cout << i << ' ' << char(i) << endl;
    }*/
}

//The quick brown fox jumps over the lazy dog