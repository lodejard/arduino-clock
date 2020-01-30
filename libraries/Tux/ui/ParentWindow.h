#pragma once

#include "Window.h"

class ParentWindow : public Window {
    Window* _child;
public:
    ParentWindow();
    virtual Window* child();
    virtual void child(Window* child);
};
