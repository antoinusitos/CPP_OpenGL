#pragma once

#include <vector>

namespace Engine
{
	class LogManager
	{
	public:
		LogManager();
		~LogManager();

		static LogManager* GetInstance();

		void AddLog(std::string aLog);

	protected:
		std::vector<std::string> myLogs;

	private:
		static LogManager* mySingleton;
	};
}