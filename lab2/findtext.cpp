#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const int MAX_CHARS_PER_LINE = 512;

int main(int argc, char* argv[])
{
	if (argc < 3) 
	{
		cout << "USAGE: findtext.exe <file name> <text to search>" << endl;
		return 0;
	}

	char* filename = argv[1];
	char* textToSearch = argv[2];

	ifstream f;
	f.open(filename); 
	if (!f.good()) 
	{
		cout << "File opening error" << endl;
		return 1;
	}

	bool found = false;
	int i = 0;
	// read each line of the file
	while (!f.eof())
	{
		++i;
		string buf;
		getline(f, buf);
		// find textToSearch in read line
		std::size_t found = buf.find(textToSearch);
		if (found != std::string::npos)
		{
			cout << i << endl;
			found = true;
		}
	}
	f.close();
	if (!found) 
	{
		cout << "Text not found." << endl;
		return 1;
	}
	return 0;
}

