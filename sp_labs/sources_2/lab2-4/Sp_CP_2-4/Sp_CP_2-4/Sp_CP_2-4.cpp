#include "..\ReverseWords\ReverseWords.h"

#pragma comment(lib,"..\\Debug\\ReverseWords.lib")

int main()
{
    vector<string> lines;
    vector<string> words;
    string filePath = "Sp_CP_2-4.txt";

    readFile(filePath, lines);
    
    linesToWords(lines, words);
    reverseWords(words);
    
    appendToFile("Sp_CP_2-4.txt", words);

    system("notepad Sp_CP_2-4.txt");

    return 0;
}