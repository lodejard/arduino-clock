#pragma once

#if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
 #define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
#else
 #define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
#endif

class AFontGFX : public AFont {
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

public:
	AFontGFX(const __FlashStringHelper * fontName, GFXfont* font, uint8_t size) 
		: AFont(fontName), Font(font), Size(size)
	{
		if (font != NULL) {
			uint8_t first = pgm_read_byte(&font->first);
			uint8_t last = pgm_read_byte(&font->last);
			uint8_t yAdvance = pgm_read_byte(&font->yAdvance);

			int8_t top = 0, bottom = 0;

	        for (uint8_t ch = first; ch < last; ++ch) {
				GFXglyph *glyph = pgm_read_glyph_ptr(font, ch - first);

				uint8_t height = pgm_read_byte(&glyph->height);
				int8_t yOffset = pgm_read_byte(&glyph->yOffset);

				if (top > yOffset) {
					top = yOffset;
				}
				if (bottom < yOffset + height) {
					bottom = yOffset + height;
				}

				// Serial 
				// 	<< " ch " << ch
				// 	<< " top " << top
				// 	<< " bottom " << bottom
				// 	<< " yOffset " << yOffset
				// 	<< " height " << height
				// 	<< endl;				
			}

			int cellHeight = bottom - top;
			int rowSpacing = yAdvance - cellHeight;
			Baseline = (-top + (rowSpacing + 1) / 2) * Size;

			Serial 
				<< " yAdvance " << yAdvance
				<< " top " << top
				<< " bottom " << bottom
				<< " cellHeight " << cellHeight
				<< " rowSpacing " << rowSpacing
				<< " Baseline " << Baseline
				<< endl;
		} else {
			Baseline = 0;
		}
	}

	GFXfont* Font;
	int Size;
	int Baseline;
};

#undef pgm_read_pointer
