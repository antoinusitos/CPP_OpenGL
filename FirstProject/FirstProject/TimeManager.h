#pragma once

namespace Engine
{
	class TimeManager
	{
	public:
		TimeManager();
		~TimeManager();

		static TimeManager* GetInstance();

		const float GetDeltaTime();

		void Update();

	private:
		static TimeManager* mySingleton;
		
		float myDeltaTime;
		float myLastFrame;
	};
}