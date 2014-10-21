#include "stdafx.h"
#include "stdlib.h"
#include <fstream>
using std::ifstream;

const int MAX_CHARS_PER_LINE = 512;

double StringToDouble(const char * str, bool & err)
{
	char * pLastChar = NULL;
	double param = strtod(str, &pLastChar);
	err = ((*str == '\0' ) || (*pLastChar != '\0' ));
	return param;
}

int LoadMatrix(char* filename, double matrix[3][3])
{
	ifstream f;
	// open a file
	f.open(filename); 
	if (!f.good()) 
	{
		printf("File opening error\n");
		return 1;
	}

	bool err = false;
	int i = 0;

	// read each line of the file
	while ((!f.eof()) && (!err) && (i<3))
	{
		// read an entire line into memory
		char buf[MAX_CHARS_PER_LINE];
		f.getline(buf, MAX_CHARS_PER_LINE);

		int j = 0;
		char* ch = strtok(buf, " \t");
		while ((ch != NULL) && (!err) && (j,3))
		{
			//printf("%s\n", ch);
			matrix[i][j] = StringToDouble(ch, err);
			if (err)
				printf("error\n");
			ch = strtok(NULL, " \t");
			++j;
		}
		++i;
	}
	f.close();
	if (err)
		return 1; 
	else
		return 0;
}

int main(int argc, char* argv[])
{
	if (argc < 3) 
	{
		printf("USAGE: multmatrix. exe <matrix file1> <matrix file2>\n");
		return 0;
	}

	char* filename1 = argv[1];
	char* filename2 = argv[2];

	double matrix1[3][3];
	double matrix2[3][3];

	if (LoadMatrix(filename1, matrix1) != 0)
	{
		printf("Error while loading %s\n", filename1);
		return 1;
	}
	if (LoadMatrix(filename2, matrix2) != 0)
	{
		printf("Error while loading %s\n", filename2);
		return 1;
	}

	for(int i=0; i<3; ++i)
	{
		for (int j=0; j<3; ++j)
		{
			double c = 0;
			for (int k=0; k<3; ++k)
			{
				c += matrix1[i][k]*matrix2[k][j];
			}
			printf("%g\t", c);
		}
		printf("\n");
	}

	return 0;
}

