#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H  
#include <map>
#include <glad/glad.h>
#include "Data.h"

namespace Engine
{
	class TextManager
	{
	public:
		TextManager();
		~TextManager();

	private:
		FT_Library myFontLibrary;
		FT_Face myFontFace;

		std::map<GLchar, Character> Characters;
	};
}