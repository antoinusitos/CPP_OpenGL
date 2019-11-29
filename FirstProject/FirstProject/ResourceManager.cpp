#include "ResourceManager.h"
#include "Model.h"
#include "Shader.h"
#include "LogManager.h"
#include "stb_image.h"
#include "Data.h"
#include "FileWatcher.h"
#include "FileLinkerManager.h"
#include "UIText.h"
#include "UIButton.h"

namespace Engine
{
	ResourceManager* ResourceManager::mySingleton = nullptr;

	ResourceManager::ResourceManager()
	{
		
	}

	ResourceManager::~ResourceManager()
	{
		for (int i = 0; i < myImagesInfos.size(); i++)
		{
			delete myImagesInfos[i];
		}
		for (int i = 0; i < myModels.size(); i++)
		{
			delete myModels[i];
		}
		for (int i = 0; i < myShaders.size(); i++)
		{
			delete myShaders[i];
		}
	}

	Engine::ResourceManager* ResourceManager::GetInstance()
	{
		if (mySingleton == nullptr)
		{
			mySingleton = new ResourceManager();
		}

		return mySingleton;
	}

	Model* ResourceManager::LoadModel(const std::string aName, bool aGamma)
	{
		for (int i = 0; i < myModels.size(); i++)
		{
			if (myModels[i]->myName == aName)
			{
				return myModels[i]->myModel;
			}
		}

		FileLinker* link = FileLinkerManager::GetInstance()->GetLinkedFile(aName);
		if (link != nullptr)
		{
			Model* model = new Model(link->myFile.c_str(), aGamma);
			myModels.push_back(new ModelInfos(aName, model));
			return model;
		}

		return nullptr;
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

	unsigned int ResourceManager::LoadTexture(const std::string aName, bool useCustomPath)
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

		std::string theFile = "";
		std::string thePath = "";

		FileLinker* link = FileLinkerManager::GetInstance()->GetLinkedFile(aName);
		if (link != nullptr)
		{
			theFile = std::string(link->myFile);
			thePath = std::string("Assets\\Images\\" + theFile);
			if (useCustomPath)
			{
				thePath = std::string(link->myFile);
			}
		}
		else
		{
			LogManager::GetInstance()->AddLog(std::string("Texture " + aName + " cannot be loaded from file linker"));
			link = FileLinkerManager::GetInstance()->GetLinkedFile("DefaultTexture");
			theFile = std::string(link->myFile);
			thePath = std::string("Assets\\Images\\" + theFile);
		}

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

	void ResourceManager::SetPath(const std::string aPath)
	{
		myCurrentFolder = aPath;
		myAllFiles.empty();
		UpdateFiles();
	}

	void ResourceManager::AddPath(const std::string aPath)
	{
		myLastFolder = myCurrentFolder;
		myCurrentFolder += aPath + "\\";
		SetPath(myCurrentFolder);
	}

	const std::vector<FileInfo*> ResourceManager::GetFilesInfo()
	{
		return myFiles;
	}

	void ResourceManager::PreviousPath()
	{
		std::string s = myCurrentFolder;
		std::string delimiter = "\\";

		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			s.erase(0, pos + delimiter.length());
		}
		std::string newS = myCurrentFolder;
		newS = newS.substr(0, newS.length() - token.length() - 1);
		SetPath(newS);
	}

	void ResourceManager::UpdateFiles()
	{
		/*for (int i = 0; i < myFiles.size(); i++)
		{
			delete myFiles[i];
		}*/

		myFiles.clear();

		Engine::UIText* parentfileText = new Engine::UIText(std::string("parentfileText"));
		parentfileText->SetText("..");
		parentfileText->CreateUI();
		parentfileText->Init();

		UIButton* parentFile = new UIButton(std::string("parentFile"));
		parentFile->AttachUIText(parentfileText);
		parentFile->SetColor(Vector3(1.0f, 1.0f, 1.0f));
		parentFile->CreateUI();
		parentFile->Init();
		parentFile->AlignCollisionWithTransform();
		myFiles.push_back(new FileInfo("..", FileType::DIRECTORY, parentFile));

		for (const auto & entry : std::experimental::filesystem::directory_iterator(myCurrentFolder))
		{
			std::string s = entry.path().string();
			std::string delimiter = "\\";

			size_t pos = 0;
			std::string token;
			while ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				s.erase(0, pos + delimiter.length());
			}

			Engine::UIText* fileText = new Engine::UIText(std::string("File"));
			fileText->SetText(s);
			fileText->CreateUI();
			fileText->Init();

			UIButton* aFile = new UIButton(std::string("aFile"));
			aFile->AttachUIText(fileText);
			aFile->SetColor(Vector3(1.0f, 1.0f, 1.0f));
			aFile->CreateUI();
			aFile->Init();
			aFile->AlignCollisionWithTransform();

			FileType fileType = FileType::FILE;

			std::size_t found = s.find(".");
			if (found == std::string::npos)
			{
				fileType = FileType::DIRECTORY;
			}
			else
			{
				pos = s.find(".");
				token = s.substr(0, pos);
				s.erase(0, pos + delimiter.length());
			}

			myFiles.push_back(new FileInfo(s, fileType, aFile));
		}
	}
}