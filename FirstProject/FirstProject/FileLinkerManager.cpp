#include "FileLinkerManager.h"
#include "Data.h"
#include <iostream>
#include <fstream>
#include "LogManager.h"

namespace Engine
{
	FileLinkerManager* FileLinkerManager::mySingleton = nullptr;

	FileLinkerManager::FileLinkerManager()
	{
		std::string line;
		std::ifstream myfile("FileLinker.txt");
		if (myfile.is_open())
		{
			std::string delimiter = ";";
			while (getline(myfile, line))
			{
				size_t pos = 0;
				pos = line.find(delimiter);
				std::string name = line.substr(0, pos);
				std::cout << name << std::endl;
				line.erase(0, pos + delimiter.length());
				std::cout << line << std::endl;

				myFilesLinked.push_back(new FileLinker(name, line));
			}
			myfile.close();
		}

		else
		{
			LogManager::GetInstance()->AddLog("Unable to open File Linker file");
		}
	}

	FileLinkerManager::~FileLinkerManager()
	{
	}

	FileLinkerManager* FileLinkerManager::GetInstance()
	{
		if (mySingleton == nullptr)
		{
			mySingleton = new FileLinkerManager();
		}

		return mySingleton;
	}

	FileLinker* FileLinkerManager::GetLinkedFile(std::string aName)
	{
		for (unsigned int i = 0; i < myFilesLinked.size(); i++)
		{
			std::cout << "compare " << aName << " with " << myFilesLinked[i]->myFileName << std::endl;
			if (myFilesLinked[i]->myFileName == aName)
				return myFilesLinked[i];
		}

		return nullptr;
	}

}