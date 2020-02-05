
#include "ui/UserInterface.h"
#include "streamFlow.h"

UserInterface::UserInterface()
    :_desktop(NULL)
{
}

Display* UserInterface::display() {return NULL;}
Pointer* UserInterface::pointer() {return NULL;}
Window* UserInterface::desktop() {return _desktop;}

void UserInterface::desktop(Window* window) {
    _desktop = window;

    // resize desktop once attached
    _desktop->position(Rect(0, 0, display()->width(), display()->height()));
}

void UserInterface::loop()
{
    Point origin = desktop()->origin();
    drawRecursive(desktop(), origin);
}

#include "streamFlow.h"
void UserInterface::drawRecursive(Window* window, Point origin)
{
    Serial
        << F(" drawRecursive window ") << hex(window)
        << F(" position ") << window->position()
        << endl;

    window->draw(display(), origin);
    for(Window* scan = window->child(); scan != NULL; scan = scan->next())
    {
        drawRecursive(scan, origin + scan->origin());
    }
}
