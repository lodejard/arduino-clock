//Example based on this demo:
//https://github.com/electricmango/Arduino-Music-Project.git
//

//Hardware connections:

//                    +10µF 
//PIN 11 ---[ 1k ]--+---||--->> Audio out
//                  |
//                 === 10nF
//                  |
//                 GND

// DZL 2014
// HTTP://dzlsevilgeniuslair.blogspot.dk
// HTTP://illutron.dk

#include <synth.h>
#include "notes.h"
#include "song.h"

synth edgar;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Song");
  
  edgar.begin();

  edgar.setupVoice(0,SINE,60,ENVELOPE0,80,64);
  edgar.setupVoice(1,SINE,62,ENVELOPE0,100,64);
  edgar.setupVoice(2,SINE,64,ENVELOPE2,110,64);
  edgar.setupVoice(3,SINE,67,ENVELOPE0,110,64);


  for (int thisNote = 0; thisNote < 384; thisNote++) {

    /*
    to calculate the note duration, take one second divided by the note type.
     e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
     */
    int noteDuration = 800/noteDurations[thisNote];
    //    tone(8, melody[thisNote],noteDuration);

    if(melody[thisNote]<=NOTE_E4)
      edgar.mTrigger(1,melody[thisNote]+32);
    else
      edgar.mTrigger(0,melody[thisNote]+32);
    delay(noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    //noTone(8);
  }


  pinMode(6, INPUT);
  Serial.println("Done");
}

void loop() 
{

}


#if 0

// NEW STYLE

/* 16-bit Timer Type B */
typedef struct TCB_struct
{
    register8_t CTRLA;  /* Control A */
    register8_t CTRLB;  /* Control Register B */
    register8_t reserved_0x02;
    register8_t reserved_0x03;
    register8_t EVCTRL;  /* Event Control */
    register8_t INTCTRL;  /* Interrupt Control */
    register8_t INTFLAGS;  /* Interrupt Flags */
    register8_t STATUS;  /* Status */
    register8_t DBGCTRL;  /* Debug Control */
    register8_t TEMP;  /* Temporary Value */
    _WORDREGISTER(CNT);  /* Count */
    _WORDREGISTER(CCMP);  /* Compare or Capture */
    register8_t reserved_0x0E;
    register8_t reserved_0x0F;
} TCB_t;

// NEW USAGE

// CCMPL -- PWM_TIMER_PERIOD (plus one) -- 255 means 256 (Same as OCR2A?) 
// CCMPH -- PWM_TIMER_COMPARE -- (CCMPL + 1) * dutycycle (Same as ORC2B?)

// CTRLA bits 
// 0000 0001 Enable TCB_ENABLE_bm
// 0000 0110 Clock Select TCB_CLKSEL_gm
// 0001 0000 Synchronize Update TCB_SYNCUPD_bm
// 0100 0000 Run Standby TCB_RUNSTDBY_bm

// CTRLB bits 
// 0000 0111 Timer Mode TCB_CNTMODE_gm (000 interrupt, 001 time-out check, 111 PWM)
// 0001 0000 Pin Output Enable TCB_CCMPEN_bm
// 0010 0000 Pin Initial State TCB_CCMPINIT_bm
// 0100 0000 Asynchronous Enable TCB_ASYNC_bm

// OLD USAGE

// OCR2A -- number the timer should count down from
// OCR2B -- number the timer reaches where PWM output switches from low to high

// TCCR1A -- timer/conter 1 control register a
/* TCCR1A */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

// TCCR1B -- timer/conter 1 control register b
/* TCCR1B */
#define ICNC1   7
#define ICES1   6
/* bit 5 reserved */
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

// TCCR1B bits
// 0000 0111 --- clock source (and prescaler selector)

// TCCR1C
#define FOC1C                           5 // Force output compare 
#define FOC1B                           6
#define FOC1A                           7

// TCCR2B
0000 0111 Clock Select
0000 1000 Waveform Generation Mode
0100 0000 Force Output Compare B
1000 0000 Force Output Compare A

struct __reg_TCCR2B {
        unsigned int cs2 : 3;	/* Clock Select */
        unsigned int wgm22 : 1;	/* Waveform Generation Mode */
        unsigned int : 2;
        unsigned int foc2b : 1;	/* Force Output Compare B */
        unsigned int foc2a : 1;	/* Force Output Compare A */
};
#endif