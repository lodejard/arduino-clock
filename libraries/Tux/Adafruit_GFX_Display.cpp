#include "devices/Adafruit_GFX_Display.h"

Adafruit_GFX_Display::Adafruit_GFX_Display(Adafruit_GFX* device) 
    : _device(device),_font(NULL),_color(0,0,0)
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

Font* Adafruit_GFX_Display::font()
{
    return _font;
}

void Adafruit_GFX_Display::font(Font* font)
{
    _font = (Adafruit_GFX_Font*)font;
    if (_font == NULL) {
        _device->setFont(NULL);
        _device->setTextSize(1);
    } else {
        _device->setFont(_font->font());
        _device->setTextSize(_font->size());
    }
}

Adafruit_GFX_Font g_defaultFont(NULL, 1);

Font* Adafruit_GFX_Display::Adafruit_GFX_Display::defaultFont()
{
    return &g_defaultFont;
}

void Adafruit_GFX_Display::fillRect(const Rect& rc)
{
    _device->fillRect(rc.left(), rc.top(), rc.width(), rc.height(), _color);
}

// void Adafruit_GFX_Display::drawText(const char* text, Point origin)
// {
//     _device->setTextColor(_color);
//     _device->setCursor(origin.x(), origin.y());
//     _device->print(text);
// }

// void Adafruit_GFX_Display::drawText(const __FlashStringHelper* text, Point origin)
// {
//     _device->setTextColor(_color);
//     _device->setCursor(origin.x(), origin.y());
//     _device->print(text);
// }

#include "streamFlow.h"
void Adafruit_GFX_Display::drawText(TextPointer text, Point origin)
{
    _device->setTextColor(_color);
    _device->setCursor(origin.x(), origin.y());
    
    Serial 
        << " text.isFlashString() " << text.isFlashString()
        << endl;

    if (text.isFlashString()) {
        _device->print(text.flashStringPointer());
    } else {
        _device->print(text.stringPointer());
    }
}
