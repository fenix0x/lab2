#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

enum Err
{
	ERR_TEXT_FOUND,
	ERR_TEXT_NOT_FOUND,
	ERR_CANT_OPEN_FILE,
};

// try to find lines with string argv[2] in file argv[1]
Err FindLines(const char* filename, const char* textToSearch)
{
	bool found = false;
	ifstream inputFile(filename);
	if (!inputFile)
	{
		return ERR_CANT_OPEN_FILE;
	}
	int i = 0;
	// read each line of the file
	while (!inputFile.eof())
	{
		++i;
		string buf;
		getline(inputFile, buf);
		// find textToSearch in read line
		size_t foundTextPos = buf.find(textToSearch);
		if (foundTextPos != string::npos)
		{
			cout << i << endl;
			found = true;
		}
	}
	if (found)
	{
		return ERR_TEXT_FOUND;
	}
	else
	{
		return ERR_TEXT_NOT_FOUND;
	}
}

void PrintError(Err err)
{
	switch (err)
	{
	case ERR_CANT_OPEN_FILE:
		cout << "File opening error" << endl;
		return;
	case ERR_TEXT_NOT_FOUND:
		cout << "Text not found." << endl;
		return;
	default:
		return;
	}
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "USAGE: findtext.exe <file name> <text to search>" << endl;
		return 0;
	}
	Err result = FindLines(argv[1], argv[2]);
	PrintError(result);
	return result;
}