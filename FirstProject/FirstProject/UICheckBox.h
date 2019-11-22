#pragma once
#include "UIElement.h"

namespace Engine
{
	class UICheckBox : public UIElement
	{
	public:
		UICheckBox(std::string aName);
		~UICheckBox();

		void Init() override;

	protected:
		virtual void Click();
		virtual void Hover();
		virtual void Exit();

	protected:
		bool myIsChecked = false;
		Vector3 myUncheckedColor;
		Vector3 myCheckedColor;
		Vector3 myHoverColor;
	};
}