#pragma once

namespace Engine
{
	class Camera;

	class CameraManager
	{
	public:
		CameraManager();
		~CameraManager();

		static CameraManager* GetInstance();

		Camera* GetCamera();

		void InitCamera();

	protected:
		Camera* myCamera;

	private:
		static CameraManager* mySingleton;
	};
}