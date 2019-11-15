#include "Mesh.h"
#include "Shader.h"

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
}

void Mesh::Draw(Shader aShader)
{
	unsigned int diffuseNb = 1;
	unsigned int specularNb = 1;
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

		aShader.SetFloat(("myMaterial." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, myTextures[i].myId);
	}
	glActiveTexture(GL_TEXTURE0);

	// draw mesh
	glBindVertexArray(myVAO);
	glDrawElements(GL_TRIANGLES, myIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}