#include "Mesh.h"
#include "Shader.h"
#include "stb_image.h"

Mesh::Mesh(std::vector<Vertex> someVertices, std::vector<unsigned int> someIndices, std::vector<Texture> someTextures)
{
	myVertices = someVertices;
	myIndices = someIndices;
	myTextures = someTextures;

	SetupMesh();
}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &myVAO);
	glGenBuffers(1, &myVBO);
	glGenBuffers(1, &myEBO);

	glBindVertexArray(myVAO);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO);

	glBufferData(GL_ARRAY_BUFFER, myVertices.size() * sizeof(Vertex), &myVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, myIndices.size() * sizeof(unsigned int), &myIndices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, myNormal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, myTexCoords));

	glBindVertexArray(0);

	myTexture = loadTexture("Images/container2.png");
}

void Mesh::Draw(Shader aShader)
{
	aShader.SetInt("texture_diffuse1", 0);

	glm::mat4 myModel = glm::mat4(1.0f);
	aShader.SetMat4("model", myModel);

	// activate the texture unit first before binding texture
	// -----------
	glActiveTexture(GL_TEXTURE0);

	// Tell OpenGL to use the texture we loaded
	// -----------
	glBindTexture(GL_TEXTURE_2D, myTexture);

	return;

	unsigned int diffuseNb = 1;
	unsigned int specularNb = 1;
	unsigned int normalNb = 1;
	unsigned int heightNb = 1;
	for (unsigned int i = 0; i < myTextures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
										  // retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = myTextures[i].myType;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNb++);
		else if (name == "texture_specular")
			number = std::to_string(specularNb++);
		else if (name == "texture_normal")
			number = std::to_string(normalNb++); // transfer unsigned int to stream
		else if (name == "texture_height")
			number = std::to_string(heightNb++); // transfer unsigned int to stream

		aShader.SetFloat((/*"myMaterial." +*/ name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, myTextures[i].myId);
	}

	// draw mesh
	glBindVertexArray(myVAO);
	glDrawElements(GL_TRIANGLES, myIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

unsigned int Mesh::loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
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
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}