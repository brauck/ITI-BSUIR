// reverse.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
    const char base[300] = "14. Rearrange the characters in each word in reverse order and write the resulting words to the end of the file (to reverse words, you can use the Windows library functions \"_strrev, _tcsrev, _mbsrev\").";
    cout << base << "\n\n";

    char words[300][30] = { 0 };
    char word[30] = { 0 };

    int w = 0;
    int j = 0;
    int wLen = 0;

    for (int i = 0; i < strlen(base); i++)
    {
        if (!isalpha(base[i]) && !strlen(word))
        {
            continue;
        }

        if (!isalpha(base[i]) && strlen(word))
        {
            wLen = strlen(word);
            for (int k = 0; k < wLen; k++)
            {
                words[w][k] = word[wLen - k - 1];
            }
            w++;
            j = 0;
            wLen = 0;
            memset(word, 0, sizeof(word));
            continue;
        }

        if (isalpha(base[i]))
        {
            word[j] = base[i];
            j++;
        }
    }

    for (int i = 0; i < 300; i++)
    {
        if (!words[i][0]) break;
        cout << words[i] << "   ";
    }




    /*char word[30] = { 0 };
    char tempWord[30] = { 0 };

    int j = 0;
    int wLen = 0;

    for (int i = 0; i < strlen(base); i++)
    {
        if (!isalpha(base[i]) && !strlen(word))
        {
            continue;
        }

        if (!isalpha(base[i]) && strlen(word))
        {
            wLen = strlen(word);
            for (int k = 0; k < wLen; k++)
            {
                tempWord[k] = word[wLen - k -1];
            }
            cout << tempWord << ' ';
            j = 0;
            wLen = 0;
            memset(word, 0, sizeof(word));
            memset(tempWord, 0, sizeof(tempWord));
            continue;
        }

        if (isalpha(base[i]))
        {
            word[j] = base[i];
            j++;
        }
    }*/

    system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
