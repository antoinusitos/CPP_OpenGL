#include "UIManager.h"
#include "UIElement.h"
#include <iostream>
#include "Shader.h"

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}

void UIManager::UpdateManager(float aDeltaTime)
{
	if (!myIsActive)
	{
		return;
	}

	for (unsigned int i = 0; i < myElements.size(); i++)
	{
		myElements[i].Update(aDeltaTime);
	}

	Update(aDeltaTime);
}

void UIManager::DrawManager()
{
	assert("ERROR::UIMANAGER::DrawManager:: shader is not set.", myShader != nullptr);
	
	if (myIsHidden)
	{
		return;
	}

	for (unsigned int i = 0; i < myElements.size(); i++)
	{
		myElements[i].Draw(*myShader);
	}

	Draw(*myShader);
}

void UIManager::UpdateMousePosition(glm::vec2 aNewPosition)
{
	myMousePosition = aNewPosition;
}

const glm::vec2 UIManager::GetMousePosition()
{
	return myMousePosition;
}

void UIManager::SetShader(Shader* aShader)
{
	myShader = aShader;
}

void UIManager::Update(float aDeltaTime)
{

}

void UIManager::Draw(Shader aShader)
{

}
