#include "UIContainerHorizontal.h"

namespace Engine
{
	UIContainerHorizontal::UIContainerHorizontal(std::string aName) : UIContainer(aName)
	{
	}


	UIContainerHorizontal::~UIContainerHorizontal()
	{
	}

	void UIContainerHorizontal::UpdateLayout()
	{
		float positionX = 0.0f;
		for (unsigned int i = 0; i < myElements.size(); i++)
		{
			Vector2 scale = myElements[i]->GetScale();
			if(i == 0)
				positionX += scale.myX / 2.0f;
			else
				positionX += scale.myX;
			myElements[i]->SetPosition(Vector2(positionX, myElements[i]->GetPosition().myY));
		}
	}

}