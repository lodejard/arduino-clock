#pragma once

#include "Dialog.h"
#include "RadioButton.h"
//#include "TextBoxStrTouch.h"

class TimeDialog : public Dialog, IContentChangedEventReceiver
{
	DS3231* _clock;

	char _oldTime[8];
	char _newTime[24];

	Label  *_oldTimeLabel;
	TextBoxTString<char>  *_oldTimeText;
	Label  *_newTimeLabel;
	TextBoxTString<char>  *_newTimeText;

	RadioButton    *_amControl;
	RadioButton    *_pmControl;
	RadioButton    *_24hControl;
	
public:
	TimeDialog(int left,int top,int width,int height) : Dialog(F("Time"),left,top,width,height)
    {
		_oldTime[0] = 0;
		_newTime[0] = 0;

		AddChild(_oldTimeLabel = new Label(0,0,0,0,F("Current Time:")));
		_oldTimeLabel->SetHorizontalAlignment(DC::HorizontalAlignment::Right);
		AddChild(_oldTimeText = new TextBoxTString<char>(0,0,0,0,_oldTime));

		AddChild(_newTimeLabel = new Label(0,0,0,0,F("Update Time:")));
		_newTimeLabel->SetHorizontalAlignment(DC::HorizontalAlignment::Right);
		AddChild(_newTimeText = new TextBoxTString<char>(0,0,0,0,_newTime));
		_newTimeText->RegisterContentChangedReceiver(this);

		_amControl = NewRadio(F("AM"));
		_pmControl = NewRadio(F("PM"));
		_24hControl = NewRadio(F("24h"));

        _btnOK=NewButton(60, 110, 60, F("OK"));
		_btnCancel=new Button(0,0,0,0,F("Cancel"));
    }

	RadioButton* NewRadio(const __FlashStringHelper * caption)
	{
		RadioButton* radio = new RadioButton(0,0,0,0,caption);
		radio->SetMargins(20, 5);
		radio->RegisterTouchEventReceiver(this);
		AddChild(radio);
		return radio;
	}

    Button* NewButton(int left,int top,int width,const __FlashStringHelper * caption)
	{
		Button* btn = new Button(left, top, width, 25, caption);
		btn->SetMargins(5,5);
		btn->RegisterTouchEventReceiver(this);
		AddChild(btn);
		return btn;
	}

	void Initialize(DS3231* clock) {
		_clock = clock;

		Rect rc(0, 0, Width(), Height());
		rc.shrink(5, 25, 5, 5);
		Rect rcControls;

		rcControls = rc.cropTop(30);
		rcControls.cropLeft(rc.width() / 2).move(_oldTimeLabel);
		rcControls.move(_oldTimeText);

		rcControls = rc.cropTop(30);
		rcControls.cropLeft(rc.width() / 2).move(_newTimeLabel);
		rcControls.move(_newTimeText);

		rcControls = rc.cropTop(30);
		rcControls.cropLeft(rc.width() / 3).move(_amControl);
		rcControls.cropLeft(rc.width() / 3).move(_pmControl);
		rcControls.cropLeft(rc.width() / 3).move(_24hControl);

		rc.cropBottom(30).cropRight(rc.width() / 2).move(_btnOK);
	}

	virtual void SetVisible(bool visible) {
		Dialog::SetVisible(visible);

		if (visible) {
			bool h12, PM;
			int hour = _clock->getHour(h12, PM);
			if (h12 && !PM) {
				SetChecked(_amControl);
			} else if (h12 && PM) {
				SetChecked(_pmControl);
			} else {
				SetChecked(_24hControl);
			}
		}
	}

	void SetChecked(RadioButton* radio) {
		_amControl->SetChecked(radio == _amControl);
		_pmControl->SetChecked(radio == _pmControl);
		_24hControl->SetChecked(radio == _24hControl);
	}

    void DoControlMessage(Window *window)
    {
		bool oldH12, oldPM;
		int old24Hour = _clock->getHour(oldH12, oldPM) % 24;
		if (oldH12) {
			old24Hour = (old24Hour % 12) + (oldPM ? 12 : 0);
		}

        if (window == _amControl) {
			_clock->setClockMode(true);
			_clock->setHour(((old24Hour + 11) % 12) + 1);
			SetChecked(window);
		}
		if (window == _pmControl) {
			_clock->setClockMode(true);
			_clock->setHour(((old24Hour + 11) % 12) + 13);
			SetChecked(window);
		}
		if (window == _24hControl) {
			_clock->setClockMode(false);
			_clock->setHour(old24Hour % 24);
			SetChecked(window);
		}
    }

	void NotifyContentChanged(Window *window) {
		if (window == _newTimeText) {

		}
	}
};

