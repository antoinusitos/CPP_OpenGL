#pragma once

#include <string>
#include <vector>

namespace Engine
{
	class Model;
	class Shader;
	struct ImageInfos;
	struct ShaderInfos;
	struct ModelInfos;

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		static ResourceManager* GetInstance();

		Model* LoadModel(const std::string aName, bool aGamma = false);
		Shader* LoadShader(const std::string aName, const char* aVertexPath, const char* aFragmentPath);
		unsigned int LoadTexture(const std::string aName, bool useCustomPath = false);

	private:
		static ResourceManager* mySingleton;

		std::vector<ModelInfos*> myModels;
		std::vector<ShaderInfos*> myShaders;
		std::vector<ImageInfos*> myImagesInfos;
	};
}