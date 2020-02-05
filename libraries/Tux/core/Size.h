#pragma once
#include "Arduino.h"

class Size
{
    uint16_t _cx;
    uint16_t _cy;
public:
    Size(uint16_t width, uint16_t height);

    inline uint16_t width() const {return _cx;}
    inline void width(uint16_t width) {_cx = width;}

    inline uint16_t height() const {return _cy;}
    inline void height(uint16_t height) {_cy = height;}

    Size& operator+=(const Size& pt) {_cx += pt._cx; _cy += pt._cy; return *this;}
    Size operator+(const Size& pt) const {return Size(_cx + pt._cx, _cy + pt._cy);}
};

Stream& operator<<(Stream& s,const Size& v);
