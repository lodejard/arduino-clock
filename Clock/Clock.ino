

#include "SPI.h"
#include "Wire.h"
#include "DS3231.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "DSEG14_Classic_Bold_Italic_72.h"
#include "XPT2046_Touchscreen.h"
// #include "TouchEvent.h"
#include "streamFlow.h"
#include "StringPrint.h"

#include <synth.h>
#include "notes.h"
#include "song.h"


#define countof(x) (sizeof(x) / sizeof(*(x)))

#define RGB(r, g, b) (((r/8)<<11) | ((g/4)<<5) | ((b/8)))

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

//#define TFT_SPI_FREQUENCY 4000000
//#define TFT_SPI_FREQUENCY 6000000
#define TFT_SPI_FREQUENCY 10000000

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

#define TOUCH_CS 7     //touch screen chip select
#define TOUCH_IRQ 255     //touch screen interrupt

XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ);
// TouchEvent tevent(touch);

DS3231 Clock;

synth audio;

void setup()
{
    Serial.begin(115200);
    Serial.println("Alarm Clock"); 

    Wire.begin();
    SPI.begin();
    tft.begin(TFT_SPI_FREQUENCY);
    touch.begin();
    audio.begin();

    audio.setupVoice(0,SINE,60,ENVELOPE0,80,64);
    audio.setupVoice(1,SINE,62,ENVELOPE0,100,64);
    audio.setupVoice(2,SINE,64,ENVELOPE2,110,64);
    audio.setupVoice(3,SINE,67,ENVELOPE0,110,64);

    tft.setRotation(3);
    tft.setFont(&DSEG14_Classic_Bold_Italic_72);
    tft.setTextColor(RGB(185, 128, 0));
    tft.fillScreen(ILI9341_BLACK);

    // tevent.setResolution(tft.width(),tft.height());
    // tevent.setDrawMode(false);
}

struct Current {
  StringPrint<16> text;
  int16_t x = 0;
  int16_t y = 0;
  uint16_t w = 0;
  uint16_t h = 0;
};

Current current;

void loop()
{
  bool is12hour, isPM;
  int hour = Clock.getHour(is12hour, isPM);
  int minute = Clock.getMinute();
  int second = Clock.getSecond();

  StringPrint<16> text;
  if (is12hour) {
    text << (hour < 10 ? " " : "") << hour;
  } else {
    text << hour / 10 << hour % 10;
  }
  text << ":" << minute / 10 << minute % 10;
  if (is12hour) {
    // text << (isPM ? " PM" : " AM");
  }

  if (strcmp(current.text.ptr(), text.ptr())) {
    int16_t x,y;
    uint16_t w,h;
    tft.getTextBounds(text.ptr(), 0, 0, &x, &y, &w, &h);
    int16_t dx = (tft.width() - w) / 2 - x;
    int16_t dy = (tft.height() - h) / 2 - y;
    tft.fillRect(current.x, current.y, current.w, current.h, ILI9341_BLACK);
    tft.setCursor(dx, dy);
    tft.print(text.ptr());
    current.text = text;
    current.x = x + dx;
    current.y = y + dy;
    current.w = w;
    current.h = h;
  }

//  playSong();
}

void onClick(TS_Point p)
{
    tft.fillCircle(p.x, p.y, 10, RGB(64,128,64+128));    
}
