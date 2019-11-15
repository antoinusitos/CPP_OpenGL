//START NEXT TIME WITH PAGE 33

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"
#include "stb_image.h"
#include "Camera.h"
#include "Box.h"

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#include "FileWatcher.h"

void framebuffer_size_callback(GLFWwindow* aWindow, int aWidth, int aHeight);
void processInput(GLFWwindow* aWindow);
void Mouse_Callback(GLFWwindow* aWindow, double aXPos, double aYPos);
void Scroll_Callback(GLFWwindow* aWindow, double aXOffset, double aYOffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
// -----------
Camera* myCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

Camera* myMainCamera = myCamera;

bool cam1 = true;
// timing
// -----------
float myDeltaTime = 0.0f; // Time between current frame and last frame
float myLastFrame = 0.0f; // Time of last frame

// mouse position
// -----------
float myLastMousePosX = 400.0f;
float myLastMousePosY = 300.0f;

bool myFirstMouse = false;

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

	// hide and capture the cursor
	// -----------------------------
	glfwSetInputMode(myWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Tell opengl to call back when the mouse move
	// -----------------------------
	glfwSetCursorPosCallback(myWindow, Mouse_Callback);

	// Tell opengl to call back when the mouse wheel move
	// -----------------------------
	glfwSetScrollCallback(myWindow, Scroll_Callback);
#pragma endregion

#pragma region fileWatcher

	// Create a FileWatcher instance that will check the current folder for changes every 5 seconds
	FileWatcher fw{ "./", std::chrono::milliseconds(1000) };
#pragma endregion

#pragma region Shader

	//int nrAttributes; 
	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes); 
	//std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	Shader myShader("simple.vert", "simple.frag");
	Shader myLightShader("Lights.vert", "Lights.frag");
	Shader myColorShader("Color.vert", "Color.frag");

	fw.myShaders.push_back(myShader);
	fw.myShaders.push_back(myLightShader);
	fw.myShaders.push_back(myColorShader);

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

	// world space positions of our cubes
	// -----------
	Box cubes[] = {
		Box(0.0f,  0.0f,  0.0f),
		Box(2.0f,  5.0f, -15.0f),
		Box(-1.5f, -2.2f, -2.5f),
		Box(-3.8f, -2.0f, -12.3f),
		Box(2.4f, -0.4f, -3.5f),
		Box(-1.7f,  3.0f, -7.5f),
		Box(1.3f, -2.0f, -2.5f),
		Box(1.5f,  2.0f, -2.5f),
		Box(1.5f,  0.2f, -1.5f),
		Box(-1.3f,  1.0f, -1.5f)
	};

	//Box myLight = Box(1.2f, 1.0f, 2.0f);
	//myLight.Scale(glm::vec3(0.2f));

	for (unsigned int i = 0; i < 10; i++)
	{
		cubes[i].Rotate(20.0f * i);
	}

	Box myPointLightPositions[] = {
		Box(0.7f,  0.2f,  2.0f),
		Box(2.3f, -3.3f, -4.0f),
		Box(-4.0f,  2.0f, -12.0f),
		Box(0.0f,  0.0f, -3.0f)
	};

	for (unsigned int i = 0; i < 4; i++)
	{
		myPointLightPositions[i].Scale(glm::vec3(0.2f));
	}

#pragma endregion

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

		// Checking file modification
		// -----------
		fw.myDeltaTime = myDeltaTime;
		fw.Update([](std::string path_to_watch, FileStatus status) -> void
		{
			// Process only regular files, all other file types are ignored
			if (!std::experimental::filesystem::is_regular_file(std::experimental::filesystem::path(path_to_watch)) && status != FileStatus::erased)
			{
				return;
			}
		});

		// input
		// -----------
		processInput(myWindow);

		// clear the window
		// -----------
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#pragma region rectangle rendering
		// Tell OpenGL to use the program
		// -----------
		myLightShader.Use();
		myLightShader.SetVec3("myViewPos", myMainCamera->myPosition);
		// directional light
		myLightShader.SetVec3("myDirectionalLight.myDirection", -0.2f, -1.0f, -0.3f);
		myLightShader.SetVec3("myDirectionalLight.myAmbient", 0.05f, 0.05f, 0.05f);
		myLightShader.SetVec3("myDirectionalLight.myDiffuse", 0.4f, 0.4f, 0.4f);
		myLightShader.SetVec3("myDirectionalLight.mySpecular", 0.5f, 0.5f, 0.5f);

		for (unsigned int i = 0; i < 4; i++)
		{
			std::string number = std::to_string(i);
			myLightShader.SetVec3(("myPointLights[" + number + "].myPosition").c_str(), myPointLightPositions[i].myPosition);
			myLightShader.SetVec3("myPointLights[" + number + "].myAmbient", 0.05f, 0.05f, 0.05f);
			myLightShader.SetVec3("myPointLights[" + number + "].myDiffuse", 0.8f, 0.8f, 0.8f);
			myLightShader.SetVec3("myPointLights[" + number + "].mySpecular", 1.0f, 1.0f, 1.0f);
			myLightShader.SetFloat("myPointLights[" + number + "].myConstant", 1.0f);
			myLightShader.SetFloat("myPointLights[" + number + "].myLinear", 0.09);
			myLightShader.SetFloat("myPointLights[" + number + "].myQuadratic", 0.032);
		}

		// settings for the point and spot light
		myLightShader.SetVec3("mySpotLight.myPosition", myMainCamera->myPosition);
		myLightShader.SetVec3("mySpotLight.myDirection", myMainCamera->myFront);
		myLightShader.SetVec3("mySpotLight.myAmbient", 0.0f, 0.0f, 0.0f);
		myLightShader.SetVec3("mySpotLight.myDiffuse", 1.0f, 1.0f, 1.0f);
		myLightShader.SetVec3("mySpotLight.mySpecular", 1.0f, 1.0f, 1.0f);
		myLightShader.SetFloat("mySpotLight.myConstant", 1.0f);
		myLightShader.SetFloat("mySpotLight.myLinear", 0.09f);
		myLightShader.SetFloat("mySpotLight.myQuadratic", 0.032f);
		myLightShader.SetFloat("mySpotLight.myCutOff", glm::cos(glm::radians(12.5f)));
		myLightShader.SetFloat("mySpotLight.myOuterCutOff", glm::cos(glm::radians(17.5f)));

		// view/projection transformations
		myMainCamera->Render(myLightShader, myWindow);

		// Render Box
		// -----------
		for (unsigned int i = 0; i < 10; i++)
		{
			cubes[i].Render(myLightShader);
		}

		myColorShader.Use();
		myMainCamera->Render(myColorShader, myWindow);

		for (unsigned int i = 0; i < 4; i++)
		{
			myPointLightPositions[i].Render(myColorShader);
		}

#pragma endregion

		// check and call events and swap the buffers
		// -----------
		glfwSwapBuffers(myWindow);
		glfwPollEvents();
	}

