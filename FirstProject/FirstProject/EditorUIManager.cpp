#include "EditorUIManager.h"
#include "UIElement.h"
#include "UIButton.h"
#include "UIPanel.h"
#include <iostream>
#include <GLFW/glfw3.h>

namespace Editor
{
	EditorUIManager::EditorUIManager() : Engine::UIManager()
	{
		
	}

	EditorUIManager::~EditorUIManager()
	{
	}

	void EditorUIManager::InitUIManager()
	{
		int width, height;
		glfwGetWindowSize(myWindow, &width, &height);

		Engine::UIButton* fileMenu = new Engine::UIButton(std::string("File Menu"));
		fileMenu->CreateUI();
		fileMenu->SetUIManager(this);
		myElements.push_back(fileMenu);

		Engine::UIButton* editMenu = new Engine::UIButton(std::string("Edit Menu"));
		editMenu->SetPosition(Engine::Vector2(editMenu->GetScale().myX + editMenu->GetScale().myX / 2.0f, editMenu->GetPosition().myY));
		editMenu->CreateUI();
		editMenu->SetUIManager(this);
		myElements.push_back(editMenu);

		Engine::UIPanel* menuPanel = new Engine::UIPanel(std::string("Menu Panel"));
		menuPanel->SetScale(Engine::Vector2((float)width, 20.0f));
		menuPanel->SetPosition(Engine::Vector2((float)width / 2.0f, 20.0f / 2.0f));
		menuPanel->CreateUI();
		menuPanel->SetUIManager(this);
		myElements.push_back(menuPanel);
	}
}