#pragma once
#include "UIElement.h"

namespace Engine
{
	class UIButton : public UIElement
	{
	public:
		UIButton(std::string aName);
		~UIButton();

	protected:
		void Init() override;
		virtual void Click();
		virtual void Release();
		virtual void Enter();
		virtual void Exit();

		Vector3 myBaseColor;
		Vector3 myHoverColor;
	};
}

