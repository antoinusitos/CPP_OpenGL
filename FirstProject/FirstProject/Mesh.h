#pragma once

// include glad to get all the required OpenGL headers
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

class Shader;

struct Vertex 
{
	glm::vec3 myPosition;
	glm::vec3 myNormal;
	glm::vec2 myTexCoords;
};

struct Texture 
{
	unsigned int myId;
	std::string myType;
	std::string myPath;
};

class Mesh
{
public:
	// mesh data
	// ---------
	std::vector<Vertex> myVertices;
	std::vector<unsigned int> myIndices;
	std::vector<Texture> myTextures;

	unsigned int myTexture;

	// functions
	// ---------
	Mesh(std::vector<Vertex> someVertices, std::vector<unsigned int> someIndices, std::vector<Texture> someTextures);
	void Draw(Shader aShader);

private:
	// render data
	// ---------
	unsigned int myVAO;
	unsigned int myVBO;
	unsigned int myEBO;

	// functions
	// ---------
	void SetupMesh();
};