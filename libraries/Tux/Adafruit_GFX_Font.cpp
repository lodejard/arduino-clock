#include "devices/Adafruit_GFX_Font.h"

Adafruit_GFX_Font::Adafruit_GFX_Font(GFXfont* font, int size)
:_font(font),_size(size)
{
    _metrics.verticalAdvance = 0;
    _metrics.bitmapAboveBaseline = 0;
    _metrics.bitmapBelowBaseline = 0;
    _metrics.horizontalAdvance = 0;
    _metrics.horizontalUnderhang = 0;
    _metrics.horizontalOverhang = 0;

    if (font != NULL) {
        _metrics.verticalAdvance = (uint8_t)pgm_read_byte(&_font->yAdvance);

        int8_t first = (uint8_t)pgm_read_byte(&_font->first);
        int8_t last = (uint8_t)pgm_read_byte(&_font->last);

        for (int ch = first; ch != last; ++ch) {
            TextMetrics cm;
            measureCharacter(ch, &cm);
            if (_metrics.bitmapAboveBaseline < cm.bitmapAboveBaseline)
                _metrics.bitmapAboveBaseline = cm.bitmapAboveBaseline;
            if (_metrics.bitmapBelowBaseline < cm.bitmapBelowBaseline)
                _metrics.bitmapBelowBaseline = cm.bitmapBelowBaseline;
            if (_metrics.horizontalAdvance < cm.horizontalAdvance)
                _metrics.horizontalAdvance = cm.horizontalAdvance;
            if (_metrics.horizontalUnderhang < cm.horizontalUnderhang)
                _metrics.horizontalUnderhang = cm.horizontalUnderhang;
            if (_metrics.horizontalOverhang < cm.horizontalOverhang)
                _metrics.horizontalOverhang = cm.horizontalOverhang;
        }
    } else {
        _metrics.verticalAdvance = 8;
        _metrics.bitmapBelowBaseline = 8;
        _metrics.horizontalAdvance = 6;
    }
}

void Adafruit_GFX_Font::measureFont(TextMetrics* metrics)
{
    *metrics = _metrics;
}

// Pointers are a peculiar case...typically 16-bit on AVR boards,
// 32 bits elsewhere.  Try to accommodate both...

#if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
#define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
#else
#define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
#endif

inline GFXglyph *pgm_read_glyph_ptr(const GFXfont *gfxFont, uint8_t c) {
#ifdef __AVR__
  return &(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c]);
#else
  // expression in __AVR__ section may generate "dereferencing type-punned
  // pointer will break strict-aliasing rules" warning In fact, on other
  // platforms (such as STM32) there is no need to do this pointer magic as
  // program memory may be read in a usual way So expression may be simplified
  return gfxFont->glyph + c;
#endif //__AVR__
}

void Adafruit_GFX_Font::measureCharacter(char ch, TextMetrics* metrics)
{
    if (_font == NULL) {
        metrics->verticalAdvance = 8;
        metrics->bitmapAboveBaseline = 0;
        metrics->bitmapBelowBaseline = 8;
        metrics->horizontalAdvance = 6;
        metrics->horizontalUnderhang = 0;
        metrics->horizontalOverhang = 0;
        return;
    }
    
    int8_t first = (uint8_t)pgm_read_byte(&_font->first);
    GFXglyph* glyph = pgm_read_glyph_ptr(_font, ch - first);

    uint8_t width = (uint8_t)pgm_read_byte(&glyph->width);
    uint8_t height = (uint8_t)pgm_read_byte(&glyph->height);
    uint8_t xAdvance = (uint8_t)pgm_read_byte(&glyph->xAdvance);
    uint8_t xOffset = (uint8_t)pgm_read_byte(&glyph->xOffset);
    int8_t yOffset = (int8_t)pgm_read_byte(&glyph->yOffset);

    metrics->verticalAdvance = _metrics.verticalAdvance;
    metrics->bitmapAboveBaseline = -yOffset;
    metrics->bitmapBelowBaseline = height + yOffset;
    metrics->horizontalAdvance = xAdvance;
    metrics->horizontalUnderhang = -xOffset;
    metrics->horizontalOverhang = width + xOffset - xAdvance;
}
