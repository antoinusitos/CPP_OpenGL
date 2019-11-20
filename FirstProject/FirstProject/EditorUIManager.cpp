#include "EditorUIManager.h"
#include "UIElement.h"

EditorUIManager::EditorUIManager() : UIManager()
{
	UIElement elem = UIElement();
	elem.CreateUI();
	elem.SetSize(50.0f, 50.0f);
	elem.SetPosition(glm::vec3(0.0f));
	elem.SetUIManager(this);
	myElements.push_back(elem);
}


EditorUIManager::~EditorUIManager()
{
}
