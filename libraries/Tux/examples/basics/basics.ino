
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
#include "devices/Adafruit_GFX_Display.h"

UserInterfaceDisplay<Adafruit_GFX_Display> ui(&tft);

void NewButton(Window* window, Rect rc)
{
    Window* control = new ParentWindow();
    window->attach(control);

    Window* frame1 = new BorderWindow(Color(255,0,0),Color(0,0,0),1);
    control->attach(frame1);

    Window* frame2 = new BorderWindow(Color(255,128,128),Color(128,0,0),1);
    control->attach(frame2);

    Window* red = new SolidWindow(Color(255,0,0));
    control->attach(red);

    control->position(rc);
    rc = rc.offset(-rc.left(), -rc.top());
    frame1->position(rc);
    frame2->position(rc.shrink(1));
    red->position(rc.shrink(2));
}

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

    ui.desktop(window);

    Serial.println("setup complete");
}

void loop()
{
    ui.loop();
}
