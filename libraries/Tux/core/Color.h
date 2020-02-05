#pragma once
#include "Arduino.h"

class Color {
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;
public:
    Color(uint8_t red, uint8_t green, uint8_t blue);

    uint8_t red();
    void red(uint8_t red);
    uint8_t green();
    void green(uint8_t green);
    uint8_t blue();
    void blue(uint8_t blue);

    uint16_t color565();
    static Color from565(uint16_t color);
};
