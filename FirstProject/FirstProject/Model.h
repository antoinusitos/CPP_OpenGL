#pragma once

#include <vector>
#include "Mesh.h"
#include "Data.h"

class Shader;
class Mesh;

struct Texture;
struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

enum aiTextureType;

class Model
{
public:
	Model(char* aPath, bool aGamma = false);

	void Draw(Shader aShader);
	
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
	bool myGammaCorrection;
	Transform myTransform;
	float myAngle = 0;

private:
	void LoadModel(std::string aPath);
	void ProcessNode(aiNode* aNode, const aiScene* aScene);
	Mesh ProcessMesh(aiMesh* aMesh, const aiScene* aScene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* aMaterial, aiTextureType aType, std::string aTypeName);
	unsigned int TextureFromFile(const char* aPath, const std::string& aDirectory, bool aGamma = false);
};
