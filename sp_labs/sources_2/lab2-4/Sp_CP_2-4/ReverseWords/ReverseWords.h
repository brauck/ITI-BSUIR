// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the REVERSEWORDS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// REVERSEWORDS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

#ifdef REVERSEWORDS_EXPORTS
#define REVERSEWORDS_API __declspec(dllexport)
#else
#define REVERSEWORDS_API __declspec(dllimport)
#endif

// This class is exported from the dll
class REVERSEWORDS_API CReverseWords {
public:
	CReverseWords(void);
	// TODO: add your methods here.
};

extern REVERSEWORDS_API int nReverseWords;
//extern REVERSEWORDS_API vector<string> lines;

REVERSEWORDS_API int fnReverseWords(void);

REVERSEWORDS_API void readFile(string filePath, vector<string>& lines);
REVERSEWORDS_API void linesToWords(vector<string>& lines, vector<string>& words);
REVERSEWORDS_API void reverseWords(vector<string>& words);
REVERSEWORDS_API void appendToFile(const char* filePath, vector<string> words);
