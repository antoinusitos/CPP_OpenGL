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

		void RenderText(Shader* aShader, GLFWwindow* aWindow, std::string aText, GLfloat aX, GLfloat aY, GLfloat aScale, glm::vec3 aColor);

	private:
		static TextManager* mySingleton;

		FT_Library myFontLibrary;
		FT_Face myFontFace;

		std::map<GLchar, Character> myCharacters;

		GLuint myVAO;
		GLuint myVBO;
	};
}