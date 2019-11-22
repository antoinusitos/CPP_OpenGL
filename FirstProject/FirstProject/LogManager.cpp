#include "LogManager.h"
#include <iostream>
#include <string>

namespace Engine
{
	LogManager* LogManager::mySingleton = nullptr;

	LogManager::LogManager()
	{
	}

	LogManager::~LogManager()
	{
	}

	LogManager* LogManager::GetInstance()
	{
		if (mySingleton == nullptr)
		{
			mySingleton = new LogManager();
		}

		return mySingleton;
	}

	void LogManager::AddLog(std::string aLog)
	{
		std::cout << aLog << std::endl;
		myLogs.push_back(aLog);
	}

}