#include "UIWindowLog.h"
#include "LogManager.h"
#include "UIText.h"

namespace Engine
{
	UIWindowLog::UIWindowLog(std::string aName) : UIWindow(aName)
	{
	}

	UIWindowLog::~UIWindowLog()
	{
	}

	void UIWindowLog::Render(GLFWwindow* aWindow)
	{
		if (!myVisibility)
		{
			return;
		}

		UIWindow::Render(aWindow);

		std::vector<UIText*> logs = LogManager::GetInstance()->GetLogsText();

		int startPos = 0;
		if (logs.size() > myMaxLogToShow)
		{
			startPos = logs.size() - myMaxLogToShow;
		}
		for (int i = startPos; i < logs.size(); i++)
		{
			Vector2 pos = myTransform.myPosition;
			pos.myX -= myTransform.myScale.myX / 2.0f;
			pos.myY -= myTransform.myScale.myY / 2.0f;

			logs[i]->SetPosition(Vector2(pos.myX, pos.myY + (i - startPos) * 20.0f));
			logs[i]->SetUIManager(myUIManager);
			logs[i]->Render(aWindow);
		}
	}
}