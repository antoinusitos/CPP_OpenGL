#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H  
#include <map>
#include <glad/glad.h>
#include "Data.h"

struct GLFWwindow;

namespace Engine
{
	class Shader;

	class TextManager
	{
	public:
		TextManager();
		~TextManager();

		static TextManager* GetInstance();

		void InitText();

		void RenderText(Shader &s, GLFWwindow* aWindow, const std::string aText, GLfloat aX, const GLfloat aY, GLfloat aScale, const Vector3 aColor);

		void RenderText(Shader &s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
		GLFWwindow* myWindow;
		Shader* myShader;

	private:
		static TextManager* mySingleton;

		FT_Library myFontLibrary;
		FT_Face myFontFace;

		std::map<GLchar, Character> myCharacters;

		GLuint myVAO;
		GLuint myVBO;

		//GLFWwindow* myWindow;

		//Shader* myShader;
	};
}