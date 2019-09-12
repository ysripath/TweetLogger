#include <iostream>
#include <thread>
#include <mutex>
#include "FileManager.h"
#include "Error.h"

using namespace std;

static int counter = 0;
mutex m;

void writeUtil(FileManager* fileManager)
{
	if (fileManager != nullptr)
	{
		for (int i = 0; i < 10; i++)
		{
			if (m.try_lock())
			{
				StatusCode ret = fileManager->writeToFile(to_string(counter++) + '\n');
				if (ret == StatusCode::FILE_WRITE_FAIL)
				{
					cout << "File write fail for record " << i << "\n";
				}
				m.unlock();
			}
			else
			{
				cout << "Couldn't lock the mutex\n";
			}
		}
	}	
}

void readUtil(FileManager* fileManager)
{
	if (fileManager != nullptr)
	{
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
	}	
}

int main()
{
	counter++;
	cout << "Hello world\n";
	FileManager* fileManager = new FileManager("Text1.txt");
	std::thread t1(writeUtil, fileManager);
	t1.join();
	std::thread t2(writeUtil, fileManager);
	std::thread t3(writeUtil, fileManager);
	
	t2.join();
	t3.join();
	
	std::thread r1(readUtil, fileManager);
	std::thread r2(readUtil, fileManager);
	std::thread r3(readUtil, fileManager);
	
	cout << "Invoked all threads\n";
	

	r1.join();
	r2.join();
	r3.join();

	cout << "All threads finished execution\n";
	return 0;
}