#include "PinControl.h"


PinControl::PinControlbyte pin):
  _pin(pin),
  _remFlashes(0)
{ // constructor
  pinMode(_pin, OUTPUT);
  _off();
}

PinControl::PinControl(byte pin, boolean inv):
  _pin(pin),
  _remFlashes(0)
{ // constructor
  pinMode(_pin, OUTPUT);
  inverted = inv;
  _off();
}

void PinControl::update(){
  if (_remFlashes > 0) {
    if ( millis() >= _lastCycleStart + (_flashInt >> 1) ) {
      // toggle LED state
      digitalWrite( _pin, !digitalRead(_pin) );
      _lastCycleStart = millis();
      _remFlashes--;
     }
  } else if (_remFlashes == 0) {
    //
  } else if (_remFlashes < 0) {
    if ( millis() >= _lastCycleStart + (_flashInt >> 1) ) {
      // toggle LED state
      digitalWrite( _pin, !digitalRead(_pin) );
      _lastCycleStart = millis();
    }
  }
}

void PinControl::on(){
  _on();
  _remFlashes = 0;
}

void PinControl::off(){
  _off();
  _remFlashes = 0;
}


void PinControl::flash(int interval){
  flash(interval, -1);
}

void PinControl::flash(int interval, int times){
  _flashInt = interval;
  _remFlashes = times * 2;
  _lastCycleStart = millis(); // remember when we started to flash
}

// wrappers for digital write so we can invert easily
void PinControl::_on(){
  digitalWrite(_pin, HIGH ^ inverted);
}
void PinControl::_off(){
  digitalWrite(_pin, LOW ^ inverted);
}

