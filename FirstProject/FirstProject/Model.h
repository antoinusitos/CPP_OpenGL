#pragma once

#include <vector>
#include "Mesh.h"

class Shader;
class Mesh;

struct Texture;
struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;
enum aiTextureType;

struct Transform
{
	glm::vec3 myPosition;
	glm::vec3 myRotation;
	glm::vec3 myScale;
}

class Model
{
public:
	Model(char* aPath, bool aGamma = false);

	void Draw(Shader aShader);
	
	void SetPosition(glm::vec3 aPosition);
	void SetRotation(glm::vec3 aRotation);
	void SetScale(glm::vec3 aScale);

private:
	std::vector<Texture> myTexturesLoaded;
	std::vector<Mesh> myMeshes;
	std::string myDirectory;
	bool myGammaCorrection;
	Transform myTransform;

private:
	void LoadModel(std::string aPath);
	void ProcessNode(aiNode* aNode, const aiScene* aScene);
	Mesh ProcessMesh(aiMesh* aMesh, const aiScene* aScene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* aMaterial, aiTextureType aType, std::string aTypeName);
	unsigned int TextureFromFile(const char* aPath, const std::string& aDirectory, bool aGamma = false);
};
