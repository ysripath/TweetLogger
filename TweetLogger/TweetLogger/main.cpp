#include <iostream>
#include "FileManager.h"
#include "Error.h"

using namespace std;

int main()
{
	cout << "Hello world\n";
	FileManager* fileManager = new FileManager("Text1.txt");
	for (int i = 0; i < 10; i++)
	{		
		StatusCode ret = fileManager->writeToFile(to_string(i + 1)+'\n');
		if (ret == StatusCode::FILE_WRITE_FAIL)
		{
			cout << "File write fail for record " << i << "\n";
		}
	}
	string readData = "";
	StatusCode ret = fileManager->readFromFile(readData);
	if (ret == StatusCode::FILE_READ_FAIL)
	{
		cout << "File read fail\n";
		cout << readData << "\n";
	}
	else
	{
		cout << readData << "\n";
	}
	
	return 0;
}