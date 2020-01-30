#pragma once

class WindowFactory
{
    static WindowFactory* _instance;
public:
    WindowFactory();

    static WindowFactory* instance();

    Window* NewButton(Window* parent);
};
