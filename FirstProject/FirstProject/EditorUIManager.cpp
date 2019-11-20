#include "EditorUIManager.h"
#include "UIElement.h"
#include <iostream>

EditorUIManager::EditorUIManager() : UIManager()
{
	UIElement elem = UIElement();
	elem.CreateUI();
	elem.SetUIManager(this);
	myElements.push_back(elem);
	std::cout << "LOL" << std::endl;
}


EditorUIManager::~EditorUIManager()
{
}
