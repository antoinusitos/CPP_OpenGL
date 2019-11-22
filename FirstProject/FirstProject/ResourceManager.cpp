#include "ResourceManager.h"
#include "Model.h"
#include "Shader.h"

namespace Engine
{
	ResourceManager* ResourceManager::mySingleton = nullptr;

	ResourceManager::ResourceManager()
	{
	}

	ResourceManager::~ResourceManager()
	{
	}

	Engine::ResourceManager* ResourceManager::GetInstance()
	{
		if (mySingleton == nullptr)
		{
			mySingleton = new ResourceManager();
		}

		return mySingleton;
	}

	Model* ResourceManager::LoadModel(const char* aPath, bool aGamma)
	{
		return new Model(aPath, aGamma);
	}

	Engine::Shader* ResourceManager::LoadShader(const char* aVertexPath, const char* aFragmentPath)
	{
		return new Shader(aVertexPath, aFragmentPath);
	}

}