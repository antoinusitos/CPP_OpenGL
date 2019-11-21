#pragma once
#include "UIContainer.h"

namespace Engine
{
	class UIContainerHorizontal : public UIContainer
	{
	public:
		UIContainerHorizontal(std::string aName);
		~UIContainerHorizontal();

		void UpdateLayout();
	};
}
