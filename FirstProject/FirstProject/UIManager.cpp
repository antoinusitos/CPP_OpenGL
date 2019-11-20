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

void UIManager::RenderManager()
{
	assert("ERROR::UIMANAGER::DrawManager:: shader is not set.", myShader != nullptr);
	
	if (myIsHidden)
	{
		return;
	}

	for (unsigned int i = 0; i < myElements.size(); i++)
	{
		myElements[i].Render(myShader);
	}

	Render(myShader);
}

void UIManager::UpdateMousePosition(glm::vec2 aNewPosition)
{
	myMousePosition = aNewPosition;
}

const glm::vec2 UIManager::GetMousePosition()
{
	return myMousePosition;
}

void UIManager::UpdateMouseStatus(bool aStatus)
{
	myMouseStatus = aStatus;
}

const bool UIManager::GetMouseStatus()
{
	return myMouseStatus;
}

void UIManager::SetShader(Shader* aShader)
{
	myShader = aShader;
}

void UIManager::Update(float aDeltaTime)
{

}

void UIManager::Render(Shader* aShader)
{

}
