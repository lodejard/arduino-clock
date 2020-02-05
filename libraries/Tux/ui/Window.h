#pragma once
#include "Arduino.h"
#include "core/Rect.h"
#include "devices/Display.h"

class Window {
    Window* _parent;
    Window* _next;
    Rect _position;
public:
    Window();

    Window* parent();
    void parent(Window* parent);
    Window* next();
    void next(Window* next);
    virtual Window* child();
    virtual void child(Window* child);

    void attach(Window* child);

    const Rect& position();
    virtual void position(const Rect& position);

    inline const Point& origin() const {return _position.origin();}
    inline const Size& size() const {return _position.size();}

    inline int16_t left() {return _position.left();}
    inline int16_t top() {return _position.top();}
    inline uint16_t width() {return _position.width();}
    inline uint16_t height() {return _position.height();}
    int16_t right();
    int16_t bottom();

    virtual void draw(Display* display, Point origin);
};
