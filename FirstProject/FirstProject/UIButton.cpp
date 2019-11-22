#include "UIButton.h"
#include <iostream>
#include <string>
#include "UIManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Shader.h"

namespace Engine
{
	UIButton::UIButton(std::string aName) : UIElement(aName)
	{
		myTransform.myPosition = Vector2(75.0f / 2.0f, 20.0f / 2.0f);
		myTransform.myScale = Vector2(75.0f, 20.0f);
	}

	UIButton::~UIButton()
	{
	}

	void UIButton::AddUIAction(UIAction anAction)
	{
		myUIActions.push_back(anAction);
	}

	void UIButton::Init()
	{
		UIElement::Init();

		myMouseClickFunction = std::bind(&UIButton::Click, this);
		myMouseReleaseFunction = std::bind(&UIButton::Release, this);
		myMouseHoverFunction = std::bind(&UIButton::Hover, this);
		myMouseExitFunction = std::bind(&UIButton::Exit, this);

		myImageID = ResourceManager::GetInstance()->LoadTexture("CheckBox_Off", myImage);
		myShader = ResourceManager::GetInstance()->LoadShader("UITexture", "UITexture.vert", "UITexture.frag");

		myBaseColor = Vector3(1.0f);
		myHoverColor = Vector3(0.5f);
		myColor = myBaseColor;
	}

	void UIButton::Render(GLFWwindow* aWindow)
	{
		if (!myVisibility)
			return;

		myShader->Use();

		CameraManager::GetInstance()->GetCamera()->Render(myShader, aWindow, true);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(myTransform.myPosition.myX + -0.5f * myTransform.myScale.myX, myTransform.myPosition.myY + -0.5f * myTransform.myScale.myY, 0.0f));

		model = glm::translate(model, glm::vec3(0.5f * myTransform.myScale.myX, 0.5f * myTransform.myScale.myY, 0.0f));
		model = glm::rotate(model, myAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * myTransform.myScale.myX, -0.5f * myTransform.myScale.myY, 0.0f));

		model = glm::scale(model, glm::vec3(myTransform.myScale.myX, myTransform.myScale.myY, 1.0f));

		myShader->SetMat4("myModel", model);
		myShader->SetVec3("mySpriteColor", glm::vec3(myColor.myX, myColor.myY, myColor.myZ));
		myShader->SetInt("myImage", 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, myImageID);

		glBindVertexArray(myVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void UIButton::Click()
	{
		LogManager::GetInstance()->AddLog("Clicked on " + myName);
		myColor = Vector3(0.0f, 1.0f, 0.0f);

		for (unsigned int i = 0; i < myUIActions.size(); i++)
		{
			switch (myUIActions[i].myActionType)
			{
			case VISIBILITY:
			{
				myUIActions[i].myElement->SetVisibility(myUIActions[i].myValue2);
				break;
			}
			case TOGGLEVISIBILITY:
			{
				myUIActions[i].myElement->SetVisibility(!myUIActions[i].myElement->GetVisibility());
				break;
			}
			case QUIT:
			{
				myUIManager->Quit();
				break;
			}
			case POSITION:
			{
				myUIActions[i].myElement->SetPosition(myUIActions[i].myValue3);
				break;
			}
			default:
				break;
			}
		}
	}

	void UIButton::Release()
	{
		//LogManager::GetInstance()->AddLog("Released on " + myName);
		myColor = myHoverColor;
	}

	void UIButton::Hover()
	{
		//LogManager::GetInstance()->AddLog("Mouse Enter on " + myName);
		myColor = myHoverColor;
	}

	void UIButton::Exit()
	{
		//LogManager::GetInstance()->AddLog("Mouse Exit on " + myName);
		myColor = myBaseColor;
	}

}