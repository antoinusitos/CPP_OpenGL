
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"
#include "stb_image.h"
#include "Camera.h"
#include "Box.h"
#include "Model.h"

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

	Shader myShaderModel("ModelLoading.vert", "ModelLoading.frag");

	fw.myShaders.push_back(myShaderModel);

#pragma endregion

	Model myModel = Model("Models/NanoSuit/nanosuit.obj");

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
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		//glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#pragma region rectangle rendering
		// Tell OpenGL to use the program
		// -----------
		myShaderModel.Use();

		myCamera->Render(myShaderModel, myWindow);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		myShaderModel.SetMat4("model", model);
		myModel.Draw(myShaderModel);

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
		myCamera->ProcessKeyboard(FORWARD, myDeltaTime);
	}
	if (glfwGetKey(aWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		myCamera->ProcessKeyboard(BACKWARD, myDeltaTime);
	}

	if (glfwGetKey(aWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		myCamera->ProcessKeyboard(LEFT, myDeltaTime);
	}
	if (glfwGetKey(aWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		myCamera->ProcessKeyboard(RIGHT, myDeltaTime);
	}

	if (glfwGetKey(aWindow, GLFW_KEY_Y) == GLFW_PRESS)
	{
		myCamera->InvertY();
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

	myCamera->ProcessMouseMovement(xOffset, yOffset);
}

void Scroll_Callback(GLFWwindow* aWindow, double aXOffset, double aYOffset)
{
	myCamera->ProcessMouseScroll(aYOffset);
}