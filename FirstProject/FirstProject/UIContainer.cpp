#include "UIContainer.h"

namespace Engine
{
	UIContainer::UIContainer(std::string aName) : UIPanel(aName)
	{
	}

	UIContainer::~UIContainer()
	{
	}

	void UIContainer::Render(Shader* aShader)
	{
		for (unsigned int i = 0; i < myElements.size(); i++)
		{
			myElements[i]->Render(aShader);
		}

		UIPanel::Render(aShader);
	}

	void UIContainer::Update(const float aDeltaTime)
	{
		UIPanel::Update(aDeltaTime);

		for (unsigned int i = 0; i < myElements.size(); i++)
		{
			myElements[i]->Update(aDeltaTime);
		}
	}

	void UIContainer::AttachUIElement(UIElement* anElement)
	{
		myElements.push_back(anElement);
	}

}