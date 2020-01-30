
#include "WindowFactory.h"

WindowFactory::_instance;

WindowFactory::WindowFactory()
{

}

WindowFactory* WindowFactory::instance()
{
    return &_instance;
}
