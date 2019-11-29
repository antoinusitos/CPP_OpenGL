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

		void SetMySpacing(const float aValue);
		void SetSizeToContent(const bool aValue);

	protected:
		float mySpacing = 0.0f;
		bool mySizeToContent = false;
	};
}
