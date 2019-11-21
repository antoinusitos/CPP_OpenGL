#include "UIElement.h"
#include <assert.h>

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>

#include "UIManager.h"
#include "Shader.h"

#include <iostream>

namespace Engine
{
	UIElement::UIElement()
	{
		myTransform.myPosition = Vector2(400.0f, 300.0f);
		myTransform.myRotation = Vector3(0.0f, 1.0f, 0.0f);
		myTransform.myScale = Vector2(100.0f, 100.0f);
		myColor = Vector3(0.0f, 1.0f, 0.0f);
	}

	UIElement::~UIElement()
	{
		glDeleteVertexArrays(1, &myVAO);
	}

	void UIElement::Hover()
	{
		if (myHoverFunction != nullptr)
		{
			myHoverFunction;
		}
		//std::cout << "HOVER" << std::endl;
	}

	void UIElement::Enter()
	{
		if (myEnterFunction != nullptr)
		{
			myEnterFunction();
		}
		//std::cout << "ENTER" << std::endl;
	}

	void UIElement::Exit()
	{
		if (myExitFunction != nullptr)
		{
			myExitFunction();
		}
		//std::cout << "EXIT" << std::endl;
	}

	void UIElement::MouseClick()
	{
		if (myMouseClickFunction != nullptr)
		{
			myMouseClickFunction;
		}
		//std::cout << "Mouse click" << std::endl;
	}

	void UIElement::BindHoverFunction(void f())//callback_function aFunction)
	{
		myHoverFunction = &f;
	}

	void UIElement::BindEnterFunction(callback_function aFunction)
	{
		myEnterFunction = aFunction;
	}

	void UIElement::BindExitFunction(callback_function aFunction)
	{
		myExitFunction = aFunction;
	}

	void UIElement::BindMouseClickFunction(void f())//callback_function aFunction)
	{
		myMouseClickFunction = f;
	}

	void UIElement::Update(const float aDeltaTime)
	{
		assert("ERROR::UIELEMENT::UPDATE:: UI manager is not set.", myUIManager != nullptr);

		Vector2 mousePos = myUIManager->GetMousePosition();

		if (myUIManager->GetMouseStatus())
		{
			if (myEntered && !myClicked)
			{
				myClicked = true;
				MouseClick();
			}
		}
		else if (myClicked)
		{
			myClicked = false;
		}

		if (mousePos.myX <= (myTransform.myPosition.myX + (myTransform.myScale.myX / 2.0f)) && mousePos.myX >= (myTransform.myPosition.myX - (myTransform.myScale.myX / 2.0f)) &&
			mousePos.myY <= (myTransform.myPosition.myY + (myTransform.myScale.myY / 2.0f)) && mousePos.myY >= (myTransform.myPosition.myY - (myTransform.myScale.myY / 2.0f)))
		{
			if (myEntered)
			{
				Hover();
			}
			else
			{
				myEntered = true;
				Enter();
			}
		}
		else if (myEntered)
		{
			myEntered = false;
			Exit();
		}
	}

	void UIElement::Render(Shader* aShader)
	{
		aShader->Use();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(myTransform.myPosition.myX + -0.5f * myTransform.myScale.myX, myTransform.myPosition.myY + -0.5f * myTransform.myScale.myY, 0.0f));

		model = glm::translate(model, glm::vec3(0.5f * myTransform.myScale.myX, 0.5f * myTransform.myScale.myY, 0.0f));
		model = glm::rotate(model, myAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * myTransform.myScale.myX, -0.5f * myTransform.myScale.myY, 0.0f));

		model = glm::scale(model, glm::vec3(myTransform.myScale.myX, myTransform.myScale.myY, 1.0f));

		aShader->SetMat4("myModel", model);
		aShader->SetVec3("mySpriteColor", glm::vec3(myColor.myX, myColor.myY, myColor.myZ));

		//glActiveTexture(GL_TEXTURE0);
		//texture.Bind();

		glBindVertexArray(myVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void UIElement::SetUIManager(UIManager* aManager)
	{
		myUIManager = aManager;
	}

	void UIElement::SetPosition(Vector2 aPosition)
	{
		myTransform.myPosition = aPosition;
	}

	void UIElement::SetRotation(Vector3 aRotation)
	{
		myTransform.myRotation = aRotation;
	}

	void UIElement::SetScale(Vector2 aScale)
	{
		myTransform.myScale = aScale;
	}

	const Vector2 UIElement::GetPosition()
	{
		return myTransform.myPosition;
	}

	const Vector3 UIElement::GetRotation()
	{
		return myTransform.myRotation;
	}

	const Vector2 UIElement::GetScale()
	{
		return myTransform.myScale;
	}

	void UIElement::CreateUI()
	{
		// Configure VAO/VBO
		GLuint VBO;
		GLfloat vertices[] = {
			// Pos      // Tex
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};

		glGenVertexArrays(1, &myVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(myVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		Init();
	}

	void UIElement::Init()
	{

	}

}