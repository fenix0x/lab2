#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

const unsigned long MAX_SIZE = 2 * 1073741824 - 1; // 2Gb
const long BUF_SIZE = 1024;

const int ERR_MAX_SIZE = 1;
const int ERR_ZERO_LENGTH_FILE = 2;

void printUsage() 
{
	printf("USAGE: rle.exe pack <input file> <output file> \n");
	printf("       rle.exe unpack <input file> <output file> \n");
}

int packFile(ifstream& fileIn, ofstream& fileOut)
{
	char* bufferOut = new char[2];
	unsigned long totalSize = 0;
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
			unsigned int incSize = 2 * sizeof(char);
			totalSize += incSize;
			if (totalSize > MAX_SIZE)
			{
				return ERR_MAX_SIZE;
			} else
			{
				fileOut.write(bufferOut, incSize);
			}
		}
		delete[] bufferOut;
	}
	if (totalSize == 0)
	{
		return ERR_ZERO_LENGTH_FILE;
	}
	return 0;
}

int unpackChars(char* & bufferIn, int bufferInSize, ofstream& fileOut, unsigned long& totalBufferOutSize)
{
	char* bufferOut = new char[BUF_SIZE];
	for (int i = 0; i < bufferInSize; i += 2)
	{
		unsigned long bufferOutSize = 0;
		unsigned char countChars = bufferIn[i];
		char newChar = bufferIn[i + 1];
		for (unsigned char j = 0; j < countChars; ++j)
		{
			bufferOut[bufferOutSize++] = newChar;
		}
		totalBufferOutSize += bufferOutSize;
		if (totalBufferOutSize > MAX_SIZE)
		{
			return ERR_MAX_SIZE;
		}
		fileOut.write(bufferOut, bufferOutSize);
	}
	return 0;
}

int unpackFile(ifstream& fileIn, ofstream& fileOut)
{
	unsigned long totalSize = 0;
	while (!fileIn.eof())
	{
		char* bufferIn = new char[BUF_SIZE];
		int err = 0;
		while (fileIn.read(bufferIn, BUF_SIZE))
		{
			err = unpackChars(bufferIn, BUF_SIZE, fileOut, totalSize);
			if (err != 0) return err;
		}
		err = unpackChars(bufferIn, fileIn.gcount(), fileOut, totalSize);
		delete[] bufferIn;
		if (err != 0)
			return err;
	}
	return 0;
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

	int err = 0;
	if (strcmp(command, "pack")==0)
	{
		err = packFile(fIn, fOut);
	}
	else
	{
		err = unpackFile(fIn, fOut);
	}

	fOut.close();
	fIn.close();

	switch (err)
	{
	case ERR_MAX_SIZE:
		printf("Output file %s max size reached. Aborting job.\n", outputFilename);
		return 1;
	case ERR_ZERO_LENGTH_FILE:
		printf("Warning! Intput file %s is empty.\n", inputFilename);
		break;
	default:
		printf("File %s %sed into %s succesfuly.\n", inputFilename, command, outputFilename);
		break;
	}

	return 0;
}

