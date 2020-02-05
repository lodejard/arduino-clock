#pragma once
#include "SolidWindow.h"
#include "core/TextPointer.h"
#include "devices/Font.h"
#include "TextAlignment.h"

class TextWindow : public SolidWindow 
{
    TextPointer _text;
    Font* _font;
    Color _textColor;
    TextAlignment _textAlignment;

public:
    TextWindow();
    TextWindow(TextPointer text, Font* font, TextAlignment textAlignment, Color textColor, Color color);

    TextPointer text() const;
    void text(TextPointer text);

    Font* font() const;
    void font(Font* font);

    TextAlignment textAlignment() const;
    void textAlignment(TextAlignment textAlignment);

    Color textColor() const;
    void textColor(Color color);

    void draw(Display* display, Point origin);
};
