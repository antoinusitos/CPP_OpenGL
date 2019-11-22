#include "UIManager.h"
#include "UIElement.h"
#include <iostream>
#include "Shader.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	UIManager::UIManager()
	{
	}


	UIManager::~UIManager()
	{
		for (unsigned int i = 0; i < myElements.size(); i++)
		{
			delete myElements[i];
		}
	}

	void UIManager::UpdateManager(float aDeltaTime)
	{
		if (!myIsActive)
		{
			return;
		}

		for (unsigned int i = 0; i < myElements.size(); i++)
		{
			myElements[i]->Update(aDeltaTime);
		}

		Update(aDeltaTime);
	}

	void UIManager::RenderManager(GLFWwindow* aWindow)
	{
		assert("ERROR::UIMANAGER::DrawManager:: shader is not set.", myShader != nullptr);

		if (myIsHidden)
		{
			return;
		}
		
		for (unsigned int i = 0; i < myElements.size(); i++)
		{
			myElements[i]->Render(aWindow);
		}

		Render(aWindow);
	}

	void UIManager::UpdateMousePosition(glm::vec2 aNewPosition)
	{
		myMousePosition = Vector2(aNewPosition.x, aNewPosition.y);
	}

	const Vector2 UIManager::GetMousePosition()
	{
		//std::cout << "mousePos x:" << myMousePosition.myX << " mouse y:" << myMousePosition.myY << std::endl;
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

	void UIManager::InitUIManager()
	{

	}

	void UIManager::SetWindow(GLFWwindow* aWindow)
	{
		myWindow = aWindow;
	}

	void UIManager::Quit()
	{
		glfwSetWindowShouldClose(myWindow, true);
	}

	void UIManager::Update(float aDeltaTime)
	{

	}

	void UIManager::Render(GLFWwindow* aWindow)
	{

	}
}