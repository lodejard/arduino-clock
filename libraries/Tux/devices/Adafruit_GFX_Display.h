
#pragma once
#include "Arduino.h"
#include "Display.h"
#include "Adafruit_GFX.h"

class Adafruit_GFX_Display : public Display {
    Adafruit_GFX* _device;
    uint16_t _color;
public:
    Adafruit_GFX_Display(Adafruit_GFX* device);

    virtual uint16_t width();
    virtual uint16_t height();

    virtual Color color();
    virtual void color(Color color);
    virtual void fillRect(const Rect& rc);
};
