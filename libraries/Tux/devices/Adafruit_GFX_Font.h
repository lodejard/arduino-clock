#pragma once
#include "Arduino.h"
#include "Font.h"
#include "gfxfont.h"

class Adafruit_GFX_Font : public Font
{
    GFXfont* _font;
    int _size;
    TextMetrics _metrics;

public:
    Adafruit_GFX_Font(GFXfont* font, int size);

    GFXfont* font() const {return _font;}
    int size() const {return _size;}

    void measureFont(TextMetrics* metrics);
    void measureCharacter(char ch, TextMetrics* metrics);
};
