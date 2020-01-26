/*
  Text example is intended to demonstrate basics features of AWind library. 

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

//#include "DC_UTFT.h"
//#include "TouchUTFT.h"

#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"
#include "DSEG14_Classic_Bold_Italic_72.h"
#include "Fonts/FreeSans12pt7b.h"

#include "DC_GfxOLED.h"

#include "WindowsManager.h"
#include "Log.h"
#include "TextExampleWindow.h"
#include "DefaultDecorators.h"

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

#define TFT_SPI_FREQUENCY 10000000

#define TOUCH_CS 7     //touch screen chip select
#define TOUCH_IRQ 255     //touch screen interrupt

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen xpt(TOUCH_CS, TOUCH_IRQ);

// // Setup TFT display + touch (see UTFT and UTouch library documentation)
// #ifdef _VARIANT_ARDUINO_DUE_X_   //DUE +tft shield
// UTFT    myGLCD(CTE32,25,26,27,28);
// URTouch  myTouch(6,5,32,3,2);
// //URTouch  myTouch(6, 5, 4, 3, 2);
// #else
// UTFT    myGLCD(ITDB32S,39,41,43,45);
// URTouch  myTouch( 49, 51, 53, 50, 52);
// #endif

class AFontGFX : public AFont {
public:
	AFontGFX(const __FlashStringHelper * fontName, GFXfont* font, uint8_t size) 
		: AFont(fontName), Font(font), Size(size)
	{
	}

	GFXfont* Font;
	int Size;
};

class DC_GfxTFT : public DC_Gfx
{
public:
	DC_GfxTFT(Adafruit_GFX* gfx) : DC_Gfx(gfx) {}

	///Set active font
	virtual void SetFontImpl(AFont *font)
	{
		out << F("SetFontImpl ")<<font->Name<<endln;
		if (font != NULL)
			SetFont(((AFontGFX *)font)->Font, ((AFontGFX *)font)->Size);
		else 
			SetFont(NULL, 1);
	}

	void SetFont(GFXfont* font, uint8_t size)
	{
		out << "font " << (font == NULL ? "null" : " not null");
		out << " size " << size << endln;
		_display->setFont(font);
		_display->setTextSize(size);
	}
	
	static void RegisterDefaultFonts()
	{
		Environment::Get()->RegisterFont(new AFontGFX(F("Big"), &FreeSans12pt7b, 1));
		Environment::Get()->RegisterFont(new AFontGFX(F("Small"), NULL, 1));
	}	
};

class TouchXPT2046 : public Touch
{
	XPT2046_Touchscreen  *_touch;
	int16_t _x0;
	int16_t _y0;
	int16_t _x1;
	int16_t _y1;
	int16_t _x;
	int16_t _y;
	
public:
	TouchXPT2046(XPT2046_Touchscreen *touch):Touch(), _touch(touch)
	{

	}

	void scale(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
	{
		_x0 = x0;
		_y0 = y0;
		_x1 = x1;
		_y1 = y1;
	}

	bool dataAvailable()
	{
		return _touch->touched();
	}
	int16_t getX()
	{
		return _x;
	};
	int16_t getY()
	{
		return _y;
	}
	void read()
	{
		uint16_t x, y;
		uint8_t z;
		_touch->readData(&x, &y, &z);
		_x = ((int32_t)x) * (_x1 - _x0) / 4096 + _x0;
		_y = ((int32_t)y) * (_y1 - _y0) / 4096 + _y0;
	}
};

DC_GfxTFT dc(&tft);
TouchXPT2046 touch(&xpt);

//Windows manager: container for GUI elements 
WindowsManager<TextExampleWindow> windowsManager(&dc, &touch);



void setup()
{
	out.begin(9600);
	out<<F("Setup")<<endln;

	//initialize display
	// myGLCD.InitLCD();
	// myGLCD.clrScr();
	out<<F("Beginning")<<endln;

	tft.begin(TFT_SPI_FREQUENCY);
	xpt.begin();

	tft.setRotation(3);
	xpt.setRotation(1);


	//my speciality I have connected LED-A display pin to the pin 47 on Arduino board. Comment next two lines if the example from UTFT library runs without any problems 
	//pinMode(47,OUTPUT);
	//digitalWrite(47,HIGH);
	//initialize touch
	// myTouch.InitTouch();
	// myTouch.setPrecision(PREC_LOW);
	touch.scale(0, 0, tft.width(), tft.height());

	DC_GfxTFT::RegisterDefaultFonts();
	//Initialize appearance. Create your own DefaultDecorators class if you would like different application look
	DecoratorList *list=new DecoratorList();
	list->Add(new DecoratorRectFill(Color::Black, false));
	list->Add(new DecoratorColor(Color::LightGray));
	Environment::Get()->RegisterDecoratorsGroup(F("Window"),list);

	DefaultDecorators::InitAll();
	//initialize window manager
	windowsManager.Initialize();

	out<<F("End setup")<<endln;

}

void loop()
{

	windowsManager.loop();
}

