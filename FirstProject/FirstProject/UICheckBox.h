#pragma once
#include "UIElement.h"

struct GLFWwindow;

namespace Engine
{
	class Shader;

	class UICheckBox : public UIElement
	{
	public:
		UICheckBox(std::string aName);
		~UICheckBox();

		void Init() override;

		void Update(const float aDeltaTime) override;

	protected:
		virtual void Click();
		virtual void Hover();
		virtual void Exit();

	protected:
		bool myIsChecked = false;
		Vector3 myUncheckedColor;
		Vector3 myCheckedColor;
		Vector3 myHoverColor;

		char* myCheckedImage = "CheckBox_On.png";

		unsigned int myCheckedImageID;
	};
}