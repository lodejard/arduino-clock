#pragma once

#include "Window.h"

class Rect
{
    int16_t _x;
    int16_t _y;
    uint16_t _cx;
    uint16_t _cy;
public:
    Rect():_x(0),_y(0),_cx(0),_cy(0) {}

    Rect(int16_t x, int16_t y, uint16_t width, uint16_t height) {
        _x = x;
        _y = y;
        _cx = width;
        _cy = height;
    }

    int16_t left() {return _x;}
    int16_t right() {return _x + _cx;}
    int16_t top() {return _y;}
    int16_t bottom() {return _y + _cy;}
    uint16_t width() {return _cx;}
    uint16_t height() {return _cy;}

    Rect& shrink(int left, int top, int right, int bottom) {
        _x += left;
        _y += top;
        _cx -= left + right;
        _cy -= top + bottom;
        return *this;
    }

    Rect cropTop(uint16_t height) {
        _y += height;
        _cy -= height;
        return Rect(_x, _y - height, _cx, height); 
    }

    Rect cropLeft(uint16_t width) {
        _x += width;
        _cx -= width;
        return Rect(_x - width, _y, width, _cy); 
    }

    Rect cropRight(uint16_t width) {
        _cx -= width;
        return Rect(_x + _cx, _y, width, _cy); 
    }

    Rect cropBottom(uint16_t height) {
        _cy -= height;
        return Rect(_x, _y + _cy, _cx, height); 
    }

    bool contains(const TS_Point& pt) {
        return pt.x >= _x && pt.x < _x + _cx && pt.y >= _y && pt.y < _y + _cy;
    }

    void move(Window* wnd) {
        wnd->Move(_x, _y, _cx, _cy);
    }
};

