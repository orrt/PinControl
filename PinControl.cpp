#include "PinControl.h"


PinControl::PinControl(byte pin):
  _pin(pin),
  _remToggles(0)
{ 
  pinMode(_pin, OUTPUT);
  _off();
}

PinControl::PinControl(byte pin, boolean inv):
  _pin(pin),
  _remToggles(0)
{ 
  pinMode(_pin, OUTPUT);
  inverted = inv;
  _off();
}

void PinControl::update(){
  if (_remToggles > 0) {
    if ( millis() >= _lastCycleStart + (_toggleInt >> 1) ) {
      // toggle pin 
      digitalWrite( _pin, !digitalRead(_pin) );
      _lastCycleStart = millis();
      _remToggles--;
     }
  } else if (_remToggles == 0) {
    //
  } else if (_remToggles < 0) {
    if ( millis() >= _lastCycleStart + (_toggleInt >> 1) ) {
      // toggle LED state
      digitalWrite( _pin, !digitalRead(_pin) );
      _lastCycleStart = millis();
    }
  }
}

void PinControl::on(){
  _on();
  _remToggles = 0;
}

void PinControl::off(){
  _off();
  _remToggles = 0;
}

void PinControl::toggle(int interval){
  toggle(interval, -1);
}

void PinControl::toggle(int interval, int times){
  _toggleInt = interval;
  _remToggles = times * 2;
  _lastCycleStart = millis(); // remember when we started to flash
}

// wrappers for digital write so we can invert easily
void PinControl::_on(){
  digitalWrite(_pin, HIGH ^ inverted);
}
void PinControl::_off(){
  digitalWrite(_pin, LOW ^ inverted);
}

