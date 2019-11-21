#include "EditorUIManager.h"
#include "UIElement.h"
#include <iostream>

namespace Editor
{
	EditorUIManager::EditorUIManager() : Engine::UIManager()
	{
		Engine::UIElement* elem = new Engine::UIElement();
		elem->CreateUI();
		elem->SetUIManager(this);
		myElements.push_back(elem);
	}

	EditorUIManager::~EditorUIManager()
	{
	}
}