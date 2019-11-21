#pragma once
#include "UIManager.h"

namespace Editor
{
	class EditorUIManager : public Engine::UIManager
	{
	public:
		EditorUIManager();
		~EditorUIManager();

		void InitUIManager() override;
	};
}