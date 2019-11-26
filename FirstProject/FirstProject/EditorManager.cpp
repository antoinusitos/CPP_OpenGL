#include "EditorManager.h"
#include "Model.h"

namespace Engine
{
	EditorManager* EditorManager::mySingleton = nullptr;

	EditorManager::EditorManager()
	{
	}

	EditorManager::~EditorManager()
	{
	}

	EditorManager* EditorManager::GetInstance()
	{
		if (mySingleton == nullptr)
		{
			mySingleton = new EditorManager();
		}

		return mySingleton;
	}

	void EditorManager::MoveObject(const float aDeltaTime)
	{
		/*Vector3 pos = myObject->GetPosition();
		pos.myX += aDeltaTime;
		myObject->SetPosition(myObject->GetPosition())->myPosition.r += aDeltaTime;*/
	}

}