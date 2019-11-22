#pragma once

#include <vector>
#include <glm/glm.hpp> 
#include "Data.h"

struct GLFWwindow;

namespace Engine
{
	class Shader;
	class UIElement;

	class UIManager
	{
	public:
		UIManager();
		~UIManager();

		void UpdateManager(float aDeltaTime);
		void RenderManager(GLFWwindow* aWindow);

		void UpdateMousePosition(glm::vec2 aNewPosition);
		const Vector2 GetMousePosition();

		void UpdateMouseStatus(bool aStatus);
		const bool GetMouseStatus();

		virtual void InitUIManager();

		void SetWindow(GLFWwindow* aWindow);

		void Quit();

	protected:
		virtual void Update(float aDeltaTime);
		virtual void Render(GLFWwindow* aWindow);

	protected:
		std::vector<UIElement*> myElements;

		bool myIsActive = true;
		bool myIsHidden = false;

		Vector2 myMousePosition = Vector2(0.0f);
		bool myMouseStatus = false;

		GLFWwindow* myWindow;
	};
}