#pragma once

#include <experimental/filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <string>
#include <functional>
#include "Shader.h"
#include "LogManager.h"

namespace Engine
{
	// Define available file changes
	enum class FileStatus
	{
		created,
		modified,
		erased
	};

	class FileWatcher
	{
	public:
		static FileWatcher* GetInstance();

		void SetPathToWatch(std::string aPathToWatch, std::chrono::duration<int, std::milli> aDelay);

		void AddShaderToWatch(Shader* aShader);

		void SetDeltaTime(float aDeltaTime);

		// Monitor "path_to_watch" for changes and in case of a change execute the user supplied "action" function
		void Update(const std::function<void(std::string, FileStatus)> &action);

	private:
		static FileWatcher* mySingleton;

		std::string myPathToWatch;
		// Time interval at which we check the base folder for changes
		std::chrono::duration<int, std::milli> myDelay;

		// Keep a record of files from the base directory and their last modification time
		FileWatcher();

		std::vector<Shader*> myShaders;
		float myDeltaTime = 0;

	private:
		std::unordered_map<std::string, std::experimental::filesystem::file_time_type> myPaths;
		float myTime = 0;
		float myTimeToCheck = 2;

		// Check if "myPaths" contains a given key
		// If your compiler supports C++20 use myPaths.contains(key) instead of this function
		bool Contains(const std::string& aKey);
	};
}