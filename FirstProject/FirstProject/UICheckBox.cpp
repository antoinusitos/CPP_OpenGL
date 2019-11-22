#include "UICheckBox.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "CameraManager.h"
#include "Camera.h"

namespace Engine
{
	UICheckBox::UICheckBox(std::string aName) : UIElement(aName)
	{
		myTransform.myPosition = Vector2(75.0f / 2.0f, 20.0f / 2.0f);
		myTransform.myScale = Vector2(30.0f, 30.0f);
		myUncheckedColor = Vector3(1.0f);
		myHoverColor = Vector3(0.5f);
		myCheckedColor = Vector3(1.0f);
	}

	UICheckBox::~UICheckBox()
	{
	}

	void UICheckBox::Init()
	{
		myMouseClickFunction = std::bind(&UICheckBox::Click, this);
		myMouseHoverFunction = std::bind(&UICheckBox::Hover, this);
		myMouseExitFunction = std::bind(&UICheckBox::Exit, this);

		myCheckedImageID = ResourceManager::GetInstance()->LoadTexture("CheckBox_On", myCheckedImage);
		myCheckOffImageID = ResourceManager::GetInstance()->LoadTexture("CheckBox_Off", myCheckOffImage);

		myShader = ResourceManager::GetInstance()->LoadShader("UITexture", "UITexture.vert", "UITexture.frag");

		myColor = myUncheckedColor;
	}

	void UICheckBox::Render(GLFWwindow* aWindow)
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
		if (myIsChecked)
		{
			glBindTexture(GL_TEXTURE_2D, myCheckedImageID);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, myCheckOffImageID);
		}

		glBindVertexArray(myVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void UICheckBox::Click()
	{
		myIsChecked = !myIsChecked;
		if (myIsChecked)
		{
			myColor = myCheckedColor;
		}
		else
		{
			myColor = myUncheckedColor;
		}
	}

	void UICheckBox::Hover()
	{
		myColor = myHoverColor;
	}

	void UICheckBox::Exit()
	{
		myColor = myUncheckedColor;
	}

}