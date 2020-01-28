#pragma once

#include "DC_Gfx.h"
#include "AFontGfx.h"

#if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
 #define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
#else
 #define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
#endif

class DC_GfxTFT : public DC_Gfx
{
	inline GFXglyph * pgm_read_glyph_ptr(const GFXfont *gfxFont, uint8_t c)
	{
	#ifdef __AVR__
		return &(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c]);
	#else
		// expression in __AVR__ section may generate "dereferencing type-punned pointer will break strict-aliasing rules" warning
		// In fact, on other platforms (such as STM32) there is no need to do this pointer magic as program memory may be read in a usual way
		// So expression may be simplified
		return gfxFont->glyph + c;
	#endif //__AVR__
	}

	GFXfont* _font;
public:
	DC_GfxTFT(Adafruit_GFX* gfx) : DC_Gfx(gfx), _font(NULL) {}

	///Set active font
	virtual void SetFontImpl(AFont *font)
	{
		if (font != NULL)
			SetFont(((AFontGFX *)font)->Font, ((AFontGFX *)font)->Size, ((AFontGFX *)font)->Baseline);
		else 
			SetFont(NULL, 1, 0);
	}

	void SetFont(GFXfont* font, uint8_t size, int8_t baseline)
	{
		_font = font;
		_display->setFont(font);
		_display->setTextSize(size);
		_baseline = baseline;
	}

	int GetTextWidth(const __FlashStringHelper * text)
	{
		if (_font == NULL) {
			return DC_Gfx::GetTextWidth(text);
		}
		int width = 0;
		for(int index = 0; ; ++index) {
			char ch = pgm_read_byte((char*)text + index);
			if (ch == 0) {
				return width;
			}
			width += GetCharacterWidth(ch);
		}
	}

	int GetTextWidth(const char * text)
	{
		if (_font == NULL) {
			return DC_Gfx::GetTextWidth(text);
		}
		int width = 0;
		for (int index = 0; ; ++index) {
			char ch = text[index];
			if (ch == 0) {
				return width;
			}
			width += GetCharacterWidth(ch);
		}
		return width;
	}

	int GetCharacterWidth(char text)
	{
		uint8_t first = pgm_read_byte(&_font->first);
		uint8_t last = pgm_read_byte(&_font->last);

		if (text >= first && text < last) {
			GFXglyph *glyph = pgm_read_glyph_ptr(_font, text - first);
			return pgm_read_byte(&glyph->xAdvance);
		}

		return 0;
	}
	
	static void RegisterDefaultFonts()
	{
		Environment::Get()->RegisterFont(new AFontGFX(F("Big"), NULL, 2));
		Environment::Get()->RegisterFont(new AFontGFX(F("Small"), NULL, 1));
	}	
};

#undef pgm_read_pointer
