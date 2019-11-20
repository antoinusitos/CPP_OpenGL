#pragma once

#include "Data.h"

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

	void BindHoverFunction(callback_function aFunction);
	void BindEnterFunction(callback_function aFunction);
	void BindExitFunction(callback_function aFunction);

	virtual void Update(const float aDeltaTime);
	virtual void Draw(Shader aShader);

	void SetUIManager(UIManager* aManager);

	void SetSize(const float aWidth, const float aHeight);

	void SetPosition(glm::vec3 aPosition);
	void SetRotation(glm::vec3 aRotation);
	void SetScale(glm::vec3 aScale);

	const glm::vec3 GetPosition();
	const glm::vec3 GetRotation();
	const glm::vec3 GetScale();

	void CreateUI();

protected:
	bool myEntered = false;
	callback_function myHoverFunction = nullptr;
	callback_function myEnterFunction = nullptr;
	callback_function myExitFunction = nullptr;
	UIManager* myUIManager;

	Transform myTransform;
	float myHeight = 0;
	float myWidth = 0;

	float myVertices[18] = {
		// first triangle
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f,  0.5f, 0.0f,  // top left 
		// second triangle
		 0.5f, -0.5f, 0.0f,  // bottom right
		 -0.5f, -0.5f, 0.0f,  // bottom left
		 -0.5f,  0.5f, 0.0f   // top left
	};

	unsigned int myIndices[6] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int myVAO;
	unsigned int myVBO;
	unsigned int myEBO;
};

