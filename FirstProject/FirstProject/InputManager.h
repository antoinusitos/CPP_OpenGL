#pragma once
#include <map>
#include "Data.h"

struct GLFWwindow;

namespace Engine
{
	class UIManager;

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		static InputManager* GetInstance();

		void MouseUpdate(GLFWwindow* aWindow, double aXPos, double aYPos);

		void UpdateInput(GLFWwindow* aWindow);

		const Vector2 GetMousePosition();

		const bool GetKeyPressed(const int aKey);
		const bool GetKeyReleased(const int aKey);
		const bool GetKey(const int aKey);

	private:
		static InputManager* mySingleton;

		float myLastMousePosX = 400.0f;
		float myLastMousePosY = 300.0f;

		bool myFirstMouse = false;

		std::map<int, bool> myCurrentInput;
		std::map<int, bool> myLastInput;

		void UpdateMouseButtons(GLFWwindow* aWindow);
	};
}