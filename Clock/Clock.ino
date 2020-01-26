

#include "SPI.h"
#include "Wire.h"
#include "DS3231.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "DSEG14_Classic_Bold_Italic_72.h"
#include "XPT2046_Touchscreen.h"
#include "TouchEvent.h"
#include "streamFlow.h"
#include "StringPrint.h"


#ifdef MENU_STUFF
#include <menu.h>

#include <menuIO/adafruitGfxOut.h>

//#include <menuIO/encoderIn.h>
#include <menuIO/keyIn.h>
#include <menuIO/chainStream.h>
#include <menuIO/serialOut.h>
#include <menuIO/serialIn.h>

#include "TouchEventIn.h"
#endif 


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
TouchEvent tevent(touch);

DS3231 Clock;


#ifdef MENU_STUFF

#define MAX_DEPTH 4
#define textScale 4

char* constMEM hexDigit MEMMODE="0123456789ABCDEF";
char* constMEM hexNr[] MEMMODE={"0","x",hexDigit,hexDigit};
char buf1[]="0x11";

//customizing a prompt look!
//by extending the prompt class
class altPrompt:public prompt {
public:
  altPrompt(constMEM promptShadow& p):prompt(p) {}
  Used printTo(navRoot &root,bool sel,menuOut& out, idx_t idx,idx_t len,idx_t) override {
    return out.printRaw(F("special prompt!"),len);;
  }
};


int selTest=0;
SELECT(selTest,selMenu,"Select",doNothing,noEvent,noStyle
  ,VALUE("Zero",0,doNothing,noEvent)
  ,VALUE("One",1,doNothing,noEvent)
  ,VALUE("Two",2,doNothing,noEvent)
);

int chooseTest=-1;
CHOOSE(chooseTest,chooseMenu,"Choose",doNothing,noEvent,noStyle
  ,VALUE("First",1,doNothing,noEvent)
  ,VALUE("Second",2,doNothing,noEvent)
  ,VALUE("Third",3,doNothing,noEvent)
  ,VALUE("Last",-1,doNothing,noEvent)
);

MENU(subMenu,"Sub-Menu",doNothing,noEvent,noStyle
  ,altOP(altPrompt,"",doNothing,noEvent)
  ,OP("Op",doNothing,noEvent)
  ,EXIT("<Back")
);

MENU(mainMenu,"Main menu",doNothing,noEvent,wrapStyle
  ,OP("Op1",doNothing,noEvent)
  ,OP("Op2",doNothing,noEvent)
  ,SUBMENU(subMenu)
//   ,SUBMENU(setLed)
//   ,OP("LED On",myLedOn,enterEvent)
//   ,OP("LED Off",myLedOff,enterEvent)
  ,SUBMENU(selMenu)
  ,SUBMENU(chooseMenu)
  //,OP("Alert test",doAlert,enterEvent)
  //,EDIT("Hex",buf1,hexNr,doNothing,noEvent,noStyle)
  ,EXIT("<Back")
);

//when menu is suspended
result idle(menuOut& o,idleEvent e) {
  if (e==idling) {
    o.println(F("suspended..."));
    o.println(F("press [select]"));
    o.println(F("to continue"));
  }
  return proceed;
}

namespace ClockMenu {

////////////////////////////////
// Menu --- Forward declarations

extern Menu::navRoot nav;

////////////////////////////////
// Menu --- Outputs

const colorDef<uint16_t> colors[6] MEMMODE={
  {{(uint16_t)ILI9341_BLACK,(uint16_t)ILI9341_BLACK}, {(uint16_t)ILI9341_BLACK, (uint16_t)ILI9341_BLUE,  (uint16_t)ILI9341_BLUE}},//bgColor
  {{(uint16_t)ILI9341_DARKGREY, (uint16_t)ILI9341_DARKGREY},  {(uint16_t)ILI9341_WHITE, (uint16_t)ILI9341_WHITE, (uint16_t)ILI9341_WHITE}},//fgColor
  {{(uint16_t)ILI9341_WHITE,(uint16_t)ILI9341_BLACK}, {(uint16_t)ILI9341_YELLOW,(uint16_t)ILI9341_YELLOW,(uint16_t)ILI9341_RED}},//valColor
  {{(uint16_t)ILI9341_WHITE,(uint16_t)ILI9341_BLACK}, {(uint16_t)ILI9341_WHITE, (uint16_t)ILI9341_YELLOW,(uint16_t)ILI9341_YELLOW}},//unitColor
  {{(uint16_t)ILI9341_WHITE,(uint16_t)ILI9341_DARKGREY},  {(uint16_t)ILI9341_BLACK, (uint16_t)ILI9341_BLUE,  (uint16_t)ILI9341_WHITE}},//cursorColor
  {{(uint16_t)ILI9341_WHITE,(uint16_t)ILI9341_YELLOW},{(uint16_t)ILI9341_BLUE,  (uint16_t)ILI9341_RED,   (uint16_t)ILI9341_RED}},//titleColor
};

Menu::idx_t serialOut_tops[MAX_DEPTH];
Menu::serialOut serialOut(Serial, serialOut_tops);

constMEM Menu::panel adaGfxOut_panels[] MEMMODE = {
  {0, 0, 14, 8}, 
  {14, 0, 14, 8}
};
Menu::navNode* adaGfxOut_navNodes[countof(adaGfxOut_panels)];
Menu::panelsList adaGfxOut_panelsList(adaGfxOut_panels, adaGfxOut_navNodes, countof(adaGfxOut_panels));
Menu::idx_t adaGfxOut_tops[MAX_DEPTH];
Menu::adaGfxOut adaGfxOut(tft, colors, adaGfxOut_tops, adaGfxOut_panelsList, 12, 18);

Menu::menuOut* const outputs_menuOuts[] MEMMODE = {
  &serialOut, 
  &adaGfxOut
};
Menu::outputsList outputs(outputs_menuOuts, countof(outputs_menuOuts));

////////////////////////////////
// Menu --- Inputs

Menu::serialIn serialIn(Serial);

Menu::TouchEventIn touchEventIn(nav, adaGfxOut);

template<TouchEventIn& tei> void onTouchDown(TS_Point p) {tei.onTouchDown(p);}
template<TouchEventIn& tei> void onTouchDraw(TS_Point p) {tei.onTouchDraw(p);}
template<TouchEventIn& tei> void onTouchUp(TS_Point p) {tei.onTouchUp(p);}
template<TouchEventIn& tei> void onTouchClick(TS_Point p) {tei.onTouchClick(p);}
template<TouchEventIn& tei> void onTouchDblClick(TS_Point p) {tei.onTouchDblClick(p);}

template<TouchEvent& te, TouchEventIn& tei>
void connect() 
{
  te.registerOnTouchDown(onTouchDown<tei>);
  te.registerOnTouchDraw(onTouchDraw<tei>);
  te.registerOnTouchUp(onTouchUp<tei>);
  te.registerOnTouchClick(onTouchClick<tei>);
  te.registerOnTouchDblClick(onTouchDblClick<tei>);
}

Menu::menuIn* inputs_menuIns[] = {
  &serialIn,
  &touchEventIn
};
Menu::chainStream<countof(inputs_menuIns)> inputs(inputs_menuIns);

////////////////////////////////
// Menu --- Navigation

Menu::navNode nav_navNodes[MAX_DEPTH];
Menu::navRoot nav(mainMenu, nav_navNodes, MAX_DEPTH, inputs, outputs);

}
#endif

void setup()
{
    Serial.begin(115200);
    Serial.println("Alarm Clock"); 

    Wire.begin();
    SPI.begin();
    tft.begin(TFT_SPI_FREQUENCY);
    touch.begin();

#ifdef MENU_STUFF
    ClockMenu::nav.showTitle = false;
    ClockMenu::nav.idleTask = idle;//point a function to be used when menu is suspended
    ClockMenu::connect<tevent, ClockMenu::touchEventIn>();
#endif

    tft.setRotation(3);
    tft.setFont(&DSEG14_Classic_Bold_Italic_72);
//    tft.setTextSize(2);
    tft.setTextColor(RGB(185, 128, 0));
    tft.fillScreen(ILI9341_BLACK);

    tevent.setResolution(tft.width(),tft.height());
    tevent.setDrawMode(false);
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
#ifdef MENU_STUFF
  // poll for menu
  ClockMenu::nav.poll();
#endif

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

  //poll for touch events
  tevent.pollTouchScreen();
}

void onClick(TS_Point p)
{
    tft.fillCircle(p.x, p.y, 10, RGB(64,128,64+128));    
}
