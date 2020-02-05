#pragma once
#include "core/Color.h"
#include "core/Rect.h"
#include "core/TextPointer.h"
#include "devices/Font.h"

class Display {
public:
    Display();

    virtual uint16_t width() = 0;
    virtual uint16_t height() = 0;

    virtual Color color() = 0;
    virtual void color(Color color) = 0;

    virtual Font* font() = 0;
    virtual void font(Font* font) = 0;

    virtual Font* defaultFont() = 0;
    
    virtual void fillRect(const Rect& rc) = 0;
    // virtual void drawText(const char* text, Point origin) = 0;
    // virtual void drawText(const __FlashStringHelper* text, Point origin) = 0;
    virtual void drawText(TextPointer text, Point origin) = 0;
};
