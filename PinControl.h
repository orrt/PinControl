#ifndef PinControl_h
#define PinControl_h

#include <Arduino.h>


class PinControl{

public:
  PinControl(byte pin); // contructor
  PinControl(byte pin, boolean inv); // contructor
  void update(); // main entry point, call as often as possible
  void flash(int interval);
  void flash(int interval, int times);
  void on();
  void off();
  void set(boolean st){ if (st) on(); else off(); };  

private:
  const byte _pin;
  int _remFlashes; // how many flashes remain (negative means flash forever)
  int _flashInt; // interval at which LED flashes
  unsigned long _lastCycleStart; // the starttime of each one on/off-period is stored here
  boolean inverted = false;
  void _off();
  void _on();
 
};


#endif 
