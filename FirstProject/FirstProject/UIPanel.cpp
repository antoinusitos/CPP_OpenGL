#include "UIPanel.h"
#include <iostream>

namespace Engine
{
	UIPanel::UIPanel(std::string aName) : UIElement(aName)
	{
		myTransform.myPosition = Vector2(100.0f / 2.0f, 100.0f / 2.0f);
		myTransform.myScale = Vector2(100.0f, 100.0f);
	}

	UIPanel::~UIPanel()
	{
	}

	void UIPanel::Init()
	{
		UIElement::Init();
		myColor = Vector3(0.3f);
	}
}