#pragma once

#include <TouchEvent.h>
#include "menuDefs.h"

namespace Menu {
    class TS_Rect
    {
        int16_t _x;
        int16_t _y;
        uint16_t _cx;
        uint16_t _cy;
    public:
        TS_Rect(int16_t x, int16_t y, uint16_t width, uint16_t height) {
            _x = x;
            _y = y;
            _cx = width;
            _cy = height;
        }

        int16_t left() {return _x;}
        int16_t right() {return _x + _cx;}
        int16_t top() {return _y;}
        int16_t bottom() {return _y + _cy;}
        uint16_t width() {return _cx;}
        uint16_t height() {return _cy;}

        void shrink(int left, int top, int right, int bottom) {
            _x += left;
            _y += top;
            _cx -= left + right;
            _cy -= top + bottom;
        }

        bool contains(const TS_Point& pt) {
            return pt.x >= _x && pt.x < _x + _cx && pt.y >= _y && pt.y < _y + _cy;
        }
    };

    class TouchEventIn : public menuIn {
        navRoot& root;
        gfxOut& out;
        TS_Point lastPoint;
        int _ch;

        enum  {
            ModeUntouched,
            ModeTouchDown,
            ModeTouchClick
        } mode = ModeUntouched;

    public:
        TouchEventIn(navRoot& root, gfxOut& out):root(root),out(out) {
        }

        size_t write(uint8_t) {
            return 0;
        }

        int available() {
            return (peek() == -1) ? 0 : 1;
        }

        int read() {
            int ch = peek();
            _ch = -1;
            return ch;
        }

        int peek() {
            update();
            return _ch;
        }

        void flush() {

        }

        void update() {
            if (mode == ModeUntouched) {
                return;
            }

            menuNode& activeMenu = root.active();
            panel curPanel = out.panels[out.panels.cur];
            TS_Rect curRect = TS_Rect(
                curPanel.x * out.resX, 
                curPanel.y * out.resY, 
                curPanel.w * out.resX, 
                curPanel.h * out.resY);
            if (root.showTitle) {
                curRect.shrink(0, out.resY, 0, 0);
            }

            if (mode == ModeTouchDown) {
                mode = ModeUntouched;
            }

            if (mode == ModeTouchClick) {
                if (curRect.contains(lastPoint)) {
                    int top = out.top(root.node());
                    int row = top + (lastPoint.y - curRect.top()) / out.resY;

                    if (row < activeMenu.sz() &&
                        root.navFocus->isMenu() && 
                        root.navFocus->canNav())
                    {
                        _ch = '1' + row;
                    }
                }
                mode = ModeUntouched;
            }
        }

        void onTouchDown(TS_Point p) {
            Serial<<"onTouchDown p.x"<<p.x<<" p.y "<<p.y<<endl;

            mode = ModeTouchDown;
            lastPoint = p;
        }

        void onTouchDraw(TS_Point p) {
            // Serial<<"onTouchDraw p.x"<<p.x<<" p.y "<<p.y<<endl;
        }

        void onTouchUp(TS_Point p) {
            Serial<<"onTouchUp p.x"<<p.x<<" p.y "<<p.y<<endl;
        }

        void onTouchClick(TS_Point p) {
            Serial<<"onTouchClick p.x"<<p.x<<" p.y "<<p.y<<endl;

            mode = ModeTouchClick;
            lastPoint = p;
        }

        void onTouchDblClick(TS_Point p) {
            Serial<<"onTouchDblClick p.x"<<p.x<<" p.y "<<p.y<<endl;

            mode = ModeTouchClick;
            lastPoint = p;
        }
    };
}

