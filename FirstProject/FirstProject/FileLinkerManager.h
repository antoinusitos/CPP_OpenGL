#pragma once

#include <vector>
#include "Data.h"

namespace Engine
{
	class FileLinkerManager
	{
	public:
		FileLinkerManager();
		~FileLinkerManager();

		static FileLinkerManager* GetInstance();

		FileLinker* GetLinkedFile(std::string aName);

	private:
		static FileLinkerManager* mySingleton;

		std::vector<FileLinker*> myFilesLinked;
	};
}