#include "LEDctl.h"


LEDctl::LEDctl(byte pin):
  _pin(pin),
  _remFlashes(0)
{ // constructor
  pinMode(_pin, OUTPUT);
  _off();
}

LEDctl::LEDctl(byte pin, boolean inv):
  _pin(pin),
  _remFlashes(0)
{ // constructor
  pinMode(_pin, OUTPUT);
  inverted = inv;
  _off();
}

void LEDctl::update(){
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

void LEDctl::on(){
  _on();
  _remFlashes = 0;
}

void LEDctl::off(){
  _off();
  _remFlashes = 0;
}


void LEDctl::flash(int interval){
  flash(interval, -1);
}

void LEDctl::flash(int interval, int times){
  _flashInt = interval;
  _remFlashes = times * 2;
  _lastCycleStart = millis(); // remember when we started to flash
}

// wrappers for digital write so we can invert easily
void LEDctl::_on(){
  digitalWrite(_pin, HIGH ^ inverted);
}
void LEDctl::_off(){
  digitalWrite(_pin, LOW ^ inverted);
}

