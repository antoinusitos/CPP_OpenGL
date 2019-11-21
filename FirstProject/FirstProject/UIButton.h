#pragma once
#include "UIElement.h"
#include <vector>

namespace Engine
{
	class UIButton : public UIElement
	{
	public:
		UIButton(std::string aName);
		~UIButton();

		void AddUIAction(UIAction anAction);

	protected:
		void Init() override;
		virtual void Click();
		virtual void Release();
		virtual void Enter();
		virtual void Exit();

		Vector3 myBaseColor;
		Vector3 myHoverColor;

		std::vector<UIAction> myUIActions;
	};
}

