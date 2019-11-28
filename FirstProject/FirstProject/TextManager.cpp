#include "TextManager.h"
#include "LogManager.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

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

		glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

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

	void TextManager::RenderText(Shader* aShader, std::string aText, GLfloat aX, GLfloat aY, GLfloat aScale, glm::vec3 aColor)
	{
		// Activate corresponding render state	
		aShader->Use();
		glUniform3f(glGetUniformLocation(aShader->myID, "myTextColor"), aColor.x, aColor.y, aColor.z);
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
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
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