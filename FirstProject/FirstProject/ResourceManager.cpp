#include "ResourceManager.h"
#include "Model.h"
#include "Shader.h"
#include "LogManager.h"
#include "stb_image.h"
#include "Data.h"
#include "FileWatcher.h"

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

	Shader* ResourceManager::LoadShader(const std::string aName, const char* aVertexPath, const char* aFragmentPath)
	{
		for (int i = 0; i < myImagesInfos.size(); i++)
		{
			if (myImagesInfos[i]->myName == aName)
			{
				return myShaders[i]->myShader;
			}
		}

		Shader* shader = new Shader(aVertexPath, aFragmentPath);
		myShaders.push_back(new ShaderInfos(aName, shader));
		FileWatcher::GetInstance()->AddShaderToWatch(shader);
		return shader;
	}

	unsigned int ResourceManager::LoadTexture(const std::string aName, const char* aPath)
	{
		for (int i = 0; i < myImagesInfos.size(); i++)
		{
			if (myImagesInfos[i]->myName == aName)
			{
				return myImagesInfos[i]->myID;
			}
		}

		unsigned int textureID;
		glGenTextures(1, &textureID);

		std::string theFile = std::string(aPath);
		std::string thePath = std::string("Images/" + theFile);

		int width, height, nrComponents;
		unsigned char *data = stbi_load(thePath.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);

			myImagesInfos.push_back(new ImageInfos(aName, textureID));
		}
		else
		{
			LogManager::GetInstance()->AddLog("Texture failed to load at path: " + thePath);
			stbi_image_free(data);
		}

		return textureID;
	}
}