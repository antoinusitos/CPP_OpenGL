#include "UIButton.h"
#include <iostream>
#include <string>
#include "UIManager.h"
#include "LogManager.h"

namespace Engine
{
	UIButton::UIButton(std::string aName) : UIElement(aName)
	{
		myTransform.myPosition = Vector2(75.0f / 2.0f, 20.0f / 2.0f);
		myTransform.myScale = Vector2(75.0f, 20.0f);
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
		myMouseClickFunction = std::bind(&UIButton::Click, this);
		myMouseReleaseFunction = std::bind(&UIButton::Release, this);
		myMouseHoverFunction = std::bind(&UIButton::Hover, this);
		myMouseExitFunction = std::bind(&UIButton::Exit, this);

		myBaseColor = Vector3(1.0f);
		myHoverColor = Vector3(0.0f);
		myColor = myBaseColor;
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