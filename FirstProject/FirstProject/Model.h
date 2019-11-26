#pragma once

#include <vector>
#include "Mesh.h"
#include "Data.h"

struct Texture;
struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

enum aiTextureType;

struct GLFWwindow;

namespace Engine
{
	class Shader;
	class Mesh;

	class Model
	{
	public:
		Model(const char* aPath, bool aGamma = false);

		void Render(GLFWwindow* aWindow);

		void SetPosition(Vector3 aPosition);
		void SetRotation(Vector3 aRotation);
		void SetScale(Vector3 aScale);

		Vector3 GetPosition();
		Vector3 GetRotation();
		Vector3 GetScale();

		void Update(float aDeltaTime);

	private:
		std::vector<Texture> myTexturesLoaded;
		std::vector<Mesh> myMeshes;
		std::string myDirectory;
		std::string myFullPath;
		bool myGammaCorrection;
		Transform myTransform;
		float myAngle = 0;

		Shader* myShader;

	private:
		void LoadModel(std::string aPath);
		void ProcessNode(aiNode* aNode, const aiScene* aScene);
		Mesh ProcessMesh(aiMesh* aMesh, const aiScene* aScene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* aMaterial, aiTextureType aType, std::string aTypeName);
	};
}