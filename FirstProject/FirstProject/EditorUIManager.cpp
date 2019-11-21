#include "EditorUIManager.h"
#include "UIElement.h"
#include "UIButton.h"
#include "UIPanel.h"
#include "UIContainer.h"
#include "UIContainerHorizontal.h"
#include "UIContainerVertical.h"
#include "Data.h"
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

		Engine::UIContainerVertical* fileMenuPanel = new Engine::UIContainerVertical(std::string("File Menu container"));

		Engine::UIButton* fileMenu = new Engine::UIButton(std::string("File Menu"));

		Engine::UIButton* saveButton = new Engine::UIButton(std::string("Save Button"));
		saveButton->CreateUI();
		saveButton->SetUIManager(this);
		saveButton->AddUIAction(Engine::UIAction(Engine::VISIBILITY, fileMenuPanel, false));

		Engine::UIButton* quitButton = new Engine::UIButton(std::string("Quit Button"));
		quitButton->CreateUI();
		quitButton->SetUIManager(this);
		quitButton->AddUIAction(Engine::UIAction(Engine::QUIT, nullptr, false));

		//Engine::UIContainerVertical* fileMenuPanel = new Engine::UIContainerVertical(std::string("File Menu container"));
		fileMenuPanel->SetScale(Engine::Vector2(quitButton->GetScale().myX, 60.0f));
		fileMenuPanel->SetPosition(Engine::Vector2(quitButton->GetScale().myX / 2.0f, fileMenu->GetScale().myY + 60.0f / 2.0f));
		fileMenuPanel->CreateUI();
		fileMenuPanel->SetUIManager(this);
		fileMenuPanel->AttachUIElement(saveButton);
		fileMenuPanel->AttachUIElement(quitButton);
		fileMenuPanel->UpdateLayout();
		fileMenuPanel->SetVisibility(false);
		myElements.push_back(fileMenuPanel);

		//Engine::UIButton* fileMenu = new Engine::UIButton(std::string("File Menu"));
		fileMenu->CreateUI();
		fileMenu->SetUIManager(this);
		fileMenu->AddUIAction(Engine::UIAction(Engine::VISIBILITY, fileMenuPanel, true));

		Engine::UIButton* editMenu = new Engine::UIButton(std::string("Edit Menu"));
		editMenu->CreateUI();
		editMenu->SetUIManager(this);
		editMenu->AddUIAction(Engine::UIAction(Engine::VISIBILITY, fileMenuPanel, false));

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