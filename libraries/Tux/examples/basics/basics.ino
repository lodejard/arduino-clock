
#include "Arduino.h"

#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

//#define TFT_SPI_FREQUENCY 4000000
//#define TFT_SPI_FREQUENCY 6000000
#define TFT_SPI_FREQUENCY 10000000

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC

#define TS_CS 7     //touch screen chip select
#define TS_IRQ 255     //touch screen interrupt


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen ts(TS_CS, TS_IRQ);

#include "tux.h"
#include "ui/UserInterfaceDisplay.h"
#include "ui/ParentWindow.h"
#include "ui/BorderWindow.h"
#include "ui/SolidWindow.h"
#include "ui/ClippingWindow.h"
#include "ui/TextWindow.h"

#include "devices/Adafruit_GFX_Display.h"
#include "devices/Adafruit_GFX_Font.h"

UserInterfaceDisplay<Adafruit_GFX_Display> ui(&tft);

void NewButton(Window* window, Rect rc)
{
    Window* control = new ParentWindow();
    window->attach(control);

    Window* frame1 = new BorderWindow(Color(255,0,0),Color(0,0,0),1);
    control->attach(frame1);

    Window* frame2 = new BorderWindow(Color(255,128,128),Color(128,0,0),1);
    control->attach(frame2);

    Window* red = new TextWindow("Hello World!", NULL, TextAlignment::Center, Color(0,0,0), Color(255,0,0));
    control->attach(red);

    control->position(rc);
    rc = rc.offset(-rc.left(), -rc.top());
    frame1->position(rc);
    frame2->position(rc.shrink(1));
    red->position(rc.shrink(2));
}

#include "Fonts/FreeSansBoldOblique18pt7b.h"

#include "streamFlow.h"

void setup()
{
    Serial.begin(115200);
    tft.begin(TFT_SPI_FREQUENCY);
    ts.begin();

    Serial.println("Basics");

    tft.setRotation(3);
    Serial.println("tft rotation set");
    ts.setRotation(1);
    Serial.println("ts rotation set");

    Window* window = new ClippingWindow(Color(64,64,64));

    NewButton(window, Rect(50,50,75,25));
    NewButton(window, Rect(70,60,75,25));
    NewButton(window, Rect(50,90,75,25));
    NewButton(window, Rect(150,90,75,25));

    Adafruit_GFX_Font* font = new Adafruit_GFX_Font(&FreeSansBoldOblique18pt7b, 1); 

    TextMetrics fontMetrics;
    font->measureFont(&fontMetrics);
    Serial
        << " metrics.verticalAdvance " << fontMetrics.verticalAdvance
        << " metrics.bitmapAboveBaseline " << fontMetrics.bitmapAboveBaseline
        << " metrics.bitmapBelowBaseline " << fontMetrics.bitmapBelowBaseline
        << endl
        << " metrics.horizontalAdvance " << fontMetrics.horizontalAdvance
        << " metrics.horizontalOverhang " << fontMetrics.horizontalOverhang
        << " metrics.horizontalUnderhang " << fontMetrics.horizontalUnderhang
        << endl;

    TextWindow* fancy = new TextWindow(F("Fancy fonts"), font, TextAlignment::TopLeft, Color(255,255,255), Color(64,64,64));
    TextMetrics fancyMetrics;
    font->measureText(fancy->text(), &fancyMetrics);

    Serial
        << " metrics.verticalAdvance " << fancyMetrics.verticalAdvance
        << " metrics.bitmapAboveBaseline " << fancyMetrics.bitmapAboveBaseline
        << " metrics.bitmapBelowBaseline " << fancyMetrics.bitmapBelowBaseline
        << endl
        << " metrics.horizontalAdvance " << fancyMetrics.horizontalAdvance
        << " metrics.horizontalOverhang " << fancyMetrics.horizontalOverhang
        << " metrics.horizontalUnderhang " << fancyMetrics.horizontalUnderhang
        << endl;

    fancy->position(Rect(
        100, 
        150, 
        fancyMetrics.horizontalUnderhang + fancyMetrics.horizontalAdvance + fancyMetrics.horizontalOverhang, 
        fancyMetrics.bitmapAboveBaseline + fancyMetrics.bitmapBelowBaseline));
    window->attach(fancy);

    ui.desktop(window);

    Serial.println("setup complete");
    Serial.flush();
}

void loop()
{
    (Serial<<"loop"<<endl).flush();
    ui.loop();
}
