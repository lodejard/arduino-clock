#include "core/Point.h"

Point::Point(int16_t x, int16_t y):_x(x),_y(y)
{
}

#include "streamFlow.h"
Stream& operator<<(Stream& stream, const Point& v)
{
    return stream
        << F(" x ") << v.x()
        << F(" y ") << v.y();
}
