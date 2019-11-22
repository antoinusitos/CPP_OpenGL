#include "UIMenuPanel.h"
#include "LogManager.h"

namespace Engine
{
	UIMenuPanel::UIMenuPanel(std::string aName) : UIContainerVertical(aName)
	{
	}

	UIMenuPanel::~UIMenuPanel()
	{
	}

	void UIMenuPanel::Init()
	{
		UIContainerVertical::Init();
		myMouseExitFunction = std::bind(&UIMenuPanel::HidePanel, this);
		myForceUpdate = true;
	}

	void UIMenuPanel::HidePanel()
	{
		LogManager::GetInstance()->AddLog("Hide menu panel");
		SetVisibility(false);
	}
}