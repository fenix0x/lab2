#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

const unsigned long MAX_SIZE = 2UL * 1073741824UL - 1UL; // 2Gb

struct RLEChunk
{
	char counter;
	char value;
};

enum ErrRle
{
	ERR_NO_ERROR,
	ERR_MAX_SIZE,
	ERR_FILE_CORRUPTED,
	ERR_FILE_OPEN_READ,
	ERR_FILE_OPEN_WRITE,
};

void PrintUsage()
{
	cout << "USAGE: rle.exe pack <input file> <output file>" << endl;
	cout << "       rle.exe unpack <input file> <output file>" << endl;
}

ErrRle PackFile(const char* inputFilename, const char* outputFilename)
{

	// open a file to read
	ifstream fileIn(inputFilename, ios_base::binary);
	if (!fileIn)
	{
		return ERR_FILE_OPEN_READ;
	}

	// open a file to write
	ofstream fileOut(outputFilename, ios_base::binary);
	if (!fileOut)
	{
		fileOut.close();
		return ERR_FILE_OPEN_WRITE;
	}

	RLEChunk chunk;
	unsigned long totalSize = 0;
	if (!fileIn.eof())
	{
		char newChar = fileIn.get();
		while (fileIn)
		{
			unsigned char charCount = 1;
			char oldChar = newChar;
			if (fileIn)
			{
				while (fileIn && (oldChar == (newChar = fileIn.get())) && (charCount < 255))
				{
					++charCount;
				}
			}
			chunk.counter = charCount;
			chunk.value = oldChar;
			totalSize += sizeof(chunk);
			if (totalSize > MAX_SIZE)
			{
				fileOut.close();
				return ERR_MAX_SIZE;
			}
			else
			{
				fileOut.put(chunk.counter);
				fileOut.put(chunk.value);
			}
		}
	}
	fileOut.close();
	return ERR_NO_ERROR;
}

ErrRle UnpackFile(const char* inputFilename, const char* outputFilename)
{
	// open file to read
	ifstream fileIn(inputFilename, ios_base::binary);
	if (!fileIn)
	{
		return ERR_FILE_OPEN_READ;
	}

	// open file to write
	ofstream fileOut(outputFilename, ios_base::binary);
	if (!fileOut)
	{
		fileOut.close();
		return ERR_FILE_OPEN_WRITE;
	}

	unsigned long totalSize = 0;
	char readChar;
	while ((readChar = fileIn.get()) != EOF)
	{
		unsigned char countChars = readChar;

		if (countChars == 0)
		{
			fileOut.close();
			return ERR_FILE_CORRUPTED;
		}

		totalSize += countChars;
		if (totalSize > MAX_SIZE)
		{
			fileOut.close();
			return ERR_MAX_SIZE;
		}

		char newChar;
		if ((newChar = fileIn.get()) == EOF)
		{
			fileOut.close();
			return ERR_FILE_CORRUPTED;
		}

		while (countChars--)
		{
			fileOut.put(newChar);
		}

	}
	fileOut.close();
	return ERR_NO_ERROR;
}

void printError(int err, char* arg1, char* arg2, char* arg3)
{
	switch (err)
	{
	case ERR_FILE_CORRUPTED:
		cout << "Input file " << arg2 << " is corruped. Aborting job." << endl;
		return;
	case ERR_MAX_SIZE:
		cout << "Output file " << arg3 << " max size reached. Aborting job." << endl;
		return;
	case ERR_NO_ERROR:
		cout << "File " << arg2 << " " << arg1 << "ed into " << arg3 << " succesfuly." << endl;
		return;
	case ERR_FILE_OPEN_READ:
		cout << "Can't open file " << arg2 << " to read." << endl;
		return;
	case ERR_FILE_OPEN_WRITE:
		cout << "Can't open file " << arg3 << " to write." << endl;
		return;
	default:
		return;
	}
}

int executeCommand(const char* command, const char* inputFile, const char* outputFile)
{
	int err = 0;
	if (!strcmp(command, "pack"))
	{
		err = PackFile(inputFile, outputFile);
	}
	else if (!strcmp(command, "unpack"))
	{
		err = UnpackFile(inputFile, outputFile);
	}
	else
	{
		PrintUsage();
	}
	return err;
}

int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		PrintUsage();
		return 0;
	}

	int err = executeCommand(argv[1], argv[2], argv[3]);

	printError(err, argv[1], argv[2], argv[3]);

	return err;
}

