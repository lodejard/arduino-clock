#pragma once
#include "TextWindow.h"

class FlashStringTextWindow : public TextWindow
{
    const __FlashStringHelper *_text;

public:
    FlashStringTextWindow();
    
    const char *text() const;
    void text(const char *text);
};
