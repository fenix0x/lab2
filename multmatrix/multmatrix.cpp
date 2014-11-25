#include "stdafx.h"
#include "stdlib.h"
#include <fstream>
#include <iostream>
using namespace std;

const int MAX_CHARS_PER_LINE = 512;

typedef double Matrix3x3[3][3];
typedef const double ConstMatrix3x3[3][3];

double StringToDouble(const char * str, bool & err)
{
	char * pLastChar = NULL;
	double param = strtod(str, &pLastChar);
	err = ((*str == '\0' ) || (*pLastChar != '\0' ));
	return param;
}

int LoadMatrix(char* filename, Matrix3x3 matrix)
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
	while ((!f.eof()) && (!err) && (i < 3))
	{
		// read an entire line into memory
		char buf[MAX_CHARS_PER_LINE];
		f.getline(buf, MAX_CHARS_PER_LINE);

		int j = 0;
		char* token = strtok(buf, " \t");
		while ((token != NULL) && (!err) && (j < 3))
		{
			matrix[i][j] = StringToDouble(token, err);
			if (err)
				printf("error\n");
			token = strtok(NULL, " \t");
			++j;
		}
		++i;
	}
	if (err)
		return 1; 
	else
		return 0;
}

void MultMatrix(ConstMatrix3x3& matrix1, ConstMatrix3x3& matrix2, Matrix3x3& result)
{
	for (int i = 0; i<3; ++i)
	{
		for (int j = 0; j<3; ++j)
		{
			result[i][j] = 0;
			for (int k = 0; k<3; ++k)
			{
				result[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
}

void PrintMatrix(ConstMatrix3x3& matrix)
{
	for (int i = 0; i<3; ++i)
	{
		bool firstNumber = true;
		for (int j = 0; j<3; ++j)
		{
			if (!firstNumber)
			{
				cout << "\t";
			}
			cout << matrix[i][j];
			firstNumber = false;
		}
		cout << endl;
	}
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

	Matrix3x3 matrix1;
	Matrix3x3 matrix2;

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

	Matrix3x3 result;

	MultMatrix(matrix1, matrix2, result);
	PrintMatrix(result);

	return 0;
}

