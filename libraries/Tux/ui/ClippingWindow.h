#pragma once
#include "ParentWindow.h"

class ClippingWindow : public ParentWindow {
    Color _color;
public:
    ClippingWindow(Color color);

    void draw(Display* display, Point origin);
};
