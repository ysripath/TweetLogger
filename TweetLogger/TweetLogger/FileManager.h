#pragma once
#include <fstream>
#include "FileHandler.h"
#include "Error.h"
using namespace std;

class FileManager
{
private:
	string _fileName;
	FileHandler* _fileHandler;
public:
	FileManager(string fileName):_fileName(fileName)
	{
		_fileHandler = new FileHandler(_fileName);
	}
	StatusCode writeToFile(string data)
	{
		return _fileHandler->writeToFile(data);
	}

	StatusCode readFromFile(string &data)
	{
		return _fileHandler->readFromFile(data);
	}
};
