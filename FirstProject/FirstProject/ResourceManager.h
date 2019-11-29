#pragma once

#include <string>
#include <vector>
#include "Data.h"

namespace Engine
{
	class Model;
	class Shader;
	struct ImageInfos;
	struct ShaderInfos;
	struct ModelInfos;
	class UIText;

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		static ResourceManager* GetInstance();

		Model* LoadModel(const std::string aName, bool aGamma = false);
		Shader* LoadShader(const std::string aName, const char* aVertexPath, const char* aFragmentPath);
		unsigned int LoadTexture(const std::string aName, bool useCustomPath = false);

		void SetPath(const std::string aPath);

		void AddPath(const std::string aPath);

		const std::vector<FileInfo*> GetFilesInfo();

		void PreviousPath();

	private:
		static ResourceManager* mySingleton;

		std::string myCurrentFolder = "";
		std::string myLastFolder = "";
		std::vector<std::string> myAllFiles;
		std::vector<FileInfo*> myFiles;

		void UpdateFiles();

		std::vector<ModelInfos*> myModels;
		std::vector<ShaderInfos*> myShaders;
		std::vector<ImageInfos*> myImagesInfos;
	};
}