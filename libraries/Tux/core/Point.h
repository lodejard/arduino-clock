#pragma once
#include "Arduino.h"

class Point 
{
    int16_t _x;
    int16_t _y;
public:
    Point(int16_t x, int16_t y);

    inline int16_t x() const {return _x;}
    inline void x(int16_t x) {_x = x;}

    inline int16_t y() const {return _y;}
    inline void y(int16_t y) {_y = y;}

    Point operator+(const Point& pt) const {return Point(_x+pt._x,_y+pt._y);}
};

Stream& operator<<(Stream& s,const Point& v);
