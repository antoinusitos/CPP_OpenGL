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

// camera
// -----------
glm::vec3 myCameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 myCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 myCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// timing
// -----------
float myDeltaTime = 0.0f; // Time between current frame and last frame
float myLastFrame = 0.0f; // Time of last frame

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

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

#pragma endregion

#pragma region Shader

	//int nrAttributes; 
	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes); 
	//std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

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

	// Tell OpenGL to use the program
	// -----------
	myShader.Use();

	// affect images on channel
	// -----------
	myShader.SetInt("texture1", 0);
	myShader.SetInt("texture2", 1);

	// uncomment to show the wireframe
	// -----------
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
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

	// create a vertex array object (VAO) to store the vertex objects (as attribute pointers)
	// -----------
	unsigned int myVAOrect;
	glGenVertexArrays(1, &myVAOrect);

	// create a vertex buffer object (VBO) to store the triangle's vertices and assign an ID
	// -----------
	unsigned int myVBOrect;
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

	// world space positions of our cubes
	// -----------
	glm::vec3 myCubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

#pragma endregion

	// defining a camera
	// -----------
	/*glm::vec3 myCameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 myCameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 myCameraDirection = glm::normalize(myCameraPos - myCameraTarget);
	glm::vec3 myUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 myCameraRight = glm::normalize(glm::cross(myUp, myCameraDirection));
	glm::vec3 myCameraUp = glm::normalize(glm::cross(myCameraDirection, myCameraRight));*/

	// pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
	// -----------
	glm::mat4 myProjection = glm::mat4(1.0f);
	myProjection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	myShader.setMat4("projection", myProjection);

#pragma region Rendering

	// render loop
	// -----------
	while (!glfwWindowShouldClose(myWindow))
	{
		// per-frame time logic
		// -----------
		float myCurrentFrame = glfwGetTime();
		myDeltaTime = myCurrentFrame - myLastFrame;
		myLastFrame = myCurrentFrame;

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
		float myRadius = 10.0f;
		float myCamX = sin(glfwGetTime()) * myRadius;
		float myCamZ = cos(glfwGetTime()) * myRadius;

		glm::mat4 myView = glm::mat4(1.0f);
		myView = glm::lookAt(
			myCameraPos,					//position
			myCameraPos + myCameraFront,	//target
			myCameraUp);					//up
		myShader.setMat4("view", myView);

		// Render Boxes
		// -----------
		glBindVertexArray(myVAOrect);

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, myCubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			myShader.setMat4("model", model);

			// draw the rectangle
			// -----------
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
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
	//glDeleteBuffers(1, &myEBO);

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

	float myCameraSpeed = 2.5f * myDeltaTime;
	if (glfwGetKey(aWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		myCameraPos += myCameraSpeed * myCameraFront;
	}
	if (glfwGetKey(aWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		myCameraPos -= myCameraSpeed * myCameraFront;
	}

	if (glfwGetKey(aWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		myCameraPos -= glm::normalize(glm::cross(myCameraFront, myCameraUp)) * myCameraSpeed;
	}
	if (glfwGetKey(aWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		myCameraPos += glm::normalize(glm::cross(myCameraFront, myCameraUp)) * myCameraSpeed;
	}
}
