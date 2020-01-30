#pragma once
#include "Arduino.h"
#include "Point.h"

class Rect {
    Point _origin;
    uint16_t _width;
    uint16_t _height;
public:
    Rect();
    Rect(int16_t x, int16_t y, uint16_t width, uint16_t height);

    inline Point origin() const {return _origin;}

    inline int16_t left() const {return _origin.x();}
    inline int16_t top() const {return _origin.y();}
    inline uint16_t width() const {return _width;}
    inline uint16_t height() const {return _height;}
    int16_t right() const;
    int16_t bottom() const;

    inline void left(int16_t left) {_origin.x(left);}
    inline void top(int16_t top) {_origin.y(top);}
    inline void width(int16_t width) {_width = width;}
    inline void height(int16_t height) {_height = height;}
    void right(int16_t right);
    void bottom(int16_t bottom);

    bool intersects(const Rect& rc) const;

    Rect shrink(int16_t thickness);
    Rect shrink(int16_t left, int16_t top, int16_t right, int16_t bottom);
    Rect offset(int16_t x, int16_t y);
    Rect operator+(const Point& pt) const;
};
