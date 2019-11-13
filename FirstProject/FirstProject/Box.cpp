#include "Box.h"
#include "Shader.h"

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// unbind the buffer
	// -----------
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// unbind the vertex array
	// -----------
	glBindVertexArray(0);
}

void Box::Render(Shader aShader)
{
	myModel = glm::translate(myModel, myPosition);
	aShader.setMat4("model", myModel);
	glBindVertexArray(myVAOrect);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Box::FreeCube()
{
	// free the memory
	// ---------------
	glDeleteVertexArrays(1, &myVAOrect);
	glDeleteBuffers(1, &myVBOrect);
}
