#include "core/Size.h"

Size::Size(uint16_t width, uint16_t height):_cx(width),_cy(height)
{
}

#include "streamFlow.h"
Stream& operator<<(Stream& stream, const Size& v)
{
    return stream
        << F(" width ") << v.width()
        << F(" height ") << v.height();
}
