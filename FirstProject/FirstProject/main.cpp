//START NEXT TIME WITH PAGE 33

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"
#include "stb_image.h"

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>


void framebuffer_size_callback(GLFWwindow* aWindow, int aWidth, int aHeight);
void processInput(GLFWwindow* aWindow);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
#pragma region Init

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* myWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (myWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(myWindow);
	glfwSetFramebufferSizeCallback(myWindow, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

#pragma endregion

#pragma region Shader

	int nrAttributes; 
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes); 
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	Shader myShader("simple.vert", "simple.frag");

#pragma endregion

#pragma region Texture

	// create the texture
	// -----------
	unsigned int myTexture;
	glGenTextures(1, &myTexture);

	// bind the texture to an opengl object
	// -----------
	glBindTexture(GL_TEXTURE_2D, myTexture);

	// set the texture wrapping/filtering options (on the currently bound texture object) 
	// -----------
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load the image
	// -----------
	int myWidth;
	int myHeight;
	int myNbChannel;
	unsigned char* myData = stbi_load("Images/container.jpg", &myWidth, &myHeight, &myNbChannel, 0);
	stbi_set_flip_vertically_on_load(true);

	if (myData)
	{
		// generate the texture and generate the mipmap
		// -----------
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, myWidth, myHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, myData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// free the image memory
	// -----------
	stbi_image_free(myData);

	// create the texture
	// -----------
	unsigned int myTexture2;
	glGenTextures(1, &myTexture2);

	// bind the texture to an opengl object
	// -----------
	glBindTexture(GL_TEXTURE_2D, myTexture2);

	// set the texture wrapping/filtering options (on the currently bound texture object) 
	// -----------
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load the image
	// -----------
	myData = stbi_load("Images/awesomeface.png", &myWidth, &myHeight, &myNbChannel, 0);

	if (myData)
	{
		// generate the texture and generate the mipmap
		// -----------
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, myWidth, myHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, myData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// free the image memory
	// -----------
	stbi_image_free(myData);
	
#pragma endregion

#pragma region rectangle

	// create a rectangle
	// -----------
	float myRectangleVertices[] = {
		// positions			// texture coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int myIndices[] = {
		0, 1, 3,	//first triangle
		1, 2, 3		//second triangle
	};

	// create a vertex array object (VAO) to store the vertex objects (as attribute pointers)
	// -----------
	unsigned int myVAOrect;
	glGenVertexArrays(1, &myVAOrect);

	// create a vertex buffer object (VBO) to store the triangle's vertices and assign an ID
	// -----------
	unsigned int myVBOrect;
	glGenBuffers(1, &myVBOrect);

	// create a element buffer object (EBO) to store the vertex and some indices to draw
	// -----------
	unsigned int myEBO;
	glGenBuffers(1, &myEBO);

	// Tell OpenGL to use the vertex array object
	// -----------
	glBindVertexArray(myVAOrect);

	// assign the type of buffer to the ID
	// -----------
	glBindBuffer(GL_ARRAY_BUFFER, myVBOrect);

	// copy the data of the vertices as an array of the size of the triangle into the buffer to draw them
	// -----------
	glBufferData(GL_ARRAY_BUFFER, sizeof(myRectangleVertices), myRectangleVertices, GL_STATIC_DRAW);

	// assign the type of buffer to the ID
	// -----------
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO);

	// copy the indices of the vertices as an array of the size of the number of indices into the buffer to draw them
	// -----------
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(myIndices), myIndices, GL_STATIC_DRAW);

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

#pragma endregion

	// uncomment to show the wireframe
	// -----------
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Tell OpenGL to use the program
	// -----------
	myShader.Use();

	// affect images on channel
	// -----------
	myShader.SetInt("texture1", 0);
	myShader.SetInt("texture2", 1);


#pragma region Rendering

	// render loop
	// -----------
	while (!glfwWindowShouldClose(myWindow))
	{
		// input
		// -----------
		processInput(myWindow);

		// clear the window
		// -----------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#pragma region rectangle rendering
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
		glBindTexture(GL_TEXTURE_2D, myTexture2);

		// Tell OpenGL to use the program
		// -----------
		myShader.Use();

		// create transformations
		// -----------
		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		glm::mat4 view = glm::mat4(1.0f);
		// note that we are translating the scene in the reverse direction of where we want to move 
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		myShader.setMat4("model", model);
		myShader.setMat4("view", view);
		myShader.setMat4("projection", projection);

		// Tell OpenGL to use the vertex array object of the rectangle
		// -----------
		glBindVertexArray(myVAOrect);

		// draw the rectangle using the VAO
		// -----------
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
#pragma endregion

		// check and call events and swap the buffers
		// -----------
		glfwSwapBuffers(myWindow);
		glfwPollEvents();
	}

#pragma endregion

	// free the memory
	glDeleteVertexArrays(1, &myVAOrect);
	glDeleteBuffers(1, &myVBOrect);
	glDeleteBuffers(1, &myEBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* aWindow, int aWidth, int aHeight)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, aWidth, aHeight);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* aWindow) 
{ 
	if (glfwGetKey(aWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(aWindow, true);
	}
}
