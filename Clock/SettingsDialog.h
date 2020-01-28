#pragma once

#include "Dialog.h"

class SettingsDialog : public Dialog
{
public:
	SettingsDialog(int left,int top,int width,int height):Dialog(F("Settings"),left,top,width,height)
    {
        _btnOK=new Button(0,0,0,0,F("OK"));
		InitButton(_btnOK,60,110,60);
		_btnCancel=new Button(0,0,0,0,F("Cancel"));
		InitButton(_btnCancel,130,110,110);
    }

    void InitButton(Button *btn,int left,int top,int width)
	{
		btn->Move(left,top,width,25);
		btn->SetMargins(5,5);
		btn->RegisterTouchEventReceiver(this);
		AddChild(btn);
	}

    void DoControlMessage(Window *window)
    {
        
    }
};

