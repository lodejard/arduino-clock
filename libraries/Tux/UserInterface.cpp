
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
    drawRecursive(desktop(), desktop()->origin());
}

void UserInterface::drawRecursive(Window* window, Point origin)
{
    window->draw(display(), origin);
    for(Window* scan = window->child(); scan != NULL; scan = scan->next())
    {
        drawRecursive(scan, origin + scan->origin());
    }
}
