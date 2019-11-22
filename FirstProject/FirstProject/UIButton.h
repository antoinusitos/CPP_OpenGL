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

		void Init() override;

		void Render(GLFWwindow* aWindow) override;

	protected:
		virtual void Click();
		virtual void Release();
		virtual void Hover();
		virtual void Exit();

		Vector3 myBaseColor;
		Vector3 myHoverColor;

		std::vector<UIAction> myUIActions;

		char* myImage = "CheckBox_Off.png";

		unsigned int myImageID;
	};
}

