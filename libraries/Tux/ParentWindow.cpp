
#include "ui/ParentWindow.h"

ParentWindow::ParentWindow() :
    _child(NULL)
{    
}

Window* ParentWindow::child() {return _child;}
void ParentWindow::child(Window* child) {_child = child;}
