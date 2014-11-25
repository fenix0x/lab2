#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

const unsigned long MAX_SIZE = 2UL * 1073741824UL - 1UL; // 2Gb
const long BUF_SIZE = 1024;

enum ErrRle 
{ 
	ERR_NO_ERROR,
	ERR_MAX_SIZE, 
	ERR_ZERO_LENGTH_FILE, 
};

void PrintUsage() 
{
	cout << "USAGE: rle.exe pack <input file> <output file>" << endl;
	cout << "       rle.exe unpack <input file> <output file>" << endl;
}

ErrRle PackFile(ifstream& fileIn, ofstream& fileOut)
{
	unsigned char bufferOut[2];
	unsigned long bufferSize = sizeof(bufferOut);
	unsigned long totalSize = 0;
	if (!fileIn.eof())
	{
		unsigned char newChar = fileIn.get();
		while (!fileIn.eof())
		{
			unsigned char charCount = 1;
			unsigned char oldChar = newChar;
			if (!fileIn.eof())
			{
				while (!fileIn.eof() && (oldChar == (newChar = fileIn.get())) && (charCount < 255))
				{
					++charCount;
				}
			}
			bufferOut[0] = charCount;
			bufferOut[1] = oldChar;
			totalSize += bufferSize;
			if (totalSize > MAX_SIZE)
			{
				return ERR_MAX_SIZE;
			} 
			else
			{
				fileOut.write(reinterpret_cast<const char*>(bufferOut), bufferSize);
			}
		}
	}
	if (totalSize == 0)
	{
		return ERR_ZERO_LENGTH_FILE;
	}
	return ERR_NO_ERROR;
}

ErrRle UnpackChars(unsigned char* & bufferIn, long bufferInSize, ofstream& fileOut, unsigned long& totalBufferOutSize)
{
	unsigned char* bufferOut = new unsigned char[BUF_SIZE];
	for (int i = 0; i < bufferInSize; i += 2)
	{
		unsigned long bufferOutSize = 0;
		unsigned char countChars = bufferIn[i];
		unsigned char newChar = bufferIn[i + 1];
		for (unsigned char j = 0; j < countChars; ++j)
		{
			bufferOut[bufferOutSize++] = newChar;
		}
		totalBufferOutSize += bufferOutSize;
		if (totalBufferOutSize > MAX_SIZE)
		{
			delete[] bufferOut;
			return ERR_MAX_SIZE;
		}
		fileOut.write(reinterpret_cast<char*>(bufferOut), bufferOutSize);
	}
	delete[] bufferOut;
	return ERR_NO_ERROR;
}

ErrRle UnpackFile(ifstream& fileIn, ofstream& fileOut)
{
	unsigned long totalSize = 0;
	while (!fileIn.eof())
	{
		unsigned char* bufferIn = new unsigned char[BUF_SIZE];
		ErrRle err = ERR_NO_ERROR;
		while (fileIn.read(reinterpret_cast<char*>(bufferIn), BUF_SIZE))
		{
			err = UnpackChars(bufferIn, BUF_SIZE, fileOut, totalSize);
			if (err != 0)
			{
				delete[] bufferIn;
				return err;
			}
		}
		err = UnpackChars(bufferIn, fileIn.gcount(), fileOut, totalSize);
		delete[] bufferIn;
		if (err != 0)
			return err;
	}
	return ERR_NO_ERROR;
}

int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		PrintUsage();
		return 0;
	}

	char* command = argv[1];
	if ((command != "pack") && (command == "unpack"))
	{
		PrintUsage();
		return 0;
	}

	char* inputFilename = argv[2];
	char* outputFilename = argv[3];

	// open a file to read
	ifstream fIn(inputFilename, ifstream::binary);
	if (!fIn.good())
	{
		cout << "File " << inputFilename << " opening error." << endl;
		return 1;
	}

	// open a file to write
	ofstream fOut(outputFilename, ofstream::binary);
	if (!fOut.good())
	{
		cout << "File " << outputFilename << " opening error." << endl;
		return 1;
	}

	int err = 0;
	if (strcmp(command, "pack") == 0)
	{
		err = PackFile(fIn, fOut);
	}
	else
	{
		err = UnpackFile(fIn, fOut);
	}

	fOut.close();

	switch (err)
	{
	case ERR_MAX_SIZE:
		cout << "Output file " << outputFilename << " max size reached. Aborting job." << endl;
		return 1;
	case ERR_ZERO_LENGTH_FILE:
		cout << "Warning! Intput file " << inputFilename << " is empty." << endl;
		break;
	case ERR_NO_ERROR:
		cout << "File " << inputFilename << " " << command << "ed into " << outputFilename << " succesfuly." << endl;
		break;
	default:
		break;
	}

	return 0;
}

