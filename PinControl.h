#ifndef PinControl_h
#define PinControl_h

#include <Arduino.h>


class PinControl{

public:
  PinControl(byte pin); // contructor
  PinControl(byte pin, boolean inv); // contructor
  void update(); // main entry point, call as often as possible
  void toggle(int interval);
  void toggle(int interval, int times);
  void on();
  void off();
  void set(boolean st){ if (st) on(); else off(); };  

private:
  const byte _pin;
  int _remToggles; // how many toggles remain (negative means toggle forever)
  int _toggleInt; // interval at which pin toggles 
  unsigned long _lastCycleStart; // the starttime of each one on/off-period is stored here
  boolean inverted = false;
  void _off(); // wrappers for digitalWrite taking inverted into account
  void _on();
 
};


#endif 
