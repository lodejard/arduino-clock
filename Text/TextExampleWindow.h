/*
  AWind.h - Arduino window library support for Color TFT LCD Boards
  Copyright (C)2014 Andrei Degtiarev. All right reserved
  
  You can find the latest version of the library at 
  https://github.com/AndreiDegtiarev/AWind

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#pragma once

#include "TextBoxString.h"
#include "TextBoxNumber.h"
#include "DecoratorPrimitives.h"

class TextExampleWindow : public MainWindow, ITouchEventReceiver
{
	TextBoxNumber *_textNumber;
	Button* _btnSetup;
public:
	TextExampleWindow(int width,int height):MainWindow(width,height) 
	{
		// AddDecorator(new DecoratorRectFill(Color::Black));
		// AddDecorator(new DecoratorColor(Color::White));
		int x=0;
		int y=40;
		TextBoxFString *label=new TextBoxFString(x,y,width/2,25,F("This is label: "));
		label->SetFont(F("Big"));
		x=width*3.0/4;
		_textNumber=new TextBoxNumber(x,y,width-x-5,25,0);
		//_textNumber->SetDecorators(GetDecorators()); // here we save one decorator because main window and text window have thae same decorator properties: black background
		_textNumber->SetFont(F("Big"));
		_textNumber->SetMargins(5,4);
		_textNumber->SetNumber(4);
		_textNumber->SetIsReadOnly(false);

		AddChild(label);
		AddChild(_textNumber);

		_btnSetup=new Button(0,0,0,0,F("Setup"));
		InitButton(_btnSetup,10,80,80);
	}

	///Create child button
	void InitButton(Button *btn,int left,int top,int width)
	{
		btn->Move(left,top,width,30);
		btn->SetMargins(5,5);
		btn->RegisterTouchEventReceiver(this);
		AddChild(btn);
	}

	void Create()
	{
	}

	void Notify(Window * wnd)
	{
		if(wnd == _textNumber)
		{
			out<<F("Value changed")<<((TextBoxNumber *)_textNumber)->GetNumber()<<endln;
		}
	}
	///Process touch notifications
	void NotifyTouch(Window *window)
	{
		if (window == _btnSetup) {
			out<<F("Setup pressed")<<endln;
		}
	}
};