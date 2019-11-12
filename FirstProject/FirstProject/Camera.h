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

	// Constructor with vectors
	Camera(glm::vec3 aPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 anUp = glm::vec3(0.0f, 1.0f, 0.0f), float aYaw = YAW, float aPitch = PITCH) : myFront(glm::vec3(0.0f, 0.0f, -1.0f)), myMovementSpeed(SPEED), mySensitivity(SENSITIVITY), myFov(ZOOM)
	{
		myPosition = aPosition;
		myWorldUp = anUp;
		myYaw = aYaw;
		myPitch = aPitch;
		myInvertedY = INVERTEDY;
		UpdateCameraVectors();
	}
	// Constructor with scalar values
	Camera(float aPosX, float aPosY, float aPosZ, float anUpX, float anUpY, float anUpZ, float aYaw, float aPitch) : myFront(glm::vec3(0.0f, 0.0f, -1.0f)), myMovementSpeed(SPEED), mySensitivity(SENSITIVITY), myFov(ZOOM)
	{
		myPosition = glm::vec3(aPosX, aPosY, aPosZ);
		myWorldUp = glm::vec3(anUpX, anUpY, anUpZ);
		myYaw = aYaw;
		myPitch = aPitch;
		myInvertedY = INVERTEDY;
		UpdateCameraVectors();
	}

	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(myPosition, myPosition + myFront, myUp);
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement aDirection, float aDeltaTime)
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
	void ProcessMouseMovement(float aXOffset, float aYOffset, GLboolean aConstrainPitch = true)
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
	void ProcessMouseScroll(float aYOffset)
	{
		if (myFov >= 1.0f && myFov <= 45.0f)
			myFov -= aYOffset;
		if (myFov <= 1.0f)
			myFov = 1.0f;
		if (myFov >= 45.0f)
			myFov = 45.0f;
	}

	void InvertY()
	{
		myInvertedY = !myInvertedY;
	}

private:
	// Calculates the front vector from the Camera's (updated) Euler Angles
	void UpdateCameraVectors()
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
};