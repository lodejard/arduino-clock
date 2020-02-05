#pragma once
#include "Window.h"

class SolidWindow : public Window {
    Color _color;
public:
    SolidWindow();
    SolidWindow(Color color);

    inline Color color() {return _color;}
    void color(Color color);

    void draw(Display* display, Point origin);
};
