#pragma once

#include "Data.h"
#include <glad/glad.h>

typedef void(*callback_function)(void);

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

	void BindHoverFunction(callback_function aFunction);
	void BindEnterFunction(callback_function aFunction);
	void BindExitFunction(callback_function aFunction);
	void BindMouseClickFunction(callback_function aFunction);

	virtual void Update(const float aDeltaTime);
	virtual void Render(Shader* aShader);

	void SetUIManager(UIManager* aManager);

	void SetPosition(glm::vec2 aPosition);
	void SetRotation(glm::vec3 aRotation);
	void SetScale(glm::vec2 aScale);

	const glm::vec2 GetPosition();
	const glm::vec3 GetRotation();
	const glm::vec2 GetScale();

	void CreateUI();

protected:
	bool myEntered = false;
	callback_function myHoverFunction = nullptr;
	callback_function myEnterFunction = nullptr;
	callback_function myExitFunction = nullptr;
	callback_function myMouseClickFunction = nullptr;
	UIManager* myUIManager;

	UITransform myTransform;
	float myAngle = 0;

	unsigned int myVAO = -1;
};

