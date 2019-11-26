#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	class Shader;

	class LightManager
	{
	public:
		LightManager();
		~LightManager();

		static LightManager* GetInstance();

		void AddLightToShader(Shader* aShader);

	private:
		static LightManager* mySingleton;

		glm::vec3 pointLightPositions;
	};
}