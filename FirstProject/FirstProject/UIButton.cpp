#include "UIButton.h"
#include <iostream>
#include <string>
#include "UIManager.h"

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
		myMouseEnterFunction = std::bind(&UIButton::Enter, this);
		myMouseExitFunction = std::bind(&UIButton::Exit, this);

		myBaseColor = Vector3(1.0f);
		myHoverColor = Vector3(0.0f);
		myColor = myBaseColor;
	}

	void UIButton::Click()
	{
		std::cout << "Clicked on " << myName << std::endl;
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
			case QUIT:
			{
				myUIManager->Quit();
				break;
			}
			default:
				break;
			}
		}
	}

	void UIButton::Release()
	{
		std::cout << "Released on " << myName << std::endl;
		myColor = myHoverColor;
	}

	void UIButton::Enter()
	{
		std::cout << "Mouse Enter" << std::endl;
		myColor = myHoverColor;
	}

	void UIButton::Exit()
	{
		std::cout << "Mouse Exit" << std::endl;
		myColor = myBaseColor;
	}

}