#pragma once

namespace Engine
{
	class Model;

	class EditorManager
	{
	public:
		EditorManager();
		~EditorManager();

		Model* myObject;

		static EditorManager* GetInstance();

		void MoveObject(const float aDeltaTime);

	private:
		static EditorManager* mySingleton;
	};
}