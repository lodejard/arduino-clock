#pragma once
#include "TextWindow.h"

class StringTextWindow : public TextWindow
{
    char* _text;
public:
    const char* text() const;
    void text(const char* text);

};
