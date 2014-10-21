#include "stdafx.h"
#include "stdlib.h"

unsigned int reverse(unsigned int original)
{
	unsigned int reversed = 0;
	for(unsigned int i=0; i<8; i++)
		reversed |= ((original>>i) & 1)<<(7-i);
	return reversed;
}

int StringToInt(const char * str, bool & err)
{
	char * pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0' ) || (*pLastChar != '\0' ));
	return param;
}

int main(int argc, char* argv[])
{
	/*
	printf("%d\n", reverse(6));
	printf("%d\n", reverse(96));
	*/

	if (argc < 2)
	{
		printf("Usage: flipbyte.exe N\n");
		printf("       N - integer number to flip (0-255)\n");
		return 0;
	}

	bool err;
	int n = StringToInt(argv[1], err);

	if (err) 
	{
		printf("Argument is not an integer number.\n");
		return 1;
	}
	if ((n < 0) || (n > 255))  
	{
		printf("Argument should be from 0 to 255.\n");
		return 2;
	}

	printf("%d\n", reverse(n));
}

