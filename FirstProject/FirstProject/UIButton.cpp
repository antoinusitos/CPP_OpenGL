#include "UIButton.h"
#include <iostream>
#include <string>

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

	void UIButton::Init()
	{
		myMouseClickFunction = std::bind(&UIButton::Click, this);
		myMouseEnterFunction = std::bind(&UIButton::Enter, this);
		myMouseExitFunction = std::bind(&UIButton::Exit, this);

		myBaseColor = Vector3(1.0f);
		myHoverColor = Vector3(0.0f);
		myColor = myBaseColor;
	}

	void UIButton::Click()
	{
		std::cout << "Clicked on " << myName << std::endl;
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