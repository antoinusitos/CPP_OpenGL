#pragma once
#include "UIWindow.h"

namespace Engine
{
	class UIWindowLog : public UIWindow
	{
	public:
		UIWindowLog(std::string aName);
		~UIWindowLog();

		void Render(GLFWwindow* aWindow) override;

	private:
		const unsigned int myMaxLogToShow = 15;
	};
}