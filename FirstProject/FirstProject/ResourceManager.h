#pragma once

#include <string>
#include <vector>

namespace Engine
{
	class Model;
	class Shader;
	struct ImageInfos;
	struct ShaderInfos;

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		static ResourceManager* GetInstance();

		Model* LoadModel(const char* aPath, bool aGamma = false);
		Shader* LoadShader(const std::string aName, const char* aVertexPath, const char* aFragmentPath);
		unsigned int LoadTexture(const std::string aName, const char* aPath);

	private:
		static ResourceManager* mySingleton;

		std::vector<Model*> myModels;
		std::vector<ShaderInfos*> myShaders;
		std::vector<ImageInfos*> myImagesInfos;
	};
}