#include "ui/Window.h"

Window::Window()
:_parent(NULL),_next(NULL)
{
}

Window* Window::parent() {return _parent;}
void Window::parent(Window* window) {_parent = window;}
Window* Window::next() {return _next;}
void Window::next(Window* window) {_next = window;}
Window* Window::child() {return NULL;}
void Window::child(Window* window) { /* TODO: throw exception */ }

void Window::attach(Window* window)
{
    Window* currentChild = child();
    if (currentChild == NULL) {
        child(window);
    } else {
        Window* nextChild = currentChild->next();
        while (nextChild != NULL) {
            currentChild = nextChild;
            nextChild = currentChild->next();
        }
        currentChild->next(window);
    }
    window->parent(this);
}

const Rect& Window::position() {return _position;}
void Window::position(const Rect& position) {_position = position;}

int16_t Window::right() {return _position.right();}
int16_t Window::bottom() {return _position.bottom();}

void Window::draw(Display* display, Point location)
{
}
