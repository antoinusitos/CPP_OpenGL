#pragma once
#include "UIElement.h"

namespace Engine
{
	class UIButton : public UIElement
	{
	public:
		UIButton();
		~UIButton();

	protected:
		void Init() override;
	};
}

