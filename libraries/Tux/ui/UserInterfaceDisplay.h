
#pragma once

#include "Arduino.h"
#include "UserInterface.h"

template<class TDisplay>
class UserInterfaceDisplay:public UserInterface
{
    TDisplay _display;
public:
    UserInterfaceDisplay(const TDisplay& display) : _display(display) {}
    virtual Display* display() {return &_display;}
};
