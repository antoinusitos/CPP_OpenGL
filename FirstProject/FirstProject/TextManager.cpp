#include "TextManager.h"
#include "LogManager.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "CameraManager.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "ResourceManager.h"

namespace Engine
{
	TextManager* TextManager::mySingleton = nullptr;

	TextManager::TextManager()
	{
		// init the library
		if (FT_Init_FreeType(&myFontLibrary))
		{
			LogManager::GetInstance()->AddLog("ERROR::FREETYPE: Could not init FreeType Library");
		}

		// init the font
		if (FT_New_Face(myFontLibrary, "Fonts/arial.ttf", 0, &myFontFace))
		{
			LogManager::GetInstance()->AddLog("ERROR::FREETYPE: Failed to load font");
		}

		// set the size of the font
		FT_Set_Pixel_Sizes(myFontFace, 0, 48);

		// create an 8-bit grayscale bitmap image
		if (FT_Load_Char(myFontFace, 'X', FT_LOAD_RENDER))
		{
			LogManager::GetInstance()->AddLog("ERROR::FREETYTPE: Failed to load Glyph");
		}

		//load the first 128 characters of the ASCII table
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

		for (GLubyte c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(myFontFace, c, FT_LOAD_RENDER))
			{
				LogManager::GetInstance()->AddLog("ERROR::FREETYTPE: Failed to load Glyph");
				continue;
			}
			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				myFontFace->glyph->bitmap.width,
				myFontFace->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				myFontFace->glyph->bitmap.buffer
			);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// Now store character for later use
			Character character = {
				texture,
				glm::ivec2(myFontFace->glyph->bitmap.width, myFontFace->glyph->bitmap.rows),
				glm::ivec2(myFontFace->glyph->bitmap_left, myFontFace->glyph->bitmap_top),
				myFontFace->glyph->advance.x
			};
			myCharacters.insert(std::pair<GLchar, Character>(c, character));
		}

		// clean the resources
		FT_Done_Face(myFontFace);
		FT_Done_FreeType(myFontLibrary);

		myShader = ResourceManager::GetInstance()->LoadShader("TextShader", "Text.vert", "Text.frag");

		InitText();
	}

	TextManager::~TextManager()
	{
	}

	TextManager* TextManager::GetInstance()
	{
		if (mySingleton == nullptr)
		{
			mySingleton = new TextManager();
		}

		return mySingleton;
	}

	void TextManager::InitText()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glGenVertexArrays(1, &myVAO);
		glGenBuffers(1, &myVBO);
		glBindVertexArray(myVAO);
		glBindBuffer(GL_ARRAY_BUFFER, myVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void TextManager::RenderText(GLFWwindow* aWindow, const std::string aText, GLfloat aX, const GLfloat aY, GLfloat aScale, const Vector3 aColor)
	{
		// Activate corresponding render state	
		CameraManager::GetInstance()->GetCamera()->Render(myShader, aWindow, true);
		myShader->SetVec3("myTextColor", aColor.myX, aColor.myY, aColor.myZ);

		/*int width, height;
		glfwGetWindowSize(aWindow, &width, &height);

		glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);
		//glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height));
		myShader->SetMat4("myProjection", projection);*/

		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(myVAO);

		// Iterate through all characters
		std::string::const_iterator c;
		for (c = aText.begin(); c != aText.end(); c++)
		{
			Character ch = myCharacters[*c];

			GLfloat xpos = aX + ch.myBearing.x * aScale;
			GLfloat ypos = aY - (ch.mySize.y - ch.myBearing.y) * aScale;

			GLfloat w = ch.mySize.x * aScale;
			GLfloat h = ch.mySize.y * aScale;
			// Update VBO for each character
			GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 1.0 },
				{ xpos,     ypos,       0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 0.0 },

				{ xpos,     ypos + h,   0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 0.0 },
				{ xpos + w, ypos + h,   1.0, 1.0 }
			};


			// Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.myTextureID);
			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, myVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			aX += (ch.myAdvance >> 6) * aScale; // Bitshift by 6 to get value in pixels (2^6 = 64)
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}