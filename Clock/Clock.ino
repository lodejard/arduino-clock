

#include "SPI.h"
#include "Wire.h"

// Utility
#include "streamFlow.h"
#include "StringPrint.h"

// Real-time clock module
#include "DS3231.h" 

// Speaker synthesizer
#include <synth.h>
#include "notes.h"
#include "song.h"

// TFT Display with touchscreen
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"

// Windows manager
#include "WindowsManager.h"
#include "Log.h"
#include "DefaultDecorators.h"

#include "AWind/DC_GfxTFT.h"
#include "AWind/TouchXPT2046.h"
#include "DSEG14_Classic_Bold_Italic_72.h"
#include "Fonts/FreeSans12pt7b.h"

#include "ClockMainWindow.h"
#include "TimeDialog.h"

#define countof(x) (sizeof(x) / sizeof(*(x)))

#define RGB(r, g, b) (((r/8)<<11) | ((g/4)<<5) | ((b/8)))


#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

//#define TFT_SPI_FREQUENCY 4000000
//#define TFT_SPI_FREQUENCY 6000000
#define TFT_SPI_FREQUENCY 10000000

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC

#define TS_CS 7     //touch screen chip select
#define TS_IRQ 255     //touch screen interrupt


DS3231 clock;
synth speaker;
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen ts(TS_CS, TS_IRQ);


DC_GfxTFT dc(&tft);
TouchXPT2046 touch(&ts);


WindowsManager<ClockMainWindow> windowsManager(&dc, &touch);

void setup()
{
    Serial.begin(115200);
    Serial.println("Alarm Clock"); 

    Wire.begin();
    SPI.begin();
    speaker.begin();
    tft.begin(TFT_SPI_FREQUENCY);
    ts.begin();

    speaker.setupVoice(0,SINE,60,ENVELOPE0,80,64);
    speaker.setupVoice(1,SINE,62,ENVELOPE0,100,64);
    speaker.setupVoice(2,SINE,64,ENVELOPE2,110,64);
    speaker.setupVoice(3,SINE,67,ENVELOPE0,110,64);

    tft.setRotation(3);
    ts.setRotation(1);
    touch.scale(0, 0, tft.width(), tft.height());
    
    //Initialize appearance. Create your own DefaultDecorators class if you would like different application look
    DecoratorList *list=new DecoratorList();
    list->Add(new DecoratorRectFill(Color::Black, false));
    list->Add(new DecoratorColor(Color::LightGray));
    Environment::Get()->RegisterDecoratorsGroup(F("Window"),list);

    list=new DecoratorList();
    list->Add(new DecoratorRectFill(Color::Black, false));
    list->Add(new DecoratorColor(Color(185, 128, 0)));
    Environment::Get()->RegisterDecoratorsGroup(F("Time"),list);

    DefaultDecorators::InitAll();

		Environment::Get()->RegisterFont(new AFontGFX(F("Big"), &FreeSans12pt7b, 1));
		Environment::Get()->RegisterFont(new AFontGFX(F("Small"), NULL, 1));
		Environment::Get()->RegisterFont(new AFontGFX(F("Clock"), &DSEG14_Classic_Bold_Italic_72, 1));

    //initialize window manager
    windowsManager.Initialize();
    windowsManager.MainWnd()->Layout(windowsManager.GetDC());

    TimeDialog* timeDialog = new TimeDialog(20, 40, 255, 150);
    timeDialog->Initialize(&clock);
    windowsManager.MainWnd()->RegisterDialog(F("Time"), timeDialog);
}

uint32_t number = 0;

void loop()
{
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch >= '0' && ch <= '9') {
      number = number * 10 + ch - '0';
    } else if (ch == '\n') {
      Serial << "Setting " << number << endl;
      if (number >= 1000000) {
        clock.setClockMode(false);
      } else {
        clock.setClockMode(true);
      }
      delay(1);
      clock.setHour((number / 10000) % 100);
      clock.setMinute((number / 100) % 100);
      clock.setSecond((number) % 100);
      number = 0;
    }
  }

  bool is12hour, isPM;
  int hour = clock.getHour(is12hour, isPM);
  int minute = clock.getMinute();
  int second = clock.getSecond();

  windowsManager.MainWnd()->SetTime(is12hour, hour, minute, second, isPM);

  windowsManager.loop();

//  playSong(&speaker);
}
