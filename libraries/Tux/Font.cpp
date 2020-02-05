#include "Arduino.h"
#include "devices/font.h"

Font::Font()
{
}

#include "streamFlow.h"

void Font::measureText(TextPointer text, TextMetrics* metrics)
{
    measureFont(metrics);
    metrics->horizontalAdvance = 0;
    metrics->horizontalUnderhang = 0;
    metrics->horizontalOverhang = 0;

    TextPointer scan = text;
    for(uint8_t ch = *scan; ch != 0; ch = *(++scan)) 
    {
        Serial << (char)ch;

        TextMetrics cm;
        measureCharacter(ch, &cm);
        metrics->horizontalAdvance += cm.horizontalAdvance;
        if (scan == text) {
            metrics->horizontalUnderhang = cm.horizontalUnderhang;
        }
        metrics->horizontalOverhang = cm.horizontalOverhang;
    }
    Serial << endl;
}

// void Font::measureText(const char* text, TextMetrics* metrics)
// {
//     measureFont(metrics);
//     metrics->horizontalAdvance = 0;
//     metrics->horizontalUnderhang = 0;
//     metrics->horizontalOverhang = 0;

//     const char* scan = text;
//     for(uint8_t ch = (uint8_t)*(scan); ch != 0; ch = (uint8_t)*(++scan)) 
//     {
//         TextMetrics cm;
//         measureCharacter(ch, &cm);
//         metrics->horizontalAdvance += cm.horizontalAdvance;
//         if (scan == text) {
//             metrics->horizontalUnderhang = cm.horizontalUnderhang;
//         }
//         metrics->horizontalOverhang = cm.horizontalOverhang;
//     }
// }

// void Font::measureText(const __FlashStringHelper* text, TextMetrics* metrics)
// {
//     measureFont(metrics);
//     metrics->horizontalAdvance = 0;
//     metrics->horizontalUnderhang = 0;
//     metrics->horizontalOverhang = 0;

//     const char* scan = (const char*)text;
//     for(uint8_t ch = (uint8_t)pgm_read_byte(scan); ch != 0; ch = (uint8_t)pgm_read_byte(++scan)) 
//     {
//         TextMetrics cm;
//         measureCharacter(ch, &cm);
//         metrics->horizontalAdvance += cm.horizontalAdvance;
//         if (scan == text) {
//             metrics->horizontalUnderhang = cm.horizontalUnderhang;
//         }
//         metrics->horizontalOverhang = cm.horizontalOverhang;
//     }
// }
