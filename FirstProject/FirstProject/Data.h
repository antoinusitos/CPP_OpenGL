#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Engine
{
	class UIElement;

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

		Vector2 operator-(Vector2 aVector)
		{
			Vector2 toReturn;
			toReturn.myX = myX - aVector.myX;
			toReturn.myY = myY - aVector.myX;
			return toReturn;
		}

		Vector2 operator+(Vector2 aVector)
		{
			Vector2 toReturn;
			toReturn.myX = myX + aVector.myX;
			toReturn.myY = myY + aVector.myX;
			return toReturn;
		}

		std::string ToString()
		{
			return "X : " + std::to_string(myX) + " ;Y : " + std::to_string(myY);
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

		std::string ToString()
		{
			return "X : " + std::to_string(myX) + " ;Y : " + std::to_string(myY) + " ;Z : " + std::to_string(myZ);
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

		std::string ToString()
		{
			return "X : " + std::to_string(myX) + " ;Y : " + std::to_string(myY) + " ;Z : " + std::to_string(myZ) + " ;W : " + std::to_string(myW);
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

	enum UIActionType
	{
		VISIBILITY,
		QUIT,
		POSITION,
	};

	struct UIAction
	{
		UIActionType myActionType;
		UIElement* myElement;
		int myValue1;
		bool myValue2;
		Vector2 myValue3;

		UIAction(UIActionType anActionType, UIElement* anElement, int aValue)
		{
			myActionType = anActionType;
			myElement = anElement;
			myValue1 = aValue;
		}

		UIAction(UIActionType anActionType, UIElement* anElement, bool aValue)
		{
			myActionType = anActionType;
			myElement = anElement;
			myValue2 = aValue;
		}

		UIAction(UIActionType anActionType, UIElement* anElement, Vector2 aValue)
		{
			myActionType = anActionType;
			myElement = anElement;
			myValue3 = aValue;
		}
	};

}