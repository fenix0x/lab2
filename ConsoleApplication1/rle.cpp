#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

const int MAX_SIZE = 2*1024*1024;
const int BUF_SIZE = 1024;

void printUsage() 
{
	printf("USAGE: rle.exe pack <input file> <output file> \n");
	printf("       rle.exe unpack <input file> <output file> \n");
}

void packFile(ifstream& fileIn, ofstream& fileOut)
{
	char* bufferOut = new char[2];
	if (!fileIn.eof())
	{
		char newChar = fileIn.get();
		while (!fileIn.eof())
		{
			unsigned char charCount = 1;
			char oldChar = newChar;
			if (!fileIn.eof())
			{
				while (!fileIn.eof() && (oldChar == (newChar = fileIn.get())) && (charCount < 255))
				{
					++charCount;
				}
			}
			bufferOut[0] = charCount;
			bufferOut[1] = oldChar;
			fileOut.write(bufferOut, 2 * sizeof(char));
		}
		delete[] bufferOut;
	}
}

void unpackChars(char* & bufferIn, int bufferInSize, ofstream& fileOut)
{
	char* bufferOut = new char[BUF_SIZE];
	for (int i = 0; i < bufferInSize; i += 2)
	{
		int bufferOutSize = 0;
		unsigned char countChars = bufferIn[i];
		char newChar = bufferIn[i + 1];
		for (unsigned char j = 0; j < countChars; ++j)
		{
			bufferOut[bufferOutSize++] = newChar;
		}
		fileOut.write(bufferOut, bufferOutSize);
	}
}

void unpackFile(ifstream& fileIn, ofstream& fileOut)
{
	while (!fileIn.eof())
	{
		char* bufferIn = new char[BUF_SIZE];
		while (fileIn.read(bufferIn, BUF_SIZE))
		{
			unpackChars(bufferIn, BUF_SIZE, fileOut);
		}

		unpackChars(bufferIn, fileIn.gcount(), fileOut);

		delete[] bufferIn;
	}
}

int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		printUsage();
		return 0;
	}

	char* command = argv[1];
	char* inputFilename = argv[2];
	char* outputFilename = argv[3];

	if ((command != "pack") && (command == "unpack"))
	{
		printUsage();
		return 0;
	}

	// open a file to read
	ifstream fIn(inputFilename, ifstream::binary);
	if (!fIn.good())
	{
		printf("File %s opening error\n", inputFilename);
		return 1;
	}

	// open a file to write
	ofstream fOut(outputFilename, ofstream::binary);
	if (!fOut.good())
	{
		printf("File %s opening error\n", outputFilename);
		return 1;
	}

	printf("[%s]\n", command);
	if (strcmp(command, "pack")==0)
	{
		printf("pack file\n");
		packFile(fIn, fOut);
	}
	else
	{
		printf("unpack file\n");
		unpackFile(fIn, fOut);
	}

	fOut.close();
	fIn.close();

	printf("File %s %sed into %s succesfuly.\n", inputFilename, command, outputFilename);

	return 0;
}

