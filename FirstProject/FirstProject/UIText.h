#pragma once
#include "UIElement.h"
#include <functional>

namespace Engine
{
	class UIText : public UIElement
	{
	public:
		UIText(std::string aName);
		~UIText();

		void SetText(const std::string aText);
		void SetColor(const Vector3 aColor);

		void Render(GLFWwindow* aWindow) override;

		std::function<void(UIText* aText)> myCallBackText;

	private:
		std::string myText = "";
		Vector3 myColor = Vector3(0.0f);
	};
}