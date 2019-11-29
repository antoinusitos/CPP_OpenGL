#pragma once

#include "Data.h"
#include <glad/glad.h>
#include <functional>

typedef void(*callback_function)(void);

struct GLFWwindow;

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
		void MouseHold();
		void MouseRelease();

		virtual void Update(const float aDeltaTime);
		virtual void Render(GLFWwindow* aWindow);

		void SetUIManager(UIManager* aManager);

		void SetPosition(Vector2 aPosition);
		void SetRotation(Vector3 aRotation);
		void SetScale(Vector2 aScale);

		const Vector2 GetPosition();
		const Vector3 GetRotation();
		const Vector2 GetScale();

		void CreateUI();

		virtual void SetVisibility(const bool aNewVisibility);

		void AlignCollisionWithTransform();

		virtual void Init();

		const bool GetVisibility();

		void SetColor(const Vector3 aColor);

	public:
		bool myDebug = false;

		bool myForceUpdate = false;

		std::function<void(UIElement* anElement)> myVisibilityCallback;

		std::function<void()> myMouseEnterFunction;
		std::function<void()> myMouseHoverFunction;
		std::function<void()> myMouseExitFunction;
		std::function<void()> myMouseClickFunction;
		std::function<void()> myMouseHoldFunction;
		std::function<void()> myMouseReleaseFunction;

	protected:
		std::string myName = "";

		bool myEntered = false;
		bool myClicked = false;
		
		UIManager* myUIManager;

		UITransform myTransform;
        UITransform myCollision;

		float myAngle = 0;

		unsigned int myVAO = -1;

		Vector3 myColor;

		bool myVisibility = true;

		Shader* myShader;
		Shader* myShaderTexture;

		char* myImage;

		unsigned int myImageID;
		unsigned int myCurrentImageID;
	};
}
