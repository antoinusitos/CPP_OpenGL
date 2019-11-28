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

		std::vector<std::string> logs = LogManager::GetInstance()->GetLogs();

		for (int i = 0; i < logs.size(); i++)
		{
			Vector2 pos = myTransform.myPosition;
			pos.myX -= myTransform.myScale.myX / 2.0f;
			pos.myY -= myTransform.myScale.myY / 2.0f;

			UIText aLog = UIText(std::string("ALog"));
			aLog.SetText(logs[i]);
			aLog.SetPosition(Vector2(pos.myX, pos.myY + i * 20.0f));
			aLog.SetColor(Vector3(1.0f, 1.0f, 1.0f));
			aLog.CreateUI();
			aLog.Init();
			aLog.SetUIManager(myUIManager);
			aLog.Render(aWindow);
		}

		UIWindow::Render(aWindow);
	}
}