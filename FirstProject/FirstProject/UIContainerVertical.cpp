#include "UIContainerVertical.h"

namespace Engine
{
	UIContainerVertical::UIContainerVertical(std::string aName) : UIContainer(aName)
	{
	}

	UIContainerVertical::~UIContainerVertical()
	{
	}

	void UIContainerVertical::UpdateLayout()
	{
		float positionY = 0.0f;
		for (unsigned int i = 0; i < myElements.size(); i++)
		{
			Vector2 scale = myElements[i]->GetScale();
			if (i == 0)
				positionY += scale.myY / 2.0f;
			else
				positionY += scale.myY;
			myElements[i]->SetPosition(Vector2(myElements[i]->GetPosition().myX, positionY));
			positionY += mySpacing;
		}
	}

	void UIContainerVertical::SetMySpacing(const float aValue)
	{
		mySpacing = aValue;
	}
}