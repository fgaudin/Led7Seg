#ifndef Led7Seg_h
#define Led7Seg_h

#include "Arduino.h"

class Led7Seg
{
  public:
    Led7Seg(int a, int b, int c, int d, int e, int f, int g, int dp);
    void display(int number);
    void displayL();
    void displayH();
    void displayMinus();
    void displayNothing();
    void clear();
    void dot(boolean on);
    void refresh();
    void blink(boolean on);
  private:
    static const byte _values[15];
    static const int blinkDelay;
    int _a, _b, _c, _d, _e, _f, _g, _dp;
    int _segments[8];
    byte _dot;
    byte _value;
    boolean _blink;
    boolean _blinkDisplayed;
    unsigned long _lastBlink;
    void _display(byte value);
};

#endif  
