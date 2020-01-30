#include "ui/Color.h"

Color::Color(uint8_t red, uint8_t green, uint8_t blue)
:_red(red),_green(green),_blue(blue)
{    
}

    uint8_t Color::red() {return _red;}
    void Color::red(uint8_t red) {_red = red;}
    uint8_t Color::green() {return _green;}
    void Color::green(uint8_t green) {_green = green;}
    uint8_t Color::Color::blue() {return _blue;}
    void Color::blue(uint8_t blue) {_blue = blue;}

uint16_t Color::color565()
{
    return 
        ((uint16_t)(_red & 0b11111000) << 8) |
        ((uint16_t)(_green & 0b11111100) << 3) |
        ((_blue) >> 3);
}


Color Color::from565(uint16_t color)
{
    return Color(
        color >> 11,
        (color >> 5) & 0b111111,
        color & 0b11111);
}
