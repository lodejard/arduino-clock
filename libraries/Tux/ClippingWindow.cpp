#include "ui/ClippingWindow.h"

ClippingWindow::ClippingWindow(Color color):_color(color)
{
}

bool verticalClip(Rect* fill, int16_t clipTop, int16_t clipBottom)
{
    if (fill->top() < clipTop) {
        fill->bottom(clipTop);
        return false;
    }
    if (fill->bottom() > clipBottom) {
        fill->bottom(clipBottom);
    }
    return true;
}

bool horizontalClip(Rect* fill, int16_t clipLeft, int16_t clipRight)
{
    if (fill->left() < clipLeft) {
        fill->right(clipLeft);
        return false;
    }
    if (fill->right() > clipRight) {
        fill->right(clipRight);
    }
    return true;
}

void ClippingWindow::draw(Display* display, Point origin)
{
    display->color(_color);

    Rect fill(0, 0, width(), height());
    bool isClipping;
    while(fill.height())
    {
        isClipping = false;
        for(Window* scan = child(); scan != NULL; scan = scan->next())
        {
            if (fill.intersects(scan->position())) 
            {
                isClipping |= verticalClip(&fill, scan->top(), scan->bottom());
            }
        }
        if (!isClipping) 
        {
            display->fillRect(fill + origin);
        }
        else 
        {
            while(fill.width()) 
            {
                isClipping = false;
                for(Window* scan = child(); scan != NULL; scan = scan->next())
                {
                    if (fill.intersects(scan->position())) 
                    {
                        isClipping |= horizontalClip(&fill, scan->left(), scan->right());
                    }
                }
                if (!isClipping) 
                {
                    display->fillRect(fill + origin);
                }
                fill = Rect(fill.right(), fill.top(), width() - fill.right(), fill.height());
            }
        }
        fill = Rect(0, fill.bottom(), width(), height() - fill.bottom());
    }
}
