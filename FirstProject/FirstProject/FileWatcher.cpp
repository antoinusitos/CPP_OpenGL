#include "FileWatcher.h"

namespace Engine
{
	FileWatcher* FileWatcher::mySingleton = nullptr;

	FileWatcher::FileWatcher()
	{

	}

	FileWatcher* FileWatcher::GetInstance()
	{
		if (mySingleton == nullptr)
		{
			mySingleton = new FileWatcher();
		}

		return mySingleton;
	}

	void FileWatcher::SetPathToWatch(std::string aPathToWatch, std::chrono::duration<int, std::milli> aDelay)
	{
		myPathToWatch = aPathToWatch;
		myDelay = aDelay;
		for (auto &file : std::experimental::filesystem::recursive_directory_iterator(myPathToWatch))
		{
			myPaths[file.path().string()] = std::experimental::filesystem::last_write_time(file);
		}
	}

	void FileWatcher::AddShaderToWatch(Shader* aShader)
	{
		myShaders.push_back(aShader);
	}

	void FileWatcher::SetDeltaTime(float aDeltaTime)
	{
		myDeltaTime = aDeltaTime;
	}

	void FileWatcher::Update(const std::function<void(std::string, FileStatus)> &action)
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
			for (auto &file : std::experimental::filesystem::recursive_directory_iterator(myPathToWatch))
			{
				auto current_file_last_write_time = std::experimental::filesystem::last_write_time(file);

				// File creation
				if (!Contains(file.path().string()))
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

	bool FileWatcher::Contains(const std::string& aKey)
	{
		auto el = myPaths.find(aKey);
		return el != myPaths.end();
	}
}