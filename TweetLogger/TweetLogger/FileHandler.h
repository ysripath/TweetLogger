#pragma once
#include <fstream>
#include <iostream>
#include <mutex>
#include "TweetData.h"
#include "Error.h"
using namespace std;

class FileHandler
{
private:
	string _fileName;
	TweetData* _data;
	mutex mu;
public:
	FileHandler(string fileNameStr)
	{
		_fileName = fileNameStr;
		_data = nullptr;
	}
	FileHandler(string fileNameStr, TweetData* tweetData)
	{
		_fileName = fileNameStr;
		_data = tweetData;
	}

	StatusCode writeToFile(string data)
	{
		ofstream of;
		if (mu.try_lock())
		{


			try
			{
				of.open(_fileName, std::ios::app);
				of.clear();
				string temp = data;

				of.write(temp.c_str(), temp.length());
				of.close();
			}
			catch (exception ex)
			{
				string temp = "Exception while writing to file for -  ";
				cout << temp << "\n";
				if (of.is_open())
					of.close();
				mu.unlock();
				return StatusCode::FILE_WRITE_FAIL;
			}
			mu.unlock();
		}

		return StatusCode::FILE_WRITE_OK;
	}

	StatusCode writeToFile()
	{
		ofstream of;
		try
		{
			of.open(_fileName);
			string temp = _data->printTweetData();
			of.write(temp.c_str(), temp.length());
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

	StatusCode readFromFile(string &data)
	{
		ifstream ifSt;
		if (mu.try_lock())
		{
			try
			{
				ifSt.open(_fileName);
				while (!ifSt.eof())
				{
					char buf[10];
					ifSt.getline(buf, 10, '\n');
					data += buf;
					data += '\n';
				}
			}
			catch (exception ex)
			{
				cout << "Exception thrown during read \n";
				mu.unlock();
				return StatusCode::FILE_READ_FAIL;
			}
			mu.unlock();
		}

		return StatusCode::FILE_READ_OK;
	}
};