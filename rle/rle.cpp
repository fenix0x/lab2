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

void WriteChunk(ofstream & file, RLEChunk & chunk)
{
	file.write(reinterpret_cast<char*>(&chunk), sizeof(chunk));
}

bool ReadChunk(ifstream & file, RLEChunk & chunk)
{
	file.read(reinterpret_cast<char*>(&chunk), sizeof(chunk));
	return !!file;
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
			while (fileIn && (oldChar == (newChar = fileIn.get())) && (charCount < 255))
			{
				++charCount;
			}
			chunk.counter = charCount;
			chunk.value = oldChar;
			totalSize += sizeof(chunk);
			if (totalSize > MAX_SIZE)
			{
				return ERR_MAX_SIZE;
			}
			else
			{
				WriteChunk(fileOut, chunk);
			}
		}
	}
	fileOut.close();
	return ERR_NO_ERROR;
}

void ExplodeChunk(ostream & outStream, RLEChunk const& chunk)
{
	char countChars = chunk.counter;
	while (countChars--)
	{
		outStream.put(chunk.value);
	}
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
		return ERR_FILE_OPEN_WRITE;
	}

	unsigned long totalSize = 0;
	RLEChunk chunk;
	while (ReadChunk(fileIn, chunk))
	{
		if (chunk.counter == 0)
		{
			return ERR_FILE_CORRUPTED;
		}

		totalSize += chunk.counter;
		if (totalSize > MAX_SIZE)
		{
			return ERR_MAX_SIZE;
		}

		ExplodeChunk(fileOut, chunk);

	}
	return ERR_NO_ERROR;
}

void PrintError(ErrRle err, char* command, char* inputFileName, char* outputFileName)
{
	switch (err)
	{
	case ERR_FILE_CORRUPTED:
		cout << "Input file " << inputFileName << " is corruped. Aborting job." << endl;
		return;
	case ERR_MAX_SIZE:
		cout << "Output file " << outputFileName << " max size reached. Aborting job." << endl;
		return;
	case ERR_NO_ERROR:
		cout << "File " << inputFileName << " " << command << "ed into " << outputFileName << " succesfuly." << endl;
		return;
	case ERR_FILE_OPEN_READ:
		cout << "Can't open file " << inputFileName << " to read." << endl;
		return;
	case ERR_FILE_OPEN_WRITE:
		cout << "Can't open file " << outputFileName << " to write." << endl;
		return;
	default:
		return;
	}
}

ErrRle ExecuteCommand(const char* command, const char* inputFile, const char* outputFile)
{
	ErrRle err = ERR_NO_ERROR;
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

	ErrRle err = ExecuteCommand(argv[1], argv[2], argv[3]);

	PrintError(err, argv[1], argv[2], argv[3]);

	return err;
}

