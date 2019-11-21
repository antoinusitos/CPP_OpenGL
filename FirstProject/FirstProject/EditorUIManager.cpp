#include "EditorUIManager.h"
#include "UIElement.h"
#include "UIButton.h"
#include <iostream>

namespace Editor
{
	EditorUIManager::EditorUIManager() : Engine::UIManager()
	{
		Engine::UIButton* fileMenu = new Engine::UIButton(std::string("File Menu"));
		fileMenu->CreateUI();
		fileMenu->SetUIManager(this);
		myElements.push_back(fileMenu);

		Engine::UIButton* editMenu = new Engine::UIButton(std::string("Edit Menu"));
		editMenu->SetPosition(Engine::Vector2(editMenu->GetScale().myX + editMenu->GetScale().myX / 2.0f, editMenu->GetPosition().myY));
		editMenu->CreateUI();
		editMenu->SetUIManager(this);
		myElements.push_back(editMenu);
	}

	EditorUIManager::~EditorUIManager()
	{
	}
}