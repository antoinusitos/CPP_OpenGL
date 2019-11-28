
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

#include "ResourceManager.h"
#include "EditorUIManager.h"
#include "CameraManager.h"
#include "Camera.h"
#include "FileLinkerManager.h"
#include "EditorManager.h"
#include "TimeManager.h"
#include "TextManager.h"

void framebuffer_size_callback(GLFWwindow* aWindow, int aWidth, int aHeight);
void processInput(GLFWwindow* aWindow, Engine::UIManager* aUIManager);
void Mouse_Callback(GLFWwindow* aWindow, double aXPos, double aYPos);
void Scroll_Callback(GLFWwindow* aWindow, double aXOffset, double aYOffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
	if (!glfwInit()) {
		std::cout << "failed to initialize GLFW." << std::endl;
		return -1;
	}
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
	//glfwSetInputMode(myWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Tell opengl to call back when the mouse move
	// -----------------------------
	glfwSetCursorPosCallback(myWindow, Mouse_Callback);

	// Tell opengl to call back when the mouse wheel move
	// -----------------------------
	glfwSetScrollCallback(myWindow, Scroll_Callback);

	Engine::CameraManager::GetInstance()->InitCamera();
#pragma endregion

#pragma region fileWatcher

	// Create a FileWatcher instance that will check the current folder for changes every 5 seconds
	Engine::FileWatcher::GetInstance()->SetPathToWatch("./", std::chrono::milliseconds(1000));

#pragma endregion

	Engine::FileLinkerManager::GetInstance();

	Engine::Model* myModel = Engine::ResourceManager::GetInstance()->LoadModel("nanosuit");
	myModel->SetPosition(Engine::Vector3(0.0f, -1.75f, 0.0f));
	myModel->SetScale(Engine::Vector3(0.1f, 0.1f, 0.1f));

	Engine::Box* myBox = new Engine::Box(0,0,-1);

	Engine::EditorManager::GetInstance()->myObject = myModel;

	Editor::EditorUIManager* myEditorUIManager = new Editor::EditorUIManager();
	myEditorUIManager->SetWindow(myWindow);
	myEditorUIManager->InitUIManager();

	Engine::Shader* myTextShader = Engine::ResourceManager::GetInstance()->LoadShader("TextShader", "Text.vert", "Text.frag");

	Engine::TextManager::GetInstance();

#pragma region Rendering

	// render loop
	// -----------
	while (!glfwWindowShouldClose(myWindow))
	{
		// per-frame time logic
		// -----------
		Engine::TimeManager::GetInstance()->Update();

		// Checking file modification
		// -----------
		Engine::FileWatcher::GetInstance()->SetDeltaTime(Engine::TimeManager::GetInstance()->GetDeltaTime());
		Engine::FileWatcher::GetInstance()->Update([](std::string path_to_watch, Engine::FileStatus status) -> void
		{
			// Process only regular files, all other file types are ignored
			if (!std::experimental::filesystem::is_regular_file(std::experimental::filesystem::path(path_to_watch)) && status != Engine::FileStatus::erased)
			{
				return;
			}
		});

		// update editor
		// -----------
		myEditorUIManager->UpdateMousePosition(glm::vec2(myLastMousePosX, myLastMousePosY));
		myEditorUIManager->UpdateManager();

		// input
		// -----------
		processInput(myWindow, myEditorUIManager);

		// clear the window
		// -----------
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render editor
		// -----------
		myEditorUIManager->RenderManager(myWindow);

		myBox->Render(myWindow);

		myModel->Update(Engine::TimeManager::GetInstance()->GetDeltaTime());
		myModel->Render(myWindow);

		Engine::TextManager::GetInstance()->RenderText(myTextShader, myWindow, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

		// check and call events and swap the buffers
		// -----------
		glfwSwapBuffers(myWindow);
		glfwPollEvents();
	}

#pragma endregion

	delete myEditorUIManager;

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
void processInput(GLFWwindow* aWindow, Engine::UIManager* aUIManager)
{ 
	if (glfwGetKey(aWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(aWindow, true);
	}

	Engine::Camera* cam = Engine::CameraManager::GetInstance()->GetCamera();

	float myCameraSpeed = 2.5f * myDeltaTime;
	if (glfwGetKey(aWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		cam->ProcessKeyboard(Engine::FORWARD, myDeltaTime);
	}
	if (glfwGetKey(aWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		cam->ProcessKeyboard(Engine::BACKWARD, myDeltaTime);
	}

	if (glfwGetKey(aWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		cam->ProcessKeyboard(Engine::LEFT, myDeltaTime);
	}
	if (glfwGetKey(aWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		cam->ProcessKeyboard(Engine::RIGHT, myDeltaTime);
	}

	if (glfwGetKey(aWindow, GLFW_KEY_Y) == GLFW_PRESS)
	{
		cam->InvertY();
	}

	if (glfwGetMouseButton(aWindow, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		aUIManager->UpdateMouseStatus(true);
	}
	else
	{
		aUIManager->UpdateMouseStatus(false);
	}

	if (glfwGetMouseButton(aWindow, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		cam->SetIsMoving(true);
	}
	else
	{
		cam->SetIsMoving(false);
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

	Engine::CameraManager::GetInstance()->GetCamera()->ProcessMouseMovement(xOffset, yOffset);
}

void Scroll_Callback(GLFWwindow* aWindow, double aXOffset, double aYOffset)
{
	Engine::CameraManager::GetInstance()->GetCamera()->ProcessMouseScroll(aYOffset);
}