#pragma endregion

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
		myMainCamera->ProcessKeyboard(FORWARD, myDeltaTime);
	}
	if (glfwGetKey(aWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		myMainCamera->ProcessKeyboard(BACKWARD, myDeltaTime);
	}

	if (glfwGetKey(aWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		myMainCamera->ProcessKeyboard(LEFT, myDeltaTime);
	}
	if (glfwGetKey(aWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		myMainCamera->ProcessKeyboard(RIGHT, myDeltaTime);
	}

	if (glfwGetKey(aWindow, GLFW_KEY_Y) == GLFW_PRESS)
	{
		myMainCamera->InvertY();
	}
}

void Mouse_Callback(GLFWwindow* aWindow, double aXPos, double aYPos)
{
	if (myFirstMouse)
	{
		myFirstMouse = false;
		myLastMousePosX = aXPos;
		myLastMousePosY = aYPos;
	}

	float xOffset = aXPos - myLastMousePosX;
	float yOffset = aYPos - myLastMousePosY;

	myLastMousePosX = aXPos;
	myLastMousePosY = aYPos;

	myMainCamera->ProcessMouseMovement(xOffset, yOffset);
}

void Scroll_Callback(GLFWwindow* aWindow, double aXOffset, double aYOffset)
{
	myMainCamera->ProcessMouseScroll(aYOffset);
}