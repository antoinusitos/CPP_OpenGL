#pragma once

// include glad to get all the required OpenGL headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
const bool INVERTEDY = false;

class Camera
{
public:
	// Camera Attributes
	glm::vec3 myPosition;
	glm::vec3 myFront;
	glm::vec3 myUp;
	glm::vec3 myRight;
	glm::vec3 myWorldUp;
	// Euler Angles
	float myYaw;
	float myPitch;
	// Camera options
	float myFov;
	float myMovementSpeed;
	float mySensitivity;
	bool myInvertedY;

public:
	// Constructor with vectors
	Camera(glm::vec3 aPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 anUp = glm::vec3(0.0f, 1.0f, 0.0f), float aYaw = YAW, float aPitch = PITCH);
	// Constructor with scalar values
	Camera(float aPosX, float aPosY, float aPosZ, float anUpX, float anUpY, float anUpZ, float aYaw, float aPitch);

	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();
	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement aDirection, float aDeltaTime);
	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float aXOffset, float aYOffset, GLboolean aConstrainPitch = true);
	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float aYOffset);
	void InvertY();

private:
	// Calculates the front vector from the Camera's (updated) Euler Angles
	void UpdateCameraVectors();
};