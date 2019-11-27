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

	GLenum LogManager::CheckError(const char* aFile, int aLine)
	{
		GLenum errorCode;
		while ((errorCode = glGetError()) != GL_NO_ERROR)
		{
			std::string error;
			switch (errorCode)
			{
			case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
			case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
			case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
			case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
			case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
			case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
			//case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
			}
			std::string s = error + " | " + aFile + " (l." + std::to_string(aLine) + ")";
			AddLog(s);
		}
		return errorCode;
	}
}