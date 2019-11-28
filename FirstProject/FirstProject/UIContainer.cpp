#include "UIContainer.h"

namespace Engine
{
	UIContainer::UIContainer(std::string aName) : UIPanel(aName)
	{
	}

	UIContainer::~UIContainer()
	{
	}

	void UIContainer::Render(GLFWwindow* aWindow)
	{
		if (!myVisibility)
			return;

		if (myText != nullptr)
		{
			myText->Render(aWindow);
		}

		for (unsigned int i = 0; i < myElements.size(); i++)
		{
			myElements[i]->Render(aWindow);
		}

		UIPanel::Render(aWindow);
	}

	void UIContainer::Update(const float aDeltaTime)
	{
		if (!myVisibility && !myForceUpdate)
			return;

		for (unsigned int i = 0; i < myElements.size(); i++)
		{
			myElements[i]->Update(aDeltaTime);
		}

		UIPanel::Update(aDeltaTime);
	}

	void UIContainer::AttachUIElement(UIElement* anElement)
	{
		myElements.push_back(anElement);
	}

	void UIContainer::SetVisibility(const bool aNewVisibility)
	{
		UIPanel::SetVisibility(aNewVisibility);

		for (unsigned int i = 0; i < myElements.size(); i++)
		{
			myElements[i]->SetVisibility(aNewVisibility);
		}
	}

	void UIContainer::AttachUIText(UIElement* anElement)
	{
		myText = anElement;

		Vector2 pos = myTransform.myPosition;
		pos.myX -= myTransform.myScale.myX * 0.25f;
		pos.myY += myTransform.myScale.myY * 0.75f;

		if (myText != nullptr)
		{
			myText->SetPosition(pos);
		}
	}
}