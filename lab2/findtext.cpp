#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

enum Err
{
	ERR_NO_ERROR,
	ERR_CANT_OPEN_FILE,
};

bool FindLines(const char* filename, const char* textToSearch, Err & err)
{
	bool found = false;
	ifstream inputFile(filename);
	if (!inputFile)
	{
		cout << "File opening error" << endl;
		err = ERR_CANT_OPEN_FILE;
		return false;
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
	return found;
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "USAGE: findtext.exe <file name> <text to search>" << endl;
		return 0;
	}

	Err err = ERR_NO_ERROR;

	// try to find lines with string argv[2] in file argv[1]
	bool found = FindLines(argv[1], argv[2], err);
	
	if (err == ERR_NO_ERROR)
	{
		if (!found)
		{
			cout << "Text not found." << endl;
		}
		return 0;
	}
	else
	{
		return err;
	}
}