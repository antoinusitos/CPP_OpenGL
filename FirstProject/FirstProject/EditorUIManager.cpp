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
#include "UIText.h"
#include "Data.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "EditorManager.h"

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

		Engine::UIText* saveText = new Engine::UIText(std::string("Save"));
		saveText->SetText("Save");
		saveText->CreateUI();
		saveText->Init();
		saveText->SetUIManager(this);

		Engine::UIButton* saveButton = new Engine::UIButton(std::string("Save Button"));
		saveButton->AttachUIText(saveText);
		saveButton->CreateUI();
		saveButton->Init();
		saveButton->SetUIManager(this);
		saveButton->AddUIAction(Engine::UIAction(Engine::VISIBILITY, fileMenuPanel, false));
		saveButton->AlignCollisionWithTransform();

		Engine::UIText* quitText = new Engine::UIText(std::string("Exit"));
		quitText->SetText("Exit");
		quitText->CreateUI();
		quitText->Init();
		quitText->SetUIManager(this);

		Engine::UIButton* quitButton = new Engine::UIButton(std::string("Quit Button"));
		quitButton->AttachUIText(quitText);
		quitButton->CreateUI();
		quitButton->Init();
		quitButton->SetUIManager(this);
		quitButton->AddUIAction(Engine::UIAction(Engine::QUIT, nullptr, false));
		quitButton->AlignCollisionWithTransform();

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

		Engine::UIText* fileMenuText = new Engine::UIText(std::string("File"));
		fileMenuText->SetText("File");
		fileMenuText->CreateUI();
		fileMenuText->Init();
		fileMenuText->SetUIManager(this);
		
		fileMenu->AttachUIText(fileMenuText);
		fileMenu->CreateUI();
		fileMenu->Init();
		fileMenu->SetUIManager(this);
		fileMenu->AddUIAction(Engine::UIAction(Engine::TOGGLEVISIBILITY, fileMenuPanel, true));

		Engine::UIText* editMenuText = new Engine::UIText(std::string("Edit"));
		editMenuText->SetText("Edit");
		editMenuText->CreateUI();
		editMenuText->Init();
		editMenuText->SetUIManager(this);

		Engine::UIButton* editMenu = new Engine::UIButton(std::string("Edit Menu"));
		editMenu->AttachUIText(editMenuText);
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

		/*Engine::UICheckBox* checkBox = new Engine::UICheckBox(std::string("Check Box"));
		checkBox->SetPosition(Engine::Vector2((float)width / 2.0f, (float)height / 2.0f));
		checkBox->CreateUI();
		checkBox->Init();
		checkBox->SetUIManager(this);
		checkBox->AlignCollisionWithTransform();
		myElements.push_back(checkBox);*/

		Engine::UIButton* moveRightButton = new Engine::UIButton(std::string("Move Right Button"));
		moveRightButton->SetPosition(Engine::Vector2((float)width / 2.0f, (float)height / 2.0f));
		moveRightButton->CreateUI();
		moveRightButton->Init();
		moveRightButton->AlignCollisionWithTransform();
		moveRightButton->SetUIManager(this);
		moveRightButton->AddUIAction(Engine::UIAction(Engine::POSITIONOBJECT, Engine::EditorManager::GetInstance()->myObject, 1.0f));
		myElements.push_back(moveRightButton);

		Engine::UIButton* moveLeftButton = new Engine::UIButton(std::string("Move Left Button"));
		moveLeftButton->SetPosition(Engine::Vector2((float)width / 2.0f - 60, (float)height / 2.0f));
		moveLeftButton->CreateUI();
		moveLeftButton->Init();
		moveLeftButton->AlignCollisionWithTransform();
		moveLeftButton->SetUIManager(this);
		moveLeftButton->AddUIAction(Engine::UIAction(Engine::POSITIONOBJECT, Engine::EditorManager::GetInstance()->myObject, -1.0f));
		myElements.push_back(moveLeftButton);

		Engine::UIButton* turnRightButton = new Engine::UIButton(std::string("Turn Right Button"));
		turnRightButton->SetPosition(Engine::Vector2((float)width / 2.0f, (float)height / 2.0f + 40.0f));
		turnRightButton->CreateUI();
		turnRightButton->Init();
		turnRightButton->AlignCollisionWithTransform();
		turnRightButton->SetUIManager(this);
		turnRightButton->AddUIAction(Engine::UIAction(Engine::ROTATIONOBJECT, Engine::EditorManager::GetInstance()->myObject, 1.0f));
		myElements.push_back(turnRightButton);

		Engine::UIButton* turnLeftButton = new Engine::UIButton(std::string("Turn Left Button"));
		turnLeftButton->SetPosition(Engine::Vector2((float)width / 2.0f - 60.0f, (float)height / 2.0f + 40.0f));
		turnLeftButton->CreateUI();
		turnLeftButton->Init();
		turnLeftButton->AlignCollisionWithTransform();
		turnLeftButton->SetUIManager(this);
		turnLeftButton->AddUIAction(Engine::UIAction(Engine::ROTATIONOBJECT, Engine::EditorManager::GetInstance()->myObject, -1.0f));
		myElements.push_back(turnLeftButton);

		Engine::UIButton* ScaleUpButton = new Engine::UIButton(std::string("Scale Up Button"));
		ScaleUpButton->SetPosition(Engine::Vector2((float)width / 2.0f, (float)height / 2.0f + 80.0f));
		ScaleUpButton->CreateUI();
		ScaleUpButton->Init();
		ScaleUpButton->AlignCollisionWithTransform();
		ScaleUpButton->SetUIManager(this);
		ScaleUpButton->AddUIAction(Engine::UIAction(Engine::SCALEOBJECT, Engine::EditorManager::GetInstance()->myObject, 1.0f));
		myElements.push_back(ScaleUpButton);

		Engine::UIButton* ScaleDownButton = new Engine::UIButton(std::string("Scale Down Button"));
		ScaleDownButton->SetPosition(Engine::Vector2((float)width / 2.0f - 60.0f, (float)height / 2.0f + 80.0f));
		ScaleDownButton->CreateUI();
		ScaleDownButton->Init();
		ScaleDownButton->AlignCollisionWithTransform();
		ScaleDownButton->SetUIManager(this);
		ScaleDownButton->AddUIAction(Engine::UIAction(Engine::SCALEOBJECT, Engine::EditorManager::GetInstance()->myObject, -1.0f));
		myElements.push_back(ScaleDownButton);

		Engine::UIContainerVertical* inspectorPanel = new Engine::UIContainerVertical(std::string("Inspector container"));
		inspectorPanel->SetScale(Engine::Vector2(200.0f, 200.0f));
		inspectorPanel->SetPosition(Engine::Vector2((float)width / 2.0f, (float)height / 2.0f));
		inspectorPanel->CreateUI();
		inspectorPanel->Init();
		inspectorPanel->SetUIManager(this);
		inspectorPanel->SetVisibility(false);
		inspectorPanel->AlignCollisionWithTransform();
		//inspectorPanel->AttachUIElement(moveRightButton);
		inspectorPanel->UpdateLayout();
		myElements.push_back(inspectorPanel);
	}
}