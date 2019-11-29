#include "InputManager.h"
#include <GLFW/glfw3.h>
#include "CameraManager.h"
#include "Camera.h"
#include "UIManager.h"
#include "TimeManager.h"
#include "EditorManager.h"

namespace Engine
{
	InputManager* InputManager::mySingleton = nullptr;

	InputManager::InputManager()
	{
		// see glfw3.h to learn more
		for (int i = 0; i <= 7; i++)
		{
			myCurrentInput.insert(std::pair<int, bool>(i, false));
		}
	 	for (int i = 32; i <= 93; i++)
		{
			myCurrentInput.insert(std::pair<int, bool>(i, false));
		}
		myCurrentInput.insert(std::pair<int, bool>(96, false));
		myCurrentInput.insert(std::pair<int, bool>(161, false));
		myCurrentInput.insert(std::pair<int, bool>(162, false));
		for (int i = 256; i <= 269; i++)
		{
			myCurrentInput.insert(std::pair<int, bool>(i, false));
		}
		for (int i = 280; i <= 314; i++)
		{
			myCurrentInput.insert(std::pair<int, bool>(i, false));
		}
		for (int i = 320; i <= 348; i++)
		{
			myCurrentInput.insert(std::pair<int, bool>(i, false));
		}

		myLastInput = myCurrentInput;
	}

	InputManager::~InputManager()
	{
	}

	InputManager* InputManager::GetInstance()
	{
		if (mySingleton == nullptr)
		{
			mySingleton = new InputManager();
		}

		return mySingleton;
	}

	void InputManager::MouseUpdate(GLFWwindow* aWindow, double aXPos, double aYPos)
	{
		if (myFirstMouse)
		{
			myFirstMouse = false;
			myLastMousePosX = aXPos;
			myLastMousePosY = aYPos;
		}

		float xOffset = aXPos - myLastMousePosX;
		float yOffset = aYPos - myLastMousePosY;

		myLastMousePosX = aXPos;
		myLastMousePosY = aYPos;

		CameraManager::GetInstance()->GetCamera()->ProcessMouseMovement(xOffset, yOffset);
	}

	void InputManager::UpdateInput(GLFWwindow* aWindow)
	{
		myLastInput = myCurrentInput;

		for (std::map<int, bool>::iterator itr = myCurrentInput.begin(); itr != myCurrentInput.end(); ++itr) 
		{
			if (glfwGetKey(aWindow, itr->first) == GLFW_PRESS)
			{
				itr->second = true;
			}
			else
			{
				itr->second = false;
			}
		}

		UpdateMouseButtons(aWindow);
	}

	void InputManager::UpdateMouseButtons(GLFWwindow* aWindow)
	{
		for (int i = 0; i <= 7; i ++)
		{
			if (glfwGetMouseButton(aWindow, i) == GLFW_PRESS)
			{
				myCurrentInput[i] = true;
			}
			else
			{
				myCurrentInput[i] = false;
			}
		}
	}

	const Vector2 InputManager::GetMousePosition()
	{
		return Vector2(myLastMousePosX, myLastMousePosY);
	}

	const bool InputManager::GetKeyPressed(const int aKey)
	{
		if (myCurrentInput[aKey] == true && myLastInput[aKey] == false)
		{
			return true;
		}
		return false;
	}

	const bool InputManager::GetKeyReleased(const int aKey)
	{
		if (myCurrentInput[aKey] == false && myLastInput[aKey] == true)
		{
			return true;
		}
		return false;
	}

	const bool InputManager::GetKey(const int aKey)
	{
		if (myCurrentInput[aKey] == true && myLastInput[aKey] == true)
		{
			return true;
		}
		return false;
	}
}