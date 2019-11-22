#pragma once

#include "UIContainerVertical.h"

namespace Engine
{
	class UIMenuPanel : public UIContainerVertical
	{
	public:
		UIMenuPanel(std::string aName);
		~UIMenuPanel();

		void Init() override;

	protected:
		void HidePanel();
	};
}