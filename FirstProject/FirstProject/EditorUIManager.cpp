#include "EditorUIManager.h"
#include "UIElement.h"
#include "UIButton.h"
#include "UIPanel.h"
#include "UIContainer.h"
#include "UIContainerHorizontal.h"
#include "UIContainerVertical.h"
#include "UIWindow.h"
#include "UIWindowLog.h"
#include "UICheckBox.h"
#include "UIMenuPanel.h"
#include "UIText.h"
#include "Data.h"
#include "Model.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "EditorManager.h"
#include "UIPanelResources.h"

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

		/*Engine::UICheckBox* checkBox = new Engine::UICheckBox(std::string("Check Box"));
		checkBox->SetPosition(Engine::Vector2((float)width / 2.0f, (float)height / 2.0f));
		checkBox->CreateUI();
		checkBox->Init();
		checkBox->SetUIManager(this);
		checkBox->AlignCollisionWithTransform();
		myElements.push_back(checkBox);*/

		// --------
		// entity name
		// --------
		Engine::UIText* name = new Engine::UIText(std::string("Name"));
		name->SetText("Name :");
		name->myCallBackText = [](Engine::UIText* aText)
		{
			Engine::Model* model = Engine::EditorManager::GetInstance()->myObject;
			if (model != nullptr)
			{
				aText->SetText("Name : " + model->GetPath());
			}
		};
		name->CreateUI();
		name->Init();
		name->SetUIManager(this);
		// --------
		// position
		// --------
		Engine::UIText* position = new Engine::UIText(std::string("Position"));
		position->SetText("Position :");
		position->CreateUI();
		position->Init();
		position->SetUIManager(this);

		Engine::UIText* posX = new Engine::UIText(std::string("posX"));
		posX->SetText("pos x : 0");
		posX->myCallBackText = [](Engine::UIText* aText)
		{ 
			Engine::Model* model = Engine::EditorManager::GetInstance()->myObject;
			if (model != nullptr)
			{
				aText->SetText("X : " + std::to_string(model->GetPosition().myX));
			}
		};
		posX->CreateUI();
		posX->Init();
		posX->SetUIManager(this);

		Engine::UIText* posY = new Engine::UIText(std::string("posY"));
		posY->SetText("pos y : 0");
		posY->myCallBackText = [](Engine::UIText* aText)
		{
			Engine::Model* model = Engine::EditorManager::GetInstance()->myObject;
			if (model != nullptr)
			{
				aText->SetText("Y : " + std::to_string(model->GetPosition().myY));
			}
		};
		posY->CreateUI();
		posY->Init();
		posY->SetUIManager(this);

		Engine::UIText* posZ = new Engine::UIText(std::string("posZ"));
		posZ->SetText("pos z : 0");
		posZ->myCallBackText = [](Engine::UIText* aText)
		{
			Engine::Model* model = Engine::EditorManager::GetInstance()->myObject;
			if (model != nullptr)
			{
				aText->SetText("Z : " + std::to_string(model->GetPosition().myZ));
			}
		};
		posZ->CreateUI();
		posZ->Init();
		posZ->SetUIManager(this);

		// --------
		// rotation
		// --------
		Engine::UIText* rotation = new Engine::UIText(std::string("Rotation"));
		rotation->SetText("Rotation :");
		rotation->CreateUI();
		rotation->Init();
		rotation->SetUIManager(this);

		Engine::UIText* rotX = new Engine::UIText(std::string("rotX"));
		rotX->SetText("rot x : 0");
		rotX->myCallBackText = [](Engine::UIText* aText)
		{
			Engine::Model* model = Engine::EditorManager::GetInstance()->myObject;
			if (model != nullptr)
			{
				aText->SetText("X : " + std::to_string(model->GetRotation().myX));
			}
		};
		rotX->CreateUI();
		rotX->Init();
		rotX->SetUIManager(this);

		Engine::UIText* rotY = new Engine::UIText(std::string("rotY"));
		rotY->SetText("rot y : 0");
		rotY->myCallBackText = [](Engine::UIText* aText)
		{
			Engine::Model* model = Engine::EditorManager::GetInstance()->myObject;
			if (model != nullptr)
			{
				aText->SetText("Y : " + std::to_string(model->GetRotation().myY));
			}
		};
		rotY->CreateUI();
		rotY->Init();
		rotY->SetUIManager(this);

		Engine::UIText* rotZ = new Engine::UIText(std::string("rotZ"));
		rotZ->SetText("rot z : 0");
		rotZ->myCallBackText = [](Engine::UIText* aText)
		{
			Engine::Model* model = Engine::EditorManager::GetInstance()->myObject;
			if (model != nullptr)
			{
				aText->SetText("Z : " + std::to_string(model->GetRotation().myZ));
			}
		};
		rotZ->CreateUI();
		rotZ->Init();
		rotZ->SetUIManager(this);

		// --------
		// scale
		// --------
		Engine::UIText* scale = new Engine::UIText(std::string("Scale"));
		scale->SetText("Scale :");
		scale->CreateUI();
		scale->Init();
		scale->SetUIManager(this);

		Engine::UIText* scaleX = new Engine::UIText(std::string("scaleX"));
		scaleX->SetText("scale x : 0");
		scaleX->myCallBackText = [](Engine::UIText* aText)
		{
			Engine::Model* model = Engine::EditorManager::GetInstance()->myObject;
			if (model != nullptr)
			{
				aText->SetText("X : " + std::to_string(model->GetScale().myX));
			}
		};
		scaleX->CreateUI();
		scaleX->Init();
		scaleX->SetUIManager(this);

		Engine::UIText* scaleY = new Engine::UIText(std::string("scaleY"));
		scaleY->SetText("scale y : 0");
		scaleY->myCallBackText = [](Engine::UIText* aText)
		{
			Engine::Model* model = Engine::EditorManager::GetInstance()->myObject;
			if (model != nullptr)
			{
				aText->SetText("Y : " + std::to_string(model->GetScale().myY));
			}
		};
		scaleY->CreateUI();
		scaleY->Init();
		scaleY->SetUIManager(this);

		Engine::UIText* scaleZ = new Engine::UIText(std::string("scaleZ"));
		scaleZ->SetText("scale z : 0");
		scaleZ->myCallBackText = [](Engine::UIText* aText)
		{
			Engine::Model* model = Engine::EditorManager::GetInstance()->myObject;
			if (model != nullptr)
			{
				aText->SetText("Z : " + std::to_string(model->GetScale().myZ));
			}
		};
		scaleZ->CreateUI();
		scaleZ->Init();
		scaleZ->SetUIManager(this);

		Engine::UIContainerVertical* inspectorPanel = new Engine::UIContainerVertical(std::string("Inspector container"));
		inspectorPanel->SetScale(Engine::Vector2(200.0f, height - 20.0f));
		inspectorPanel->SetPosition(Engine::Vector2((float)width - 200.0f / 2.0f, (float)height / 2.0f + 10.0f));
		inspectorPanel->CreateUI();
		inspectorPanel->Init();
		inspectorPanel->SetUIManager(this);
		inspectorPanel->SetMySpacing(10);
		inspectorPanel->SetColor(Engine::Vector3(0.0f, 0.5f, 0.0f));
		inspectorPanel->SetVisibility(false);
		inspectorPanel->myVisibilityCallback = [](Engine::UIElement* anElement)
		{
			Engine::Model* model = Engine::EditorManager::GetInstance()->myObject;
			if (model != nullptr)
			{
				anElement->SetVisibility(true);
			}
			else
			{
				anElement->SetVisibility(false);
			}
		};
		inspectorPanel->AlignCollisionWithTransform();
		inspectorPanel->AttachUIElement(name);
		inspectorPanel->AttachUIElement(position);
		inspectorPanel->AttachUIElement(posX);
		inspectorPanel->AttachUIElement(posY);
		inspectorPanel->AttachUIElement(posZ);
		inspectorPanel->AttachUIElement(rotation);
		inspectorPanel->AttachUIElement(rotX);
		inspectorPanel->AttachUIElement(rotY);
		inspectorPanel->AttachUIElement(rotZ);
		inspectorPanel->AttachUIElement(scale);
		inspectorPanel->AttachUIElement(scaleX);
		inspectorPanel->AttachUIElement(scaleY);
		inspectorPanel->AttachUIElement(scaleZ);
		inspectorPanel->UpdateLayout();
		myElements.push_back(inspectorPanel);


		Engine::UIPanelResources* panelResource = new Engine::UIPanelResources(std::string("Panel Resources"));
		panelResource->SetScale(Engine::Vector2(200.0f, 200.0f));
		panelResource->SetPosition(Engine::Vector2(width / 2.0f, height / 2.0f));
		panelResource->CreateUI();
		panelResource->Init();
		panelResource->SetUIManager(this);
		panelResource->SetColor(Engine::Vector3(0.0f, 0.0f, 0.8f));
		panelResource->AlignCollisionWithTransform();
		myElements.push_back(panelResource);

		// -------------------
		// keep log at the end
		// -------------------
		Engine::UIWindowLog* logWindow = new Engine::UIWindowLog(std::string("Log Window"));
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
	}
}