#include "UIText.h"
#include "TextManager.h"

namespace Engine
{
	UIText::UIText(std::string aName) : UIElement(aName)
	{
		myColor = Vector3(0.0f, 0.0f, 0.0f);
	}

	UIText::~UIText()
	{
	}

	void UIText::SetText(const std::string aText)
	{
		myText = aText;
	}

	void UIText::SetColor(const Vector3 aColor)
	{
		myColor = aColor;
	}

	void UIText::Render(GLFWwindow* aWindow)
	{
		TextManager::GetInstance()->RenderText(*TextManager::GetInstance()->myShader, aWindow, myText, myTransform.myPosition.myX, myTransform.myPosition.myY, 0.4f, myColor);
	}

}