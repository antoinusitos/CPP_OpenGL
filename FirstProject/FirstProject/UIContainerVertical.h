#pragma once
#include "UIContainer.h"

namespace Engine
{
	class UIContainerVertical : public UIContainer
	{
	public:
		UIContainerVertical(std::string aName);
		~UIContainerVertical();

		void UpdateLayout();

		void SetMySpacing(const float aValue);
	
	protected:
			float mySpacing = 0.0f;
	};
}