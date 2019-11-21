#include "Mesh.h"
#include "Shader.h"
#include "stb_image.h"
#include "Data.h"

namespace Engine
{
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

	void Mesh::Draw(Shader aShader, Transform aTransform)
	{
		unsigned int diffuseNb = 1;
		unsigned int specularNb = 1;
		unsigned int normalNb = 1;
		unsigned int heightNb = 1;
		aShader.SetInt("myMaterial.myDiffuse", 0);
		aShader.SetInt("myMaterial.mySpecular", 1);
		aShader.SetInt("myMaterial.myEmissive", 2);
		aShader.SetFloat("myMaterial.myShininess", 64);

		for (unsigned int i = 0; i < myTextures.size(); i++)
		{
			/*glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
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

			aShader.SetFloat((name + number).c_str(), i);

			glBindTexture(GL_TEXTURE_2D, myTextures[i].myId);*/

			std::string name = myTextures[i].myType;
			if (name == "texture_diffuse")
			{
				// activate the texture unit first before binding texture
				// -----------
				glActiveTexture(GL_TEXTURE0);

				// Tell OpenGL to use the texture we loaded
				// -----------
				glBindTexture(GL_TEXTURE_2D, myTextures[i].myId);
			}
			else if (name == "texture_specular")
			{
				// activate the texture unit first before binding texture
				// -----------
				glActiveTexture(GL_TEXTURE1);

				// Tell OpenGL to use the texture we loaded
				// -----------
				glBindTexture(GL_TEXTURE_2D, myTextures[i].myId);
			}
			/*else if (name == "texture_normal")
			{
				// activate the texture unit first before binding texture
				// -----------
				glActiveTexture(GL_TEXTURE2);

				// Tell OpenGL to use the texture we loaded
				// -----------
				glBindTexture(GL_TEXTURE_2D, myTextures[i].myId);
			}*/
		}

		// draw mesh
		glBindVertexArray(myVAO);
		glDrawElements(GL_TRIANGLES, myIndices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}