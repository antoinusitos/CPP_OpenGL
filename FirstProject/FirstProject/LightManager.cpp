#include "LightManager.h"
#include "Shader.h"
#include "Camera.h"
#include "CameraManager.h"

namespace Engine
{
	LightManager* LightManager::mySingleton = nullptr;

	LightManager::LightManager()
	{
		pointLightPositions = glm::vec3(-0.7f, 0.2f, 1.0f);
	}

	LightManager::~LightManager()
	{
	}

	LightManager* LightManager::GetInstance()
	{
		if (mySingleton == nullptr)
		{
			mySingleton = new LightManager();
		}

		return mySingleton;
	}

	void LightManager::AddLightToShader(Shader* aShader)
	{
		Camera* cam = CameraManager::GetInstance()->GetCamera();

		aShader->SetVec3("myViewPos", cam->myPosition);
		aShader->SetFloat("myMaterial.myShininess", 32.0f);

		aShader->SetVec3("myDirectionalLight.myDirection", -0.2f, -1.0f, -0.3f);
		aShader->SetVec3("myDirectionalLight.myAmbient", 0.2f, 0.2f, 0.2f);
		aShader->SetVec3("myDirectionalLight.myDiffuse", 0.5f, 0.5f, 0.5f);
		aShader->SetVec3("myDirectionalLight.mySpecular", 1.0f, 1.0f, 1.0f);

		aShader->SetVec3("myPointLights[0].myPosition", pointLightPositions);
		aShader->SetVec3("myPointLights[0].myAmbient", 0.05f, 0.05f, 0.05f);
		aShader->SetVec3("myPointLights[0].myDiffuse", 0.8f, 0.8f, 0.8f);
		aShader->SetVec3("myPointLights[0].mySpecular", 1.0f, 1.0f, 1.0f);
		aShader->SetFloat("myPointLights[0].myConstant", 1.0f);
		aShader->SetFloat("myPointLights[0].myLinear", 0.09);
		aShader->SetFloat("myPointLights[0].myQuadratic", 0.032);

		aShader->SetVec3("mySpotLight.myPosition", cam->myPosition);
		aShader->SetVec3("mySpotLight.myDirection", cam->myFront);
		aShader->SetVec3("mySpotLight.myAmbient", 0.0f, 0.0f, 0.0f);
		aShader->SetVec3("mySpotLight.myDiffuse", 1.0f, 1.0f, 1.0f);
		aShader->SetVec3("mySpotLight.mySpecular", 1.0f, 1.0f, 1.0f);
		aShader->SetFloat("mySpotLight.myConstant", 1.0f);
		aShader->SetFloat("mySpotLight.myLinear", 0.09);
		aShader->SetFloat("mySpotLight.myQuadratic", 0.032);
		aShader->SetFloat("mySpotLight.myCutOff", glm::cos(glm::radians(12.5f)));
		aShader->SetFloat("mySpotLight.myOuterCutOff", glm::cos(glm::radians(15.0f)));

		glm::mat4 model = glm::mat4(1.0f);
		aShader->SetMat4("myModel", model);

	}

}