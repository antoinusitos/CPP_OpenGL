#pragma once

#include <string>
#include <vector>

namespace Engine
{
	class Model;
	class Shader;

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		static ResourceManager* GetInstance();

		Model* LoadModel(const char* aPath, bool aGamma = false);
		Shader* LoadShader(const char* aVertexPath, const char* aFragmentPath);

	private:
		static ResourceManager* mySingleton;

		std::vector<Model*> myModels;
		std::vector<Shader*> myShaders;
	};
}