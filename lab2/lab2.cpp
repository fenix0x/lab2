#include "stdafx.h"
#include <fstream>
using std::ifstream;

const int MAX_CHARS_PER_LINE = 512;

int main(int argc, char* argv[])
{
	if (argc < 3) 
	{
		printf("USAGE: findtext.exe <file name> <text to search>\n");
		return 0;
	}

	char* filename = argv[1];
	char* textToSearch = argv[2];

	ifstream f;
	// open a file
	f.open(filename); 
	if (!f.good()) 
	{
		printf("File opening error\n");
		return 1;
	}

	bool found = false;
	int i = 0;
	// read each line of the file
	while (!f.eof())
	{
		++i;
		// read an entire line into memory
		char buf[MAX_CHARS_PER_LINE];
		f.getline(buf, MAX_CHARS_PER_LINE);
		// find textToSearch in read line
		if (strstr(buf, textToSearch) != NULL)
		{
			printf("%d\n", i);
			found = true;
		}
	}
	f.close();
	if (!found) 
	{
		printf("Text not found.\n");
		return 1;
	}
	return 0;
}

