#include "TimeManager.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	TimeManager* TimeManager::mySingleton = nullptr;

	TimeManager::TimeManager()
	{
	}

	TimeManager::~TimeManager()
	{
	}

	TimeManager* TimeManager::GetInstance()
	{
		if (mySingleton == nullptr)
		{
			mySingleton = new TimeManager();
		}

		return mySingleton;
	}

	const float TimeManager::GetDeltaTime()
	{
		return myDeltaTime;
	}

	void TimeManager::Update()
	{
		float myCurrentFrame = glfwGetTime();
		myDeltaTime = myCurrentFrame - myLastFrame;
		myLastFrame = myCurrentFrame;
	}

}