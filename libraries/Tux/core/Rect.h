#pragma once
#include "Arduino.h"
#include "Point.h"
#include "Size.h"

class Rect {
    Point _origin;
    Size _size;
public:
    Rect();
    Rect(const Point& origin, const Size& size);
    Rect(int16_t x, int16_t y, uint16_t width, uint16_t height);

    inline const Point& origin() const {return _origin;}
    inline void origin(const Point& origin) {_origin = origin;}

    inline const Size& size() const {return _size;}
    inline void size(const Size& size) {_size = size;}

    inline int16_t left() const {return _origin.x();}
    inline int16_t top() const {return _origin.y();}
    inline uint16_t width() const {return _size.width();}
    inline uint16_t height() const {return _size.height();}
    int16_t right() const;
    int16_t bottom() const;

    inline void left(int16_t left) {_origin.x(left);}
    inline void top(int16_t top) {_origin.y(top);}
    inline void width(uint16_t width) {_size.width(width);}
    inline void height(uint16_t height) {_size.height(height);}
    void right(int16_t right);
    void bottom(int16_t bottom);

    bool intersects(const Rect& rc) const;

    Rect shrink(int16_t thickness);
    Rect shrink(int16_t left, int16_t top, int16_t right, int16_t bottom);
    Rect offset(int16_t x, int16_t y);

    Rect operator+(const Point& pt) const;
};

Stream& operator<<(Stream& s,const Rect& v);
