#pragma once

#include "MainWindow.h"
#include "ITouchEventReceiver.h"
#include "Label.h"
#include "Rect.h"
#include "MenuWindow.h"

class ClockMainWindow : public MainWindow, ITouchEventReceiver
{
	TextBoxTString<char>* _labelHours;
	Label* _labelColon;
	TextBoxTString<char>* _labelMinutes;
	TextBoxTString<char>* _labelSeconds;
	Label* _labelAmPm;

	bool _is12hour = false;
	int _hour = -1;
	int _minute = -1;
	int _second = -1;
	bool _isPM = false;

	char _hourText[3];
	char _minuteText[3];
	char _secondText[3];

	MenuWindow* _menu;

public:
	ClockMainWindow(int width,int height) : MainWindow(width,height) 
	{
		_hourText[0] = 0;
		_labelHours = new TextBoxTString<char>(0, 0, 0, 0, _hourText, F("Time"));
		_labelHours->SetFont(F("Clock"));
		_labelHours->SetHorizontalAlignment(DC::HorizontalAlignment::Right);
		AddChild(_labelHours);

		_labelColon = new Label(0, 0, 0, 0, F(""));
		_labelColon->SetDecorators(Environment::Get()->FindDecorators(F("Time")));
		_labelColon->SetFont(F("Clock"));
		_labelColon->SetHorizontalAlignment(DC::HorizontalAlignment::Center);
		AddChild(_labelColon);

		_minuteText[0] = 0;
		_labelMinutes = new TextBoxTString<char>(0, 0, 0, 0, _minuteText, F("Time"));
		// _labelMinutes->SetDecorators(Environment::Get()->FindDecorators(F("Time")));
		_labelMinutes->SetFont(F("Clock"));
		AddChild(_labelMinutes);

		_labelAmPm = new Label(0, 0, 0, 0, F(""));
		_labelAmPm->SetDecorators(Environment::Get()->FindDecorators(F("Time")));
		_labelAmPm->SetFont(F("Big"));
		AddChild(_labelAmPm);

		_secondText[0] = 0;
		_labelSeconds = new TextBoxTString<char>(0, 0, 0, 0, _secondText, F("Time"));
		// _labelSeconds->SetDecorators(Environment::Get()->FindDecorators(F("Time")));
		_labelSeconds->SetFont(F("Big"));
		AddChild(_labelSeconds);

		AddChild(_menu = new MenuWindow());
		_menu->SetActive(false);
	}

	void Layout(DC* dc)
	{
		dc->SetFont(Environment::Get()->FindFont(F("Clock")));
		int heightClock = 80; //dc->FontHeight();
		int widthClock = 60; //dc->FontWidth();
		
		dc->SetFont(Environment::Get()->FindFont(F("Big")));
		int heightBig = 29; // dc->FontHeight();
		int widthBig = dc->FontWidth();

		Rect rcScreen(0, 0, Width(), Height());
		Rect rcChild;

		rcScreen.cropTop(20);
		
		Rect rcClock = rcScreen.cropTop(80);

		rcChild = rcClock.cropRight(widthBig * 4);
		rcChild.cropBottom(heightBig).move(_labelAmPm);
		rcChild.cropTop(heightBig).move(_labelSeconds);

		Move(_labelMinutes, rcClock.cropRight(widthClock * 2));
		Move(_labelColon, rcClock.cropRight(widthClock / 3));
		rcClock.cropRight(10); // save space for font overhang
		Move(_labelHours, rcClock.cropRight(widthClock * 2));

		rcScreen.cropBottom(heightBig + 6).move(_menu);
	}

	void Move(Window* wnd, const Rect& rc)
	{
		wnd->Move(rc.left(), rc.top(), rc.width(), rc.height());
	}

	void SetTime(bool is12hour, int hour, int minute, int second, bool isPM) 
	{
		if (!is12hour) {
			isPM = false;
		}

		if (_is12hour == is12hour &&
			_hour == hour &&
			_minute == minute &&
			_second == second &&
			_isPM == isPM) 
			{
			return;
		}

		Serial 
			<< " is12hour " << is12hour 
			<< " hour " << hour 
			<< " minute " << minute 
			<< " second " << second 
			<< " isPM " << isPM 
			<< endl;

		if (_is12hour != is12hour || _hour != hour) {
			if (!is12hour) {
				_hourText[0] = '0' + (hour / 10);
				_hourText[1] = '0' + (hour % 10);
			} else {
				int displayHour = ((hour + 11) % 12) + 1;
				if (displayHour < 10) {
					_hourText[0] = '0' + (displayHour % 10);	
					_hourText[1] = 0;
				} else {
					_hourText[0] = '1';
					_hourText[1] = '0' + (displayHour % 10);	
				}
			}
			_hourText[2] = 0;
			_labelHours->SetText(_hourText);
		}

		if (_minute != minute) {
			_minuteText[0] = '0' + (minute / 10);
			_minuteText[1] = '0' + (minute % 10);
			_minuteText[2] = 0;
			_labelMinutes->SetText(_minuteText);
		}

		if (_second != second) {
			_labelColon->SetText((_second & 1) ? F("") : F(":"));
			_secondText[0] = '0' + (second / 10);
			_secondText[1] = '0' + (second % 10);
			_secondText[2] = 0;
			_labelSeconds->SetText(_secondText);
		}

		if (_is12hour != is12hour || _isPM != isPM) {
			if (!is12hour) {
				_labelAmPm->SetText(F(""));
			} else if (isPM) {
				_labelAmPm->SetText(F("PM"));
			} else {
				_labelAmPm->SetText(F("AM"));
			}
		}

		_is12hour = is12hour;
		_hour = hour;
		_minute = minute;
		_second = second;
		_isPM = isPM;
	}

	void Notify(Window * wnd)
	{
	}

	void NotifyTouch(Window *wnd)
	{
	}
};
