#include "ui/Rect.h"


Rect::Rect()
    :_origin(0,0),_width(0),_height(0)
{
}

Rect::Rect(int16_t x, int16_t y, uint16_t width, uint16_t height)
    :_origin(x,y),_width(width),_height(height)
{    
}

int16_t Rect::right() const {return _origin.x() + _width;}
int16_t Rect::bottom() const {return _origin.y() + _height;}
void Rect::right(int16_t right) {_width = right - _origin.x();}
void Rect::bottom(int16_t bottom) {_height = bottom - _origin.y();}

bool Rect::intersects(const Rect& rc) const
{
    return 
        _origin.x() < rc._origin.x() + rc._width &&
        _origin.y() < rc._origin.y() + rc._height &&
        _origin.x() + _width > rc._origin.x() &&
        _origin.y() + _height > rc._origin.y();
}

Rect Rect::shrink(int16_t thickness)
{
    return shrink(thickness, thickness, thickness, thickness);
}

Rect Rect::shrink(int16_t left, int16_t top, int16_t right, int16_t bottom)
{
    return Rect(_origin.x() + left, _origin.y() + top, _width - left - right, _height - top - bottom);
}

Rect Rect::offset(int16_t x, int16_t y) 
{
    return Rect(_origin.x() + x, _origin.y() + y, _width, _height);
}

Rect Rect::operator+(const Point& pt) const
{
    return Rect(_origin.x() + pt.x(), _origin.y() + pt.y(), _width, _height);
}
