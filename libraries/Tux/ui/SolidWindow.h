#pragma once
#include "Window.h"

class SolidWindow : public Window {
    Color _color;
public:
    SolidWindow(Color color);

    void draw(Display* display, Point origin);
};
