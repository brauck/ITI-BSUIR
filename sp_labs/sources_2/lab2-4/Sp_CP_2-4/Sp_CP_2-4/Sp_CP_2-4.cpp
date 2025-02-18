#include "..\ReverseWords\ReverseWords.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>

#pragma comment(lib,"..\\Debug\\ReverseWords.lib")

using namespace std;

int main()
{
    vector<string> lines;
    vector<string> words;
    // get the filepath
    string filePath = "Sp_CP_2-4.txt";

    readFile(filePath, lines);
    //// Open the file using ifstream
    //ifstream file(filePath);

    //// confirm file opening
    //if (!file.is_open()) {
    //    // print error message and return
    //    cerr << "Failed to open file: " << filePath << endl;

    //    return 1;
    //}
    //// Read the file line by line into a string
    //string line;
    //while (getline(file, line)) {
    //    lines.push_back(line);
    //}
    //// Close the file
    //file.close();

    for (string s : lines)
        cout << s << "\n";

    //// regex expression for pattern to be searched 
    //regex regexp("[a-zA-Z]+");

    //// flag type for determining the matching behavior (in this case on string objects)
    //smatch sm;

    //for (string s : lines)
    //{
    //    while (regex_search(s, sm, regexp)) {
    //        words.push_back(sm[0]);
    //        s = sm.suffix();
    //    }
    //}

    // Reverse the string using the std::reverse()
    
    linesToWords(lines, words);
    reverseWords(words);
    /*for (string &s : words)
        reverse(s.begin(), s.end());*/

    for (string s : words)
        cout << s << "\n";
    
    /*string test{ "notepad test.txt" };
    reverse(test.begin(), test.end());
    cout << test << "\n";*/
     
    /*std::ofstream out("output.txt");
    out << words[0];
    out.close();*/

    //std::ofstream outfile;

    //outfile.open("test.txt", std::ios_base::app); // append instead of overwrite
    //outfile << "\n\n";
    //for (string s : words)
    //outfile << "\t" << s;
    //outfile.close();
    appendToFile("test.txt", words);

    return 0;
}