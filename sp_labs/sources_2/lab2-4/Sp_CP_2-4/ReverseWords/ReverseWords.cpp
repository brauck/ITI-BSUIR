// ReverseWords.cpp : Defines the exported functions for the DLL.
//

#include "framework.h"
#include "ReverseWords.h"

// This is an example of an exported variable
REVERSEWORDS_API int nReverseWords=0;

// This is an example of an exported function.
REVERSEWORDS_API int fnReverseWords(void)
{
    return 0;
}

REVERSEWORDS_API void readFile(string filePath, vector<string>& lines)
{
    // Open the file using ifstream
    ifstream file(filePath);

    // confirm file opening
    if (!file.is_open()) {
        // print error message and return
        cerr << "Failed to open file: " << filePath << endl;

        return;
    }
    // Read the file line by line into a string
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    // Close the file
    file.close();
}

REVERSEWORDS_API void linesToWords(vector<string>& lines, vector<string>& words)
{
    // regex expression for pattern to be searched 
    regex regexp("[a-zA-Z]+");

    // flag type for determining the matching behavior (in this case on string objects)
    smatch sm;

    for (string s : lines)
    {
        while (regex_search(s, sm, regexp))
        {
            words.push_back(sm[0]);
            s = sm.suffix();
        }
    }
}

REVERSEWORDS_API void reverseWords(vector<string>& words)
{
    for (string& s : words)
        reverse(s.begin(), s.end());
}

REVERSEWORDS_API void appendToFile(const char* filePath, vector<string> words)
{
    std::ofstream outfile;

    outfile.open(filePath, std::ios_base::app); // append instead of overwrite
    outfile << "\n\n";
    for (string s : words)
        outfile << "\t" << s;
    outfile.close();
}

// This is the constructor of a class that has been exported.
CReverseWords::CReverseWords()
{
    return;
}
