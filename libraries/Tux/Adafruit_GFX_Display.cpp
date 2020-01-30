#include "devices/Adafruit_GFX_Display.h"

Adafruit_GFX_Display::Adafruit_GFX_Display(Adafruit_GFX* device) 
    : _device(device)
{   
}

uint16_t Adafruit_GFX_Display::width() {return _device->width();}
uint16_t Adafruit_GFX_Display::height() {return _device->height();}


Color Adafruit_GFX_Display::color()
{
    return Color::from565(_color);
}

void Adafruit_GFX_Display::color(Color color)
{
    _color = color.color565();
}

void Adafruit_GFX_Display::fillRect(const Rect& rc)
{
    _device->fillRect(rc.left(), rc.top(), rc.width(), rc.height(), _color);
}
