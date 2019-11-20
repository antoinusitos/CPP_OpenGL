#pragma once

#include <glm/glm.hpp>

struct Transform
{
	glm::vec3 myPosition;
	glm::vec3 myRotation;
	glm::vec3 myScale;
};

struct UITransform
{
	glm::vec2 myPosition;
	glm::vec3 myRotation;
	glm::vec2 myScale;
};