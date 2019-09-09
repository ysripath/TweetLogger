#pragma once
#include <fstream>
#include <iostream>
#include "TweetData.h"
#include "Error.h"
using namespace std;

class FileHandler
{
private:
	string _fileName;
	TweetData* _data;
public:
	FileHandler(string fileNameStr, TweetData* tweetData)
	{
		_fileName = fileNameStr;
		_data = tweetData;
	}

	StatusCode writeToFile()
	{
		ofstream of;
		try
		{
			of.open(_fileName);
			string temp = _data->printTweetData();
			of.write(temp.c_str(), temp.length);
			of.close();
		}
		catch (exception ex)
		{
			string temp = "Exception while writing to file for -  ";
			cout << temp + _data << "\n";
			if (of.is_open())
				of.close();
			return StatusCode::FILE_WRITE_FAIL;
		}

		return StatusCode::FILE_WRITE_OK;
	}
};