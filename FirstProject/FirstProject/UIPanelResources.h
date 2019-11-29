#pragma once
#include "UIPanel.h"
#include <string>
#include <vector>
#include "UIText.h"

namespace Engine
{
	class UIPanelResources : public UIPanel
	{
	public:
		UIPanelResources(std::string aName);
		~UIPanelResources();

		void Render(GLFWwindow* aWindow) override;

		void Update(const float aDeltaTime) override;
	};
}