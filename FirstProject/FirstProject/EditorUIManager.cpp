#include "EditorUIManager.h"
#include "UIElement.h"
#include "UIButton.h"
#include "UIPanel.h"
#include "UIContainer.h"
#include "UIContainerHorizontal.h"
#include "UIContainerVertical.h"
#include "UIWindow.h"
#include "UICheckBox.h"
#include "UIMenuPanel.h"
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

		Engine::UIMenuPanel* fileMenuPanel = new Engine::UIMenuPanel(std::string("File Menu container"));

		Engine::UIButton* fileMenu = new Engine::UIButton(std::string("File Menu"));

		Engine::UIButton* saveButton = new Engine::UIButton(std::string("Save Button"));
		saveButton->CreateUI();
		saveButton->Init();
		saveButton->SetUIManager(this);
		saveButton->AddUIAction(Engine::UIAction(Engine::VISIBILITY, fileMenuPanel, false));

		Engine::UIButton* quitButton = new Engine::UIButton(std::string("Quit Button"));
		quitButton->CreateUI();
		quitButton->Init();
		quitButton->SetUIManager(this);
		quitButton->AddUIAction(Engine::UIAction(Engine::QUIT, nullptr, false));

		fileMenuPanel->SetScale(Engine::Vector2(quitButton->GetScale().myX, 60.0f));
		fileMenuPanel->SetPosition(Engine::Vector2(quitButton->GetScale().myX / 2.0f, fileMenu->GetScale().myY + 60.0f / 2.0f));
		fileMenuPanel->CreateUI();
		fileMenuPanel->Init();
		fileMenuPanel->SetUIManager(this);
		fileMenuPanel->AlignCollisionWithTransform();
		fileMenuPanel->AttachUIElement(saveButton);
		fileMenuPanel->AttachUIElement(quitButton);
		fileMenuPanel->UpdateLayout();
		fileMenuPanel->SetVisibility(false);
		myElements.push_back(fileMenuPanel);

		saveButton->AlignCollisionWithTransform();
		quitButton->AlignCollisionWithTransform();

		fileMenu->CreateUI();
		fileMenu->Init();
		fileMenu->SetUIManager(this);
		fileMenu->AddUIAction(Engine::UIAction(Engine::TOGGLEVISIBILITY, fileMenuPanel, true));

		Engine::UIButton* editMenu = new Engine::UIButton(std::string("Edit Menu"));
		editMenu->CreateUI();
		editMenu->Init();
		editMenu->SetUIManager(this);

		Engine::UIContainerHorizontal* menuPanel = new Engine::UIContainerHorizontal(std::string("Menu Container Horizontal"));
		menuPanel->SetScale(Engine::Vector2((float)width, 20.0f));
		menuPanel->SetPosition(Engine::Vector2((float)width / 2.0f, 20.0f / 2.0f));
		menuPanel->CreateUI();
		menuPanel->Init();
		menuPanel->SetUIManager(this);
		menuPanel->AttachUIElement(fileMenu);
		menuPanel->AttachUIElement(editMenu);
		menuPanel->UpdateLayout();
		myElements.push_back(menuPanel);

		fileMenu->AlignCollisionWithTransform();
		editMenu->AlignCollisionWithTransform();

		Engine::UIWindow* logWindow = new Engine::UIWindow(std::string("Log Window"));
		logWindow->SetPosition(Engine::Vector2(400.0f, 400.0f));
		logWindow->SetScale(Engine::Vector2(400.0f, 400.0f));
		logWindow->CreateUI();
		logWindow->SetUIManager(this);
		logWindow->Init();
		logWindow->SetVisibility(false);
		myElements.push_back(logWindow);

		Engine::UIButton* logPanel = new Engine::UIButton(std::string("Log Panel"));
		logPanel->SetScale(Engine::Vector2((float)width, 20.0f));
		logPanel->SetPosition(Engine::Vector2((float)width / 2.0f, (float)height - 20.0f / 2.0f));
		logPanel->CreateUI();
		logPanel->Init();
		logPanel->SetUIManager(this);
		logPanel->AlignCollisionWithTransform();
		logPanel->AddUIAction(Engine::UIAction(Engine::TOGGLEVISIBILITY, logWindow, true));
		logPanel->AddUIAction(Engine::UIAction(Engine::POSITION, logWindow, Engine::Vector2(400.0f, 400.0f)));
		myElements.push_back(logPanel);

		Engine::UICheckBox* checkBox = new Engine::UICheckBox(std::string("Check Box"));
		checkBox->SetPosition(Engine::Vector2((float)width / 2.0f, (float)height / 2.0f));
		checkBox->CreateUI();
		checkBox->Init();
		checkBox->SetUIManager(this);
		checkBox->AlignCollisionWithTransform();
		myElements.push_back(checkBox);
	}
}