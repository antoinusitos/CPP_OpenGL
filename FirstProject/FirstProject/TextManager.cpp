#include "TextManager.h"
#include "LogManager.h"

namespace Engine
{
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
	}

	TextManager::~TextManager()
	{
	}
}