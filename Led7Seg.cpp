#include "Arduino.h" 
#include "Led7Seg.h"

const byte Led7Seg::_values[15] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111, // 9
  B10000000, // dot
  B01110110, // H
  B00111000, // L
  B01000000, // -
  B00000000 // clear
};

const int _blinkDelay = 500;

Led7Seg::Led7Seg(int a, int b, int c, int d, int e, int f, int g, int dp){
  _a=a;
  _b=b;
  _c=c;
  _d=d;
  _e=e;
  _f=f;
  _g=g;
  _dp=dp;
    
  _segments[0] = _a;
  _segments[1] = _b;
  _segments[2] = _c;
  _segments[3] = _d;
  _segments[4] = _e;
  _segments[5] = _f;
  _segments[6] = _g;
  _segments[7] = _dp;
    
  for(int i=0; i < 8; i++) {
    pinMode(_segments[i], OUTPUT);
  }
  
  _value = _values[sizeof(_values)-1];
  _dot = B0;
  _blink = false;
  _blinkDisplayed = true;
  _lastBlink = 0;
}

void Led7Seg::display(int number){
  if (0 < number < sizeof(_values)-1)
  _value = _values[number] | _dot;
  _display(_value);
}

void Led7Seg::displayL(){
  dot(false);
  display(12);
}

void Led7Seg::displayH(){
  dot(false);
  display(11);
}

void Led7Seg::displayMinus(){
  dot(false);
  display(13);
}

void Led7Seg::displayNothing(){
  display(sizeof(_values)-1);
}

void Led7Seg::clear(){
  _display(_values[sizeof(_values)-1]);
}

void Led7Seg::dot(boolean on){
  if (on) {
    _dot = _values[10];
  } else {
    _dot = B0;
  }
}

void Led7Seg::refresh(){
  unsigned long now = millis();
  if (_blink) {
    if (abs(now - _lastBlink) > _blinkDelay) {
      _lastBlink = now;
      if (_blinkDisplayed) {
	_blinkDisplayed = false;
	clear();
      } else {
	_blinkDisplayed = true;
	_display(_value);
      }
    }
  }
}

void Led7Seg::blink(boolean on) {
  _blink = on;
}

void Led7Seg::_display(byte value){
  for(int i=0; i < 8; i++) {
    if (bitRead(value, i)) {
      digitalWrite(_segments[i],  LOW);
    } else {
      digitalWrite(_segments[i],  HIGH);
    }
  }
}