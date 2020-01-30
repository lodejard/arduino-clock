#include "ui/SolidWindow.h"

SolidWindow::SolidWindow(Color color)
: _color(color)
{
}

void SolidWindow::draw(Display* display, Point origin)
{
    display->color(_color);
    display->fillRect(Rect(origin.x(), origin.y(), width(), height()));
}
