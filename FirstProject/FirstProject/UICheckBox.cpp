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
		myImage = "CheckBox_Off.png";
	}

	UICheckBox::~UICheckBox()
	{
	}

	void UICheckBox::Init()
	{
		UIElement::Init();

		myMouseClickFunction = std::bind(&UICheckBox::Click, this);
		myMouseHoverFunction = std::bind(&UICheckBox::Hover, this);
		myMouseExitFunction = std::bind(&UICheckBox::Exit, this);

		myCheckedImageID = ResourceManager::GetInstance()->LoadTexture("CheckBox_On", myCheckedImage);

		myColor = myUncheckedColor;
	}

	void UICheckBox::Update(const float aDeltaTime)
	{
		UIElement::Update(aDeltaTime);

		if (myIsChecked)
		{
			myCurrentImageID = myCheckedImageID;
		}
		else
		{
			myCurrentImageID = myImageID;
		}
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