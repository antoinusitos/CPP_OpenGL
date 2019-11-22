#include "Model.h"

#include "Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb_image.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	Model::Model(const char* aPath, bool aGamma) : myGammaCorrection(aGamma)
	{
		myTransform.myPosition = Vector3(0.0f);
		myTransform.myRotation = Vector3(0.0f, 1.0f, 0.0f);
		myTransform.myScale = Vector3(1.0f);
		LoadModel(aPath);
	}

	void Model::Draw(Shader* aShader)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(myTransform.myPosition.myX, myTransform.myPosition.myY, myTransform.myPosition.myZ));
		model = glm::rotate(model, myAngle, glm::vec3(myTransform.myRotation.myX, myTransform.myRotation.myY, myTransform.myRotation.myZ));
		model = glm::scale(model, glm::vec3(myTransform.myScale.myX, myTransform.myScale.myY, myTransform.myScale.myZ));
		aShader->SetMat4("myModel", model);

		for (unsigned int i = 0; i < myMeshes.size(); i++)
		{
			myMeshes[i].Draw(aShader, myTransform);
		}
	}

	void Model::SetPosition(Vector3 aPosition)
	{
		myTransform.myPosition = aPosition;
	}

	void Model::SetRotation(Vector3 aRotation)
	{
		myTransform.myRotation = aRotation;
	}

	void Model::SetScale(Vector3 aScale)
	{
		myTransform.myScale = aScale;
	}

	Vector3 Model::GetPosition()
	{
		return myTransform.myPosition;
	}

	Vector3 Model::GetRotation()
	{
		return myTransform.myRotation;
	}

	Vector3 Model::GetScale()
	{
		return myTransform.myScale;
	}

	void Model::Update(float aDeltaTime)
	{
		myAngle += aDeltaTime;
	}

	void Model::LoadModel(std::string aPath)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(aPath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}

		myDirectory = aPath.substr(0, aPath.find_last_of('/'));

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* aNode, const aiScene* aScene)
	{
		// process all the node's meshes (if any)
		for (unsigned int i = 0; i < aNode->mNumMeshes; i++)
		{
			aiMesh *mesh = aScene->mMeshes[aNode->mMeshes[i]];
			myMeshes.push_back(ProcessMesh(mesh, aScene));
		}
		// then do the same for each of its children
		for (unsigned int i = 0; i < aNode->mNumChildren; i++)
		{
			ProcessNode(aNode->mChildren[i], aScene);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* aMesh, const aiScene* aScene)
	{
		// data to fill
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		// Walk through each of the mesh's vertices
		for (unsigned int i = 0; i < aMesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
							  // positions
			vector.x = aMesh->mVertices[i].x;
			vector.y = aMesh->mVertices[i].y;
			vector.z = aMesh->mVertices[i].z;
			vertex.myPosition = vector;
			// normals
			vector.x = aMesh->mNormals[i].x;
			vector.y = aMesh->mNormals[i].y;
			vector.z = aMesh->mNormals[i].z;
			vertex.myNormal = vector;
			// texture coordinates
			if (aMesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = aMesh->mTextureCoords[0][i].x;
				vec.y = aMesh->mTextureCoords[0][i].y;
				vertex.myTexCoords = vec;
			}
			else
			{
				vertex.myTexCoords = glm::vec2(0.0f, 0.0f);
			}
			// tangent
			//vector.x = mesh->mTangents[i].x;
			//vector.y = mesh->mTangents[i].y;
			//vector.z = mesh->mTangents[i].z;
			//vertex.Tangent = vector;
			//// bitangent
			//vector.x = mesh->mBitangents[i].x;
			//vector.y = mesh->mBitangents[i].y;
			//vector.z = mesh->mBitangents[i].z;
			//vertex.Bitangent = vector;
			vertices.push_back(vertex);
		}
		// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (unsigned int i = 0; i < aMesh->mNumFaces; i++)
		{
			aiFace face = aMesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		// process materials
		aiMaterial* material = aScene->mMaterials[aMesh->mMaterialIndex];
		// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// diffuse: texture_diffuseN
		// specular: texture_specularN
		// normal: texture_normalN

		// 1. diffuse maps
		std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// 3. normal maps
		std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// 4. height maps
		std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

		// return a mesh object created from the extracted mesh data
		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* aMaterial, aiTextureType aType, std::string aTypeName)
	{
		std::vector<Texture> textures;
		for (unsigned int i = 0; i < aMaterial->GetTextureCount(aType); i++)
		{
			aiString str;
			aMaterial->GetTexture(aType, i, &str);

			bool skip = false;
			for (unsigned int j = 0; j < myTexturesLoaded.size(); j++)
			{
				if (std::strcmp(myTexturesLoaded[j].myPath.data(), str.C_Str()) == 0)
				{
					textures.push_back(myTexturesLoaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				Texture texture;
				texture.myId = TextureFromFile(str.C_Str(), myDirectory);
				texture.myType = aTypeName;
				texture.myPath = str.C_Str();
				textures.push_back(texture);
				myTexturesLoaded.push_back(texture);
			}
		}
		return textures;
	}

	unsigned int Model::TextureFromFile(const char* aPath, const std::string& aDirectory, bool aGamma)
	{
		std::string fileName = std::string(aPath);
		fileName = aDirectory + '/' + fileName;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << aPath << std::endl;
			stbi_image_free(data);
		}

		return textureID;
	}
}