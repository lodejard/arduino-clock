#include "core/Rect.h"

Rect::Rect()
    :_origin(0,0),_size(0,0)
{
}

Rect::Rect(const Point& origin, const Size& size)
    :_origin(origin),_size(size)
{    
}

Rect::Rect(int16_t x, int16_t y, uint16_t width, uint16_t height)
    :_origin(x,y),_size(width,height)
{    
}

int16_t Rect::right() const {return _origin.x() + _size.width();}
int16_t Rect::bottom() const {return _origin.y() + _size.height();}
void Rect::right(int16_t right) {_size.width(right - _origin.x());}
void Rect::bottom(int16_t bottom) {_size.height(bottom - _origin.y());}

bool Rect::intersects(const Rect& rc) const
{
    return 
        _origin.x() < rc._origin.x() + rc._size.width() &&
        _origin.y() < rc._origin.y() + rc._size.height() &&
        _origin.x() + _size.width() > rc._origin.x() &&
        _origin.y() + _size.height() > rc._origin.y();
}

Rect Rect::shrink(int16_t thickness)
{
    return shrink(thickness, thickness, thickness, thickness);
}

Rect Rect::shrink(int16_t left, int16_t top, int16_t right, int16_t bottom)
{
    return Rect(_origin.x() + left, _origin.y() + top, _size.width() - left - right, _size.height() - top - bottom);
}

Rect Rect::offset(int16_t x, int16_t y) 
{
    return Rect(_origin.x() + x, _origin.y() + y, _size.width(), _size.height());
}

Rect Rect::operator+(const Point& pt) const
{
    return Rect(_origin.x() + pt.x(), _origin.y() + pt.y(), _size.width(), _size.height());
}

#include "streamFlow.h"
Stream& operator<<(Stream& stream, const Rect& v)
{
    return stream
        << F(" origin ") << v.origin()
        << F(" size ") << v.size();
}
