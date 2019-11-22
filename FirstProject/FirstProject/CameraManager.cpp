#include "CameraManager.h"
#include "Camera.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Engine
{
	CameraManager* CameraManager::mySingleton = nullptr;

	CameraManager::CameraManager()
	{
	}


	CameraManager::~CameraManager()
	{
	}

	CameraManager* CameraManager::GetInstance()
	{
		if (mySingleton == nullptr)
		{
			mySingleton = new CameraManager();
		}

		return mySingleton;
	}

	Camera * CameraManager::GetCamera()
	{
		return myCamera;
	}

	void CameraManager::InitCamera()
	{
		myCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	}

}