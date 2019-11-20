#include "UIElement.h"
#include <assert.h>

#include <glad/glad.h>
#include <glm/glm.hpp> 

#include "UIManager.h"
#include "Shader.h"

#include <iostream>

UIElement::UIElement()
{
	myTransform.myPosition = glm::vec3(0.0f);
	myTransform.myRotation = glm::vec3(0.0f, 1.0f, 0.0f);
	myTransform.myScale = glm::vec3(1.0f);
}

UIElement::~UIElement()
{
}

void UIElement::Hover()
{
	if (myHoverFunction != nullptr)
	{
		myHoverFunction();
	}
}

void UIElement::Enter()
{
	if (myEnterFunction != nullptr)
	{
		myEnterFunction();
	}
}

void UIElement::Exit()
{
	if (myExitFunction != nullptr)
	{
		myExitFunction();
	}
}

void UIElement::BindHoverFunction(callback_function aFunction)
{
	myHoverFunction = aFunction;
}

void UIElement::BindEnterFunction(callback_function aFunction)
{
	myEnterFunction = aFunction;
}

void UIElement::BindExitFunction(callback_function aFunction)
{
	myExitFunction = aFunction;
}

void UIElement::Update(const float aDeltaTime)
{
	assert("ERROR::UIELEMENT::UPDATE:: UI manager is not set.", myUIManager != nullptr);

	glm::vec2 mousePos = myUIManager->GetMousePosition();

	if (mousePos.x <= (myTransform.myPosition.x + (myWidth / 2.0f)) && mousePos.x >= (myTransform.myPosition.x - (myWidth / 2.0f)) &&
		mousePos.y <= (myTransform.myPosition.y + (myHeight / 2.0f)) && mousePos.y >= (myTransform.myPosition.y - (myHeight / 2.0f)))
	{
		if (myEntered)
		{
			Hover();
			std::cout << "HOVER" << std::endl;
		}
		else
		{
			myEntered = true;
			Enter();
			std::cout << "ENTER" << std::endl;
		}
	}
	else if(myEntered)
	{
		myEntered = false;
		Exit();
		std::cout << "EXIT" << std::endl;
	}
}

void UIElement::Draw(Shader aShader)
{
	aShader.Use();
	glBindVertexArray(myVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void UIElement::SetUIManager(UIManager* aManager)
{
	myUIManager = aManager;
}

void UIElement::SetSize(const float aWidth, const float aHeight)
{
	myWidth = aWidth;
	myHeight = aHeight;
}


void UIElement::SetPosition(glm::vec3 aPosition)
{
	myTransform.myPosition = aPosition;
}

void UIElement::SetRotation(glm::vec3 aRotation)
{
	myTransform.myRotation = aRotation;
}

void UIElement::SetScale(glm::vec3 aScale)
{
	myTransform.myScale = aScale;
}

const glm::vec3 UIElement::GetPosition()
{
	return myTransform.myPosition;
}

const glm::vec3 UIElement::GetRotation()
{
	return myTransform.myRotation;
}

const glm::vec3 UIElement::GetScale()
{
	return myTransform.myScale;
}

void UIElement::CreateUI()
{
	/*glGenVertexArrays(1, &myVAO);
	glGenBuffers(1, &myVBO);
	glGenBuffers(1, &myEBO);

	glBindVertexArray(myVAO);

	glBindBuffer(GL_ARRAY_BUFFER, myVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(myVertices), myVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(myIndices), myIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// free resources
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);*/

	//unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &myVAO);
	glGenBuffers(1, &myVBO);
	glGenBuffers(1, &myEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(myVAO);

	glBindBuffer(GL_ARRAY_BUFFER, myVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(myVertices), myVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(myIndices), myIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	//glBindVertexArray(0);
}
