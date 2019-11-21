#include "EditorUIManager.h"
#include "UIElement.h"
#include "UIButton.h"
#include "UIPanel.h"
#include "UIContainer.h"
#include "UIContainerHorizontal.h"
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

		Engine::UIButton* editMenu = new Engine::UIButton(std::string("Edit Menu"));
		editMenu->CreateUI();
		editMenu->SetUIManager(this);

		Engine::UIContainerHorizontal* menuPanel = new Engine::UIContainerHorizontal(std::string("Menu Container Horizontal"));
		menuPanel->SetScale(Engine::Vector2((float)width, 20.0f));
		menuPanel->SetPosition(Engine::Vector2((float)width / 2.0f, 20.0f / 2.0f));
		menuPanel->CreateUI();
		menuPanel->SetUIManager(this);
		menuPanel->AttachUIElement(fileMenu);
		menuPanel->AttachUIElement(editMenu);
		menuPanel->UpdateLayout();
		myElements.push_back(menuPanel);
	}
}