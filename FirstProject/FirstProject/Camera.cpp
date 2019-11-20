#include "Camera.h"
#include "Shader.h"
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 aPosition, glm::vec3 anUp, float aYaw, float aPitch) : myFront(glm::vec3(0.0f, 0.0f, -1.0f)), myMovementSpeed(SPEED), mySensitivity(SENSITIVITY), myFov(ZOOM)
{
	myPosition = aPosition;
	myWorldUp = anUp;
	myYaw = aYaw;
	myPitch = aPitch;
	myInvertedY = INVERTEDY;
	UpdateCameraVectors();
}

// Constructor with scalar values
Camera::Camera(float aPosX, float aPosY, float aPosZ, float anUpX, float anUpY, float anUpZ, float aYaw, float aPitch) : myFront(glm::vec3(0.0f, 0.0f, -1.0f)), myMovementSpeed(SPEED), mySensitivity(SENSITIVITY), myFov(ZOOM)
{
	myPosition = glm::vec3(aPosX, aPosY, aPosZ);
	myWorldUp = glm::vec3(anUpX, anUpY, anUpZ);
	myYaw = aYaw;
	myPitch = aPitch;
	myInvertedY = INVERTEDY;
	UpdateCameraVectors();
}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(myPosition, myPosition + myFront, myUp);
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement aDirection, float aDeltaTime)
{
	float velocity = myMovementSpeed * aDeltaTime;
	if (aDirection == FORWARD)
		myPosition += myFront * velocity;
	if (aDirection == BACKWARD)
		myPosition -= myFront * velocity;
	if (aDirection == LEFT)
		myPosition -= myRight * velocity;
	if (aDirection == RIGHT)
		myPosition += myRight * velocity;
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float aXOffset, float aYOffset, GLboolean aConstrainPitch)
{
	aXOffset *= mySensitivity;
	aYOffset *= mySensitivity;

	myYaw += aXOffset;
	myPitch += aYOffset * (myInvertedY ? 1.0f : -1.0f);

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (aConstrainPitch)
	{
		if (myPitch > 89.0f)
			myPitch = 89.0f;
		if (myPitch < -89.0f)
			myPitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float aYOffset)
{
	if (myFov >= 1.0f && myFov <= 45.0f)
		myFov -= aYOffset;
	if (myFov <= 1.0f)
		myFov = 1.0f;
	if (myFov >= 45.0f)
		myFov = 45.0f;
}

void Camera::InvertY()
{
	myInvertedY = !myInvertedY;
}

void Camera::UpdateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(myYaw)) * cos(glm::radians(myPitch));
	front.y = sin(glm::radians(myPitch));
	front.z = sin(glm::radians(myYaw)) * cos(glm::radians(myPitch));
	myFront = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	myRight = glm::normalize(glm::cross(myFront, myWorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	myUp = glm::normalize(glm::cross(myRight, myFront));
}

void Camera::Render(Shader aShader, GLFWwindow* aWindow)
{
	int width, height;
	glfwGetWindowSize(aWindow, &width, &height);

	// pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
	// -----------
	glm::mat4 myProjection = glm::mat4(1.0f);
	//myProjection = glm::perspective(glm::radians(myFov), (float)width / (float)height, 0.1f, 100.0f);
	myProjection = glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);
	aShader.SetMat4("myProjection", myProjection);

	// create transformations
	// -----------
	glm::mat4 myView = glm::mat4(1.0f);
	myView = GetViewMatrix();
	aShader.SetMat4("myView", myView);
}