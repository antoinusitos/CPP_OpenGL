#include "EditorUIManager.h"
#include "UIElement.h"
#include <iostream>

EditorUIManager::EditorUIManager() : UIManager()
{
	UIElement* elem = new UIElement();
	elem->CreateUI();
	elem->SetUIManager(this);
	myElements.push_back(elem);
}


EditorUIManager::~EditorUIManager()
{
}
