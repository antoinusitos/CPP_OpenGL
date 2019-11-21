#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	struct Vector2
	{
		float myX;
		float myY;

		Vector2()
		{
			myX = 0;
			myY = 0;
		}

		Vector2(float aValue)
		{
			myX = aValue;
			myY = aValue;
		}

		Vector2(float aXValue, float aYValue)
		{
			myX = aXValue;
			myY = aYValue;
		}
	};

	struct Vector3
	{
		float myX;
		float myY;
		float myZ;

		Vector3()
		{
			myX = 0;
			myY = 0;
			myZ = 0;
		}

		Vector3(float aValue)
		{
			myX = aValue;
			myY = aValue;
			myZ = aValue;
		}

		Vector3(float aXValue, float aYValue, float aZValue)
		{
			myX = aXValue;
			myY = aYValue;
			myZ = aZValue;
		}
	};

	struct Vector4
	{
		float myX;
		float myY;
		float myZ;
		float myW;

		Vector4()
		{
			myX = 0;
			myY = 0;
			myZ = 0;
			myW = 0;
		}

		Vector4(float aValue)
		{
			myX = aValue;
			myY = aValue;
			myZ = aValue;
			myW = aValue;
		}

		Vector4(float aXValue, float aYValue, float aZValue, float aWValue)
		{
			myX = aXValue;
			myY = aYValue;
			myZ = aZValue;
			myW = aWValue;
		}
	};

	struct Transform
	{
		Vector3 myPosition;
		Vector3 myRotation;
		Vector3 myScale;
	};

	struct UITransform
	{
		Vector2 myPosition;
		Vector3 myRotation;
		Vector2 myScale;
	};

}