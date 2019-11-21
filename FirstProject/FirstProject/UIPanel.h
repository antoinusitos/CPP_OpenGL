#pragma once
#include "UIElement.h"
namespace Engine
{
	class UIPanel : public UIElement
	{
	public:
		UIPanel(std::string aName);
		~UIPanel();

	protected:
		void Init() override;
	};
}