#include "EditorUIManager.h"
#include "UIElement.h"
#include "UIButton.h"
#include <iostream>

namespace Editor
{
	EditorUIManager::EditorUIManager() : Engine::UIManager()
	{
		//Engine::UIElement* elem = new Engine::UIElement();
		Engine::UIButton* elem = new Engine::UIButton();
		elem->CreateUI();
		elem->SetUIManager(this);
		myElements.push_back(elem);
	}

	EditorUIManager::~EditorUIManager()
	{
	}
}