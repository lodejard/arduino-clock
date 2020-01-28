#pragma once

#include "Rect.h"
#include "Button.h"
#include "ITouchEventReceiver.h"

class MenuWindow : public Window, ITouchEventReceiver
{
    Label* _toggle;
    Button* _time;
    Button* _date;
    bool _active;

public:
    MenuWindow() : Window(F("menu"), 0, 0, 0, 0)
    {
        AddChild(_toggle = new Label(0,0,0,0, F("settings")));
        _toggle->SetMargins(5, 20);
		_toggle->SetHorizontalAlignment(DC::HorizontalAlignment::Right);

        AddChild(_time = NewButton(80, F("Time")));
        AddChild(_date = NewButton(80, F("Date")));

        _toggle->RegisterTouchEventReceiver(this);
        _time->RegisterTouchEventReceiver(this);		
        _date->RegisterTouchEventReceiver(this);		
    }

    Button* NewButton(int width, const __FlashStringHelper * text)
    {
        Button* wnd = new Button(0, 0, 80, 0, text);
        wnd->SetMargins(2, 5);
        return wnd;
    }

    virtual void Move(int left, int top, int width, int height)
	{
		Window::Move(left, top, width, height);
        
        Rect rc(0, 0, width, height);
        rc.move(_toggle);
        rc.cropLeft(_time->Width()).shrink(2,0,2,0).move(_time);
        rc.cropLeft(_time->Width()).shrink(2,0,2,0).move(_date);
    }

    void SetActive(bool active) {
        _active = active;
        if (active) {
            _time->SetVisible(true);
            _date->SetVisible(true);
        } else {
            _time->SetVisible(false);
            _date->SetVisible(false);
        }
        Invalidate();
    }

    void NotifyTouch(Window *window)
    {
        if (window == _toggle) {
            SetActive(!_active);
        }

        if (window == _time) {
			Dialog* dialog = this->FindDialog(F("Time"));

			this->DoDialog(dialog);

            SetActive(false);
        }
    }
};
