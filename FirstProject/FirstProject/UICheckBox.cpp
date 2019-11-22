#include "UICheckBox.h"

namespace Engine
{
	UICheckBox::UICheckBox(std::string aName) : UIElement(aName)
	{
		myTransform.myPosition = Vector2(75.0f / 2.0f, 20.0f / 2.0f);
		myTransform.myScale = Vector2(30.0f, 30.0f);
		myUncheckedColor = Vector3(1.0f);
		myHoverColor = Vector3(0.5f);
		myCheckedColor = Vector3(0.0f);
	}

	UICheckBox::~UICheckBox()
	{
	}

	void UICheckBox::Init()
	{
		myMouseClickFunction = std::bind(&UICheckBox::Click, this);
		myMouseHoverFunction = std::bind(&UICheckBox::Hover, this);
		myMouseExitFunction = std::bind(&UICheckBox::Exit, this);

		myColor = myUncheckedColor;
	}

	void UICheckBox::Click()
	{
		myIsChecked = !myIsChecked;
		if (myIsChecked)
		{
			myColor = myCheckedColor;
		}
		else
		{
			myColor = myUncheckedColor;
		}
	}

	void UICheckBox::Hover()
	{
		if (!myIsChecked)
		{
			myColor = myHoverColor;
		}
	}

	void UICheckBox::Exit()
	{
		if (!myIsChecked)
		{
			myColor = myUncheckedColor;
		}
	}

}