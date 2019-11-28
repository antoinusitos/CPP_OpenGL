#include "UIButton.h"
#include <iostream>
#include <string>
#include "UIManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Shader.h"
#include "Model.h"
#include "TimeManager.h"
#include "TextManager.h"

namespace Engine
{
	UIButton::UIButton(std::string aName) : UIElement(aName)
	{
		myTransform.myPosition = Vector2(75.0f / 2.0f, 20.0f / 2.0f);
		myTransform.myScale = Vector2(75.0f, 20.0f);
		myImage = "CheckBox_Off";
	}

	UIButton::~UIButton()
	{
	}

	void UIButton::AddUIAction(UIAction anAction)
	{
		myUIActions.push_back(anAction);
	}

	void UIButton::Init()
	{
		UIElement::Init();

		myMouseClickFunction = std::bind(&UIButton::Click, this);
		myMouseReleaseFunction = std::bind(&UIButton::Release, this);
		myMouseHoverFunction = std::bind(&UIButton::Hover, this);
		myMouseExitFunction = std::bind(&UIButton::Exit, this);

		myBaseColor = Vector3(1.0f);
		myHoverColor = Vector3(0.5f);
		myColor = myBaseColor;
	}

	void UIButton::Render(GLFWwindow* aWindow)
	{
		TextManager::GetInstance()->RenderText(myUIManager->GetWindow(), myText, myTransform.myPosition.myX + myTransform.myScale.myX / 2.0f, myTransform.myPosition.myY, 0.5f, glm::vec3(0.5, 0.8f, 0.2f));

		UIElement::Render(aWindow);
	}

	void UIButton::SetText(const std::string aText)
	{
		myText = aText;
	}

	void UIButton::Click()
	{
		LogManager::GetInstance()->AddLog("Clicked on " + myName);
		myColor = Vector3(0.0f, 1.0f, 0.0f);

		for (unsigned int i = 0; i < myUIActions.size(); i++)
		{
			switch (myUIActions[i].myActionType)
			{
			case VISIBILITY:
			{
				myUIActions[i].myElement->SetVisibility(myUIActions[i].myValue2);
				break;
			}
			case TOGGLEVISIBILITY:
			{
				myUIActions[i].myElement->SetVisibility(!myUIActions[i].myElement->GetVisibility());
				break;
			}
			case QUIT:
			{
				myUIManager->Quit();
				break;
			}
			case POSITION:
			{
				myUIActions[i].myElement->SetPosition(myUIActions[i].myValue3);
				break;
			}
			case POSITIONOBJECT:
			{
				Vector3 pos = myUIActions[i].myObject->GetPosition();
				pos.myX += myUIActions[i].myValue4 * TimeManager::GetInstance()->GetDeltaTime();
				myUIActions[i].myObject->SetPosition(pos);
				break;
			}
			case ROTATIONOBJECT:
			{
				float angle = myUIActions[i].myObject->GetAngle();
				angle += myUIActions[i].myValue4 * TimeManager::GetInstance()->GetDeltaTime();
				myUIActions[i].myObject->SetAngle(angle);
				break;
			}
			case SCALEOBJECT:
			{
				Vector3 scale = myUIActions[i].myObject->GetScale();
				scale.myX += myUIActions[i].myValue4 * TimeManager::GetInstance()->GetDeltaTime();
				scale.myY += myUIActions[i].myValue4 * TimeManager::GetInstance()->GetDeltaTime();
				scale.myZ += myUIActions[i].myValue4 * TimeManager::GetInstance()->GetDeltaTime();
				myUIActions[i].myObject->SetScale(scale);
				break;
			}
			default:
				break;
			}
		}
	}

	void UIButton::Release()
	{
		//LogManager::GetInstance()->AddLog("Released on " + myName);
		myColor = myHoverColor;
	}

	void UIButton::Hover()
	{
		//LogManager::GetInstance()->AddLog("Mouse Enter on " + myName);
		myColor = myHoverColor;
	}

	void UIButton::Exit()
	{
		//LogManager::GetInstance()->AddLog("Mouse Exit on " + myName);
		myColor = myBaseColor;
	}

}