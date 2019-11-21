#pragma once
#include "UIPanel.h"
#include <vector>

namespace Engine
{
	class UIElement;

	class UIContainer : public UIPanel
	{
	public:
		UIContainer(std::string aName);
		~UIContainer();

		void Render(Shader* aShader) override;
		void Update(const float aDeltaTime) override;

		void AttachUIElement(UIElement* anElement);

		void SetVisibility(const bool aNewVisibility) override;

	protected:
		std::vector<UIElement*> myElements;

	};
}