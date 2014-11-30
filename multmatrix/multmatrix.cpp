#include "stdafx.h"
#include "stdlib.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

typedef double Matrix3x3[3][3];
typedef const double ConstMatrix3x3[3][3];

bool LoadMatrix(const char* filename, Matrix3x3 matrix)
{
	bool err = false;
	ifstream inputFile(filename);
	err = (!inputFile);

	// read each line of the file
	for (int i = 0; (i < 3) && (!err); ++i)
	{
		inputFile >> matrix[i][0] >> matrix[i][1] >> matrix[i][2];
		err = (!inputFile);
	}

	return (!err);
}

void MultMatrix(ConstMatrix3x3 matrix1, ConstMatrix3x3 matrix2, Matrix3x3 result)
{
	for (int i = 0; i<3; ++i)
	{
		for (int j = 0; j<3; ++j)
		{
			double &pSum = result[i][j];
			pSum = 0;
			for (int k = 0; k<3; ++k)
			{
				pSum += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
}

void PrintMatrix(ConstMatrix3x3 matrix)
{
	for (int i = 0; i<3; ++i)
	{
		cout << matrix[i][0] << "\t" << matrix[i][1] << "\t" << matrix[i][2] << endl;
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
	if (!LoadMatrix(filename1, matrix1))
	{
		printf("Error while loading %s\n", filename1);
		return 1;
	}
	if (!LoadMatrix(filename2, matrix2))
	{
		printf("Error while loading %s\n", filename2);
		return 1;
	}
	Matrix3x3 result;
	MultMatrix(matrix1, matrix2, result);
	PrintMatrix(result);
	return 0;
}