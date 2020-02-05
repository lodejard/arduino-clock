#pragma once
#include "core/TextPointer.h"

struct TextMetrics
{
    uint8_t verticalAdvance;
    int8_t bitmapAboveBaseline;
    int8_t bitmapBelowBaseline;
    uint16_t horizontalAdvance;
    int8_t horizontalOverhang;
    int8_t horizontalUnderhang;
};

class Font
{
public:
    Font();

    virtual void measureFont(TextMetrics* metrics) = 0;
    virtual void measureCharacter(char ch, TextMetrics* metrics) = 0;
    virtual void measureText(TextPointer text, TextMetrics* metrics);
    // virtual void measureText(const char* text, TextMetrics* metrics);
    // virtual void measureText(const __FlashStringHelper* text, TextMetrics* metrics);
};
