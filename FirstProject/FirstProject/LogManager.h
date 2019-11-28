#pragma once

#include <vector>
#include <GLFW/glfw3.h>

namespace Engine
{
	class LogManager
	{
	public:
		LogManager();
		~LogManager();

		static LogManager* GetInstance();

		void AddLog(std::string aLog);

		GLenum CheckError(const char* aFile, int aLine);

		const std::vector<std::string> GetLogs();

	protected:
		std::vector<std::string> myLogs;

	private:
		static LogManager* mySingleton;
	};
}