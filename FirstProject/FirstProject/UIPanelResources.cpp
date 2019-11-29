#include "UIPanelResources.h"
#include <filesystem>
#include <iostream>
#include "ResourceManager.h"
#include "UIButton.h"
#include "UIText.h"

namespace Engine
{
	UIPanelResources::UIPanelResources(std::string aName) : UIPanel(aName)
	{
		
	}

	UIPanelResources::~UIPanelResources()
	{
	}

	void UIPanelResources::Render(GLFWwindow* aWindow)
	{
		UIPanel::Render(aWindow);

		std::vector<FileInfo*> myFiles = ResourceManager::GetInstance()->GetFilesInfo();

		for (int i = 0; i < myFiles.size(); i++)
		{
			Vector2 pos = myTransform.myPosition;
			pos.myX -= myTransform.myScale.myX / 2.0f;
			pos.myY -= myTransform.myScale.myY / 2.0f;

			if (myFiles[i]->myType == FileType::DIRECTORY)
			{
				std::string s = myFiles[i]->myFile;
				if (s == "..")
				{
					myFiles[i]->myText->myMouseClickFunction = [s]()
					{
						ResourceManager::GetInstance()->PreviousPath();
					};
				}
				else
				{
					myFiles[i]->myText->myMouseClickFunction = [s]()
					{
						ResourceManager::GetInstance()->AddPath(s);
					};
				}
			}

			myFiles[i]->myText->SetPosition(Vector2(pos.myX, pos.myY + i * 20.0f));
			myFiles[i]->myText->SetUIManager(myUIManager);
			myFiles[i]->myText->AlignCollisionWithTransform();
			myFiles[i]->myText->Render(aWindow);
		}
	}

	void UIPanelResources::Update(const float aDeltaTime)
	{
		UIPanel::Update(aDeltaTime);

		std::vector<FileInfo*> myFiles = ResourceManager::GetInstance()->GetFilesInfo();

		for (int i = 0; i < myFiles.size(); i++)
		{
			myFiles[i]->myText->SetUIManager(myUIManager);
			if(myFiles[i]->myText->GetText() != nullptr)
				myFiles[i]->myText->GetText()->SetUIManager(myUIManager);
			myFiles[i]->myText->Update(aDeltaTime);
		}
	}

}