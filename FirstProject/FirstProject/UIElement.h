#pragma once

#include "Data.h"
#include <glad/glad.h>

typedef void(*callback_function)(void);

namespace Engine
{
	class UIManager;
	class Shader;

	class UIElement
	{
	public:
		UIElement();
		~UIElement();

		void Hover();
		void Enter();
		void Exit();

		void MouseClick();

		void BindHoverFunction(void f());//callback_function aFunction);
		void BindEnterFunction(callback_function aFunction);
		void BindExitFunction(callback_function aFunction);
		void BindMouseClickFunction(void f());//callback_function aFunction);

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
		bool myEntered = false;
		bool myClicked = false;
		void* myHoverFunction = nullptr;
		void* myMouseClickFunction = nullptr;
		//callback_function myHoverFunction = nullptr;
		callback_function myEnterFunction = nullptr;
		callback_function myExitFunction = nullptr;
		//callback_function myMouseClickFunction = nullptr;
		UIManager* myUIManager;

		UITransform myTransform;
		float myAngle = 0;

		unsigned int myVAO = -1;

		Vector3 myColor;

	protected:
		virtual void Init();
	};
}