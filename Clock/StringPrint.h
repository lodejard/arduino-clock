
#pragma once

template<int BUFFER_SIZE>
class StringPrint : public Stream
{
  char _buf[BUFFER_SIZE];
  int _index;
public:
  StringPrint() {
    _buf[0] = 0;
    _index = 0;
  }
  void init() {
    _index = 0;
  }
  virtual size_t write(uint8_t ch) {
    if (_index == sizeof(_buf) - 1) {
      return 0;
    }
    _buf[_index++] = ch;
    return 1;
  }
  const char* ptr() {_buf[_index] = 0; return _buf;}

    int available() {return 0;}
    int read() {return -1;}
    int peek() {return -1;}
    void flush() {}

};
