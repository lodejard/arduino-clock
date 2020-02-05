
#include "ui/TextWindow.h"

TextWindow::TextWindow():_text(),_font(NULL),_textAlignment(TopLeft),_textColor(0,0,0){}

TextWindow::TextWindow(TextPointer text, Font* font, TextAlignment textAlignment, Color textColor, Color color)
    :_text(text),_font(font),_textAlignment(textAlignment),_textColor(textColor),SolidWindow(color)
{}

TextPointer TextWindow::text() const {return _text;}
void TextWindow::text(TextPointer text) {_text = text;}

Font* TextWindow::font() const {return _font;}
void TextWindow::font(Font* font) {_font = font;}

TextAlignment TextWindow::textAlignment() const {return _textAlignment;}
void TextWindow::textAlignment(TextAlignment textAlignment) {_textAlignment = textAlignment;}

Color TextWindow::textColor() const {return _textColor;}
void TextWindow::textColor(Color color) {_textColor = color;}

void TextWindow::draw(Display* display, Point origin)
{
    SolidWindow::draw(display, origin);

    TextMetrics metrics;
    if (font() != NULL) {
        font()->measureText(text(), &metrics);
    } else {
        display->defaultFont()->measureText(text(), &metrics);
    }

    switch(textAlignment() & (TextAlignment::Left | TextAlignment::Right | TextAlignment::HorizontalCenter))
    {
        case TextAlignment::Left:
        {
            origin.x(origin.x() + (int16_t)metrics.horizontalUnderhang);
            break;
        }
        case TextAlignment::Right:
        {
            origin.x(origin.x() + (int16_t)width() - (int16_t)metrics.horizontalAdvance - (int16_t)metrics.horizontalOverhang);
            break;
        }
        case TextAlignment::HorizontalCenter:
        {
            origin.x(origin.x() + ((int16_t)metrics.horizontalUnderhang + (int16_t)width() - (int16_t)metrics.horizontalAdvance - (int16_t)metrics.horizontalOverhang) / 2);
            break;
        }
    }

    switch(textAlignment() & (TextAlignment::Top | TextAlignment::Bottom | TextAlignment::VerticalCenter))
    {
        case TextAlignment::Top:
        {
            origin.y(origin.y() + (int16_t)metrics.bitmapAboveBaseline);
            break;
        }
        case TextAlignment::Bottom:
        {
            origin.y(origin.y() + (int16_t)height() - (int16_t)metrics.bitmapBelowBaseline);
            break;
        }
        case TextAlignment::VerticalCenter:
        {
            origin.y(origin.y() + ((int16_t)metrics.bitmapAboveBaseline + (int16_t)height() - (int16_t)metrics.bitmapBelowBaseline) / 2);
            break;
        }
    }

    display->font(font());
    display->color(textColor());
    display->drawText(text(), origin);
}
