#include "stdafx.h"
#include "stdlib.h"
#include "limits.h"
#include <iostream>
using namespace std;

unsigned int Reverse(unsigned int original)
{
	unsigned int reversed = 0;
	for (unsigned int i = 0; i < CHAR_BIT; ++i)
		reversed |= ((original >> i) & 1) << (CHAR_BIT - 1 - i);
	return reversed;
}

int StringToInt(const char * str, bool & err)
{
	char * pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));
	return param;
}

int main(int argc, char* argv[])
{

	if (argc < 2)
	{
		cout << "Usage: flipbyte.exe N" << endl;
		cout << "       N - integer number to flip (0-" << UCHAR_MAX << ")" << endl;
		return 0;
	}

	bool err;
	int n = StringToInt(argv[1], err);

	if (err) 
	{
		cout << "Argument is not an integer number." << endl;
		return 1;
	}

	if ((n < 0) || (n > UCHAR_MAX))
	{
		cout << "Argument should be from 0 to " << UCHAR_MAX << "." << endl;
		return 2;
	}

	cout << Reverse(n) << endl;
}

