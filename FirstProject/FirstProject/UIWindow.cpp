#include "UIWindow.h"
#include "UIButton.h"
#include "UIManager.h"

#include <iostream>

namespace Engine
{
	UIWindow::UIWindow(std::string aName) : UIContainer(aName)
	{
		myColor = Vector3(0.2f);
	}

	UIWindow::~UIWindow()
	{
	}

	void UIWindow::Update(const float aDeltaTime)
	{
		if (myFollowMouse)
		{
			Vector2 mousePos = myUIManager->GetMousePosition();
			myTransform.myPosition = mousePos - myOffset;
			UIElement::Update(aDeltaTime);
		}
		else
		{
			UIContainer::Update(aDeltaTime);
		}

		myCollision.myPosition = Vector2(myTransform.myPosition.myX - myCloseButton->GetScale().myX, myTransform.myPosition.myY - myTransform.myScale.myY / 2.0f + myCollision.myScale.myY / 2.0f);
		myCloseButton->SetPosition(Vector2(myTransform.myPosition.myX + myTransform.myScale.myX / 2.0f - myCloseButton->GetScale().myX / 2.0f, myTransform.myPosition.myY - myTransform.myScale.myY / 2.0f + myCloseButton->GetScale().myY / 2.0f));
		myCloseButton->AlignCollisionWithTransform();
	}

	void UIWindow::Init()
	{
		UIContainer::Init();

		myCloseButton = new Engine::UIButton(std::string("Close Button"));
		myCloseButton->SetScale(Vector2(30.0f));

		myCollision.myScale = Vector2(myTransform.myScale.myX - myCloseButton->GetScale().myX, myCloseButton->GetScale().myY);
		myCollision.myPosition = Vector2(myTransform.myPosition.myX - myCloseButton->GetScale().myX, myTransform.myPosition.myY - myTransform.myScale.myY / 2.0f + myCollision.myScale.myY / 2.0f);

		myMouseClickFunction = std::bind(&UIWindow::Click, this);
		myMouseReleaseFunction = std::bind(&UIWindow::Release, this);

		myCloseButton->SetPosition(Vector2(myTransform.myPosition.myX + myTransform.myScale.myX / 2.0f - myCloseButton->GetScale().myX / 2.0f, myTransform.myPosition.myY - myTransform.myScale.myY / 2.0f + myCloseButton->GetScale().myY / 2.0f));
		myCloseButton->CreateUI();
		myCloseButton->SetUIManager(myUIManager);
		myCloseButton->Init();
		myCloseButton->AddUIAction(Engine::UIAction(Engine::VISIBILITY, this, false));
		myCloseButton->AlignCollisionWithTransform();
		myElements.push_back(myCloseButton);
	}

	void UIWindow::Click()
	{
		Vector2 mousePos = myUIManager->GetMousePosition();
		myOffset = mousePos - myTransform.myPosition;
		myFollowMouse = true;
	}

	void UIWindow::Release()
	{
		myFollowMouse = false;
	}
}