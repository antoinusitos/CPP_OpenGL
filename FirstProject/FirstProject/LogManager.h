#pragma once

#include <vector>

namespace Engine
{
	class UIText;

	class LogManager
	{
	public:
		LogManager();
		~LogManager();

		static LogManager* GetInstance();

		void AddLog(std::string aLog);

		unsigned int CheckError(const char* aFile, int aLine);

		const std::vector<std::string> GetLogs();
		const std::vector<UIText*> GetLogsText();

	protected:
		std::vector<std::string> myLogs;
		std::vector<UIText*> myLogsText;

	private:
		static LogManager* mySingleton;
	};
}