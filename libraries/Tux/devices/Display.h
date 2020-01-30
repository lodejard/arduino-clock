#pragma once
#include "ui/Rect.h"
#include "ui/Color.h"

class Display {
public:
    Display();

    virtual uint16_t width() = 0;
    virtual uint16_t height() = 0;

    virtual Color color() = 0;
    virtual void color(Color color) = 0;
    virtual void fillRect(const Rect& rc) = 0;
};
