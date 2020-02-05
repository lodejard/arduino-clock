#pragma once
#include "Arduino.h"

class TextPointer {
    const uint8_t* _text;
    bool _isFlashString;

public:
    TextPointer(): _text(NULL), _isFlashString(false){}
    TextPointer(const char* text) : _text((const uint8_t*)text), _isFlashString(false) {}
    TextPointer(const __FlashStringHelper* text) : _text((const uint8_t*)text), _isFlashString(true) {}

    bool isFlashString() const {
        return _isFlashString;
    }

    const char* stringPointer() const {
        return (const char*)_text;
    }

    const __FlashStringHelper* flashStringPointer() const {
        return (const __FlashStringHelper*)_text;
    }

    bool operator==(const TextPointer& other) const {
        return 
            (!_isFlashString == !other._isFlashString) &&
            _text == other._text;
    }

    int8_t operator*() const {
        if (_isFlashString) {
            return (uint8_t)pgm_read_byte(_text);
        }
        return *_text;
    }

    TextPointer& operator++() {
        ++_text;
        return *this;
    }    
    
    TextPointer operator++(int) {
        TextPointer tmp(*this);
        operator++();
        return tmp;
    }
};
