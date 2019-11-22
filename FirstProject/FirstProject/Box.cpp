#include "Box.h"
#include "Shader.h"
#include "stb_image.h"
#include "ResourceManager.h"

namespace Engine
{
	Box::Box(glm::vec3 aPosition)
	{
		Init();

		myPosition = aPosition;
	}

	Box::Box(float aX, float aY, float aZ)
	{
		Init();

		myPosition = glm::vec3(aX, aY, aZ);
	}

	void Box::Init()
	{
		// create a vertex array object (VAO) to store the vertex objects (as attribute pointers)
		// -----------
		glGenVertexArrays(1, &myVAOrect);

		// create a vertex buffer object (VBO) to store the triangle's vertices and assign an ID
		// -----------
		glGenBuffers(1, &myVBOrect);

		// Tell OpenGL to use the vertex array object
		// -----------
		glBindVertexArray(myVAOrect);

		// assign the type of buffer to the ID
		// -----------
		glBindBuffer(GL_ARRAY_BUFFER, myVBOrect);

		// copy the data of the vertices as an array of the size of the triangle into the buffer to draw them
		// -----------
		glBufferData(GL_ARRAY_BUFFER, sizeof(myRectangleVertices), myRectangleVertices, GL_STATIC_DRAW);

		// Tell OpenGL how to interpret the vertex data per vertex attribute
		// -----------
		// position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// texture coordinates
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// unbind the buffer
		// -----------
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// unbind the vertex array
		// -----------
		glBindVertexArray(0);

		myMaterial.myShininess = 32.0f;

		//myTexture = loadTexture("Images/container2.png");
		myTexture = ResourceManager::GetInstance()->LoadTexture("container2.png", "container2");
		//myTextureSpecular = loadTexture("Images/container2_specular.png");
		myTextureSpecular = ResourceManager::GetInstance()->LoadTexture("container2_specular.png", "container2_specular");
		//myTextureEmissive = loadTexture("Images/matrix.jpg");
		myTextureEmissive = ResourceManager::GetInstance()->LoadTexture("matrix.jpg", "matrix");
	}

	void Box::Scale(glm::vec3 aScale)
	{
		myScale = aScale;
	}

	void Box::Rotate(float anAngle)
	{
		myAngle = glm::radians(anAngle);
	}

	void Box::Update(float aDeltaTime)
	{

	}

	void Box::Render(Shader* aShader)
	{
		aShader->SetInt("myMaterial.myDiffuse", 0);
		aShader->SetInt("myMaterial.mySpecular", 1);
		aShader->SetInt("myMaterial.myEmissive", 2);
		aShader->SetFloat("myMaterial.myShininess", myMaterial.myShininess);

		myModel = glm::mat4(1.0f);
		myModel = glm::translate(myModel, myPosition);
		myModel = glm::rotate(myModel, myAngle, myRotation);
		myModel = glm::scale(myModel, myScale);
		aShader->SetMat4("myModel", myModel);

		// activate the texture unit first before binding texture
		// -----------
		glActiveTexture(GL_TEXTURE0);

		// Tell OpenGL to use the texture we loaded
		// -----------
		glBindTexture(GL_TEXTURE_2D, myTexture);

		// activate the texture unit first before binding texture
		// -----------
		glActiveTexture(GL_TEXTURE1);

		// Tell OpenGL to use the texture we loaded
		// -----------
		glBindTexture(GL_TEXTURE_2D, myTextureSpecular);

		// activate the texture unit first before binding texture
		// -----------
		glActiveTexture(GL_TEXTURE2);

		// Tell OpenGL to use the texture we loaded
		// -----------
		glBindTexture(GL_TEXTURE_2D, myTextureEmissive);

		glBindVertexArray(myVAOrect);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Box::FreeCube()
	{
		// free the memory
		// ---------------
		glDeleteVertexArrays(1, &myVAOrect);
		glDeleteBuffers(1, &myVBOrect);
	}

	unsigned int Box::loadTexture(char const * path)
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
}