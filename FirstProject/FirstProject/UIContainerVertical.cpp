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
		float elementSize = 0.0f;
		for (unsigned int i = 0; i < myElements.size(); i++)
		{
			Vector2 scale = myElements[i]->GetScale();
			elementSize = scale.myY;
			if (i == 0)
				positionY += scale.myY / 2.0f;
			else
				positionY += scale.myY;
			myElements[i]->SetPosition(Vector2(myTransform.myPosition.myX - myTransform.myScale.myX / 2.0f, myTransform.myPosition.myY - myTransform.myScale.myY / 2.0f + positionY));
			positionY += mySpacing;
		}

		if (mySizeToContent)
		{
			myTransform.myScale = Vector2(myTransform.myScale.myX, myElements.size() * elementSize);
		}
	}

	void UIContainerVertical::SetMySpacing(const float aValue)
	{
		mySpacing = aValue;
	}

	void UIContainerVertical::SetSizeToContent(const bool aValue)
	{
		mySizeToContent = aValue;
	}

}