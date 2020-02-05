
#pragma once
#include "Arduino.h"
#include "Display.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GFX_Font.h"

class Adafruit_GFX_Display : public Display {
    Adafruit_GFX* _device;
    uint16_t _color;
    Adafruit_GFX_Font* _font;

public:
    Adafruit_GFX_Display(Adafruit_GFX* device);

    virtual uint16_t width();
    virtual uint16_t height();

    virtual Color color();
    virtual void color(Color color);

    virtual Font* font();
    virtual void font(Font* font);

    virtual Font* defaultFont();

    virtual void fillRect(const Rect& rc);
    // virtual void drawText(const char* text, Point origin);
    // virtual void drawText(const __FlashStringHelper* text, Point origin);
    virtual void drawText(TextPointer text, Point origin);

};
