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
		std::string path_to_watch;
		// Time interval at which we check the base folder for changes
		std::chrono::duration<int, std::milli> delay;

		// Keep a record of files from the base directory and their last modification time
		FileWatcher(std::string path_to_watch, std::chrono::duration<int, std::milli> delay) : path_to_watch{ path_to_watch }, delay{ delay } {
			for (auto &file : std::experimental::filesystem::recursive_directory_iterator(path_to_watch)) {
				myPaths[file.path().string()] = std::experimental::filesystem::last_write_time(file);

			}
		}

		// Monitor "path_to_watch" for changes and in case of a change execute the user supplied "action" function
		void Update(const std::function<void(std::string, FileStatus)> &action)
		{
			myTime += myDeltaTime;
			if (myTime >= myTimeToCheck)
			{
				myTime = 0;
				auto it = myPaths.begin();
				while (it != myPaths.end())
				{
					if (!std::experimental::filesystem::exists(it->first))
					{
						action(it->first, FileStatus::erased);
						it = myPaths.erase(it);

					}
					else
					{
						it++;
					}
				}

				// Check if a file was created or modified
				for (auto &file : std::experimental::filesystem::recursive_directory_iterator(path_to_watch))
				{
					auto current_file_last_write_time = std::experimental::filesystem::last_write_time(file);

					// File creation
					if (!contains(file.path().string()))
					{
						myPaths[file.path().string()] = current_file_last_write_time;
						action(file.path().string(), FileStatus::created);
						// File modification

					}
					else
					{
						if (myPaths[file.path().string()] != current_file_last_write_time)
						{
							myPaths[file.path().string()] = current_file_last_write_time;
							action(file.path().string(), FileStatus::modified);

							LogManager::GetInstance()->AddLog("checking shaders ...");

							std::string filePath = file.path().string();
							std::string delimiter = "\\";
							size_t pos = 0;
							std::string token;
							while ((pos = filePath.find(delimiter)) != std::string::npos) {
								token = filePath.substr(0, pos);
								filePath.erase(0, pos + delimiter.length());
							}

							for (unsigned int i = 0; i < myShaders.size(); i++)
							{
								if (myShaders[i]->GetFragmentPath() == filePath.c_str())
								{
									LogManager::GetInstance()->AddLog("Compiling Shader " + filePath);
									myShaders[i]->UpdateShader();
									return;
								}
								else if (myShaders[i]->GetVertexPath() == filePath.c_str())
								{
									LogManager::GetInstance()->AddLog("Compiling Shader " + filePath);
									myShaders[i]->UpdateShader();
									return;
								}
							}
						}
					}
				}
			}
		}

		std::vector<Shader*> myShaders;
		float myDeltaTime = 0;

	private:
		std::unordered_map<std::string, std::experimental::filesystem::file_time_type> myPaths;
		float myTime = 0;
		float myTimeToCheck = 2;

		// Check if "myPaths" contains a given key
		// If your compiler supports C++20 use myPaths.contains(key) instead of this function
		bool contains(const std::string &key)
		{
			auto el = myPaths.find(key);
			return el != myPaths.end();
		}
	};
}