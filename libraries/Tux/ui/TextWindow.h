#pragma once
#include "SolidWindow.h"
#include "devices/Font.h"


class TextWindow : public SolidWindow 
{
    Color _textColor;
    Font* _font;
public:
    TextWindow();

    Color textColor() const;
    void textColor(Color color);
    Font* font() const;
    void font(Font* font);
};

class ProgmemTextWindow : TextWindow
{

};
