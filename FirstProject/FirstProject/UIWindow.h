#pragma once
#include "UIContainer.h"

namespace Engine
{
	class UIButton;

	class UIWindow : public UIContainer
	{
	public:
		UIWindow(std::string aName);
		~UIWindow();

		void Update(const float aDeltaTime) override;

		void Init() override;

		void Click();
		void Release();

	private:
		UIButton* myCloseButton;

		bool myFollowMouse = false;
		Vector2 myOffset;
	};
}