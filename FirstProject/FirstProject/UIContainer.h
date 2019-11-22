#pragma once
#include "UIPanel.h"
#include <vector>

struct GLFWwindow;

namespace Engine
{
	class UIElement;

	class UIContainer : public UIPanel
	{
	public:
		UIContainer(std::string aName);
		~UIContainer();

		void Render(GLFWwindow* aWindow) override;
		void Update(const float aDeltaTime) override;

		void AttachUIElement(UIElement* anElement);

		void SetVisibility(const bool aNewVisibility) override;

	protected:
		std::vector<UIElement*> myElements;

	};
}