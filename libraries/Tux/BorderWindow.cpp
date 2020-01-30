#include "ui/BorderWindow.h"

BorderWindow::BorderWindow(Color highlight, Color shadow, int8_t thickness)
: _highlight(highlight), _shadow(shadow), _thickness(thickness)
{
}

void BorderWindow::draw(Display* display, Point origin)
{
    display->color(_highlight);
    display->fillRect(Rect(origin.x(), origin.y(), width(), _thickness));
    display->fillRect(Rect(origin.x(), origin.y() + _thickness, _thickness, height() - _thickness));
    display->color(_shadow);
    display->fillRect(Rect(origin.x() + _thickness, origin.y() + height() - _thickness, width() - _thickness, _thickness));
    display->fillRect(Rect(origin.x() + width() - _thickness, origin.y() + _thickness, _thickness, height() - _thickness * 2));
}
