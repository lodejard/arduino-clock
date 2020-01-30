
#pragma once
#include "Arduino.h"

#include "Window.h"
#include "devices/Display.h"
#include "devices/Pointer.h"

class UserInterface
{
    Window* _desktop;

public:
    UserInterface();
    
    virtual Display* display();
    virtual Pointer* pointer();

    Window* desktop();
    void desktop(Window* window);

    void loop();

private:
    void drawRecursive(Window* window, Point origin);
};
