#pragma once
#include "Window.h"

class BorderWindow : public Window {
    Color _highlight;
    Color _shadow;
    int8_t _thickness;
public:
    BorderWindow(Color highlight, Color shadow, int8_t thickness);

    void draw(Display* display, Point origin);
};
