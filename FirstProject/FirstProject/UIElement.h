#pragma once

#include "Data.h"
#include <glad/glad.h>
#include <functional>

typedef void(*callback_function)(void);

namespace Engine
{
	class UIManager;
	class Shader;

	class UIElement
	{
	public:
		UIElement(std::string aName = "New UI Element");
		~UIElement();

		void MouseHover();
		void MouseEnter();
		void MouseExit();

		void MouseClick();

		virtual void Update(const float aDeltaTime);
		virtual void Render(Shader* aShader);

		void SetUIManager(UIManager* aManager);

		void SetPosition(Vector2 aPosition);
		void SetRotation(Vector3 aRotation);
		void SetScale(Vector2 aScale);

		const Vector2 GetPosition();
		const Vector3 GetRotation();
		const Vector2 GetScale();

		void CreateUI();

	protected:
		std::string myName = "";

		bool myEntered = false;
		bool myClicked = false;
		std::function<void()> myMouseEnterFunction;
		std::function<void()> myMouseHoverFunction;
		std::function<void()> myMouseExitFunction;
		std::function<void()> myMouseClickFunction;
		UIManager* myUIManager;

		UITransform myTransform;
		float myAngle = 0;

		unsigned int myVAO = -1;

		Vector3 myColor;

	protected:
		virtual void Init();
	};
}