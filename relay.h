#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>

class Relay
{
  private:
    short int relayPin;

  public:
    Relay(short int _pin); //Default digital pinA = pin 7 och  pinB = pin 8.
    ~Relay();
    void relayOn(); //Relay on.
    void relayOff();
    short int getRelayPin();
    bool getRelayState();

  private:


};

#endif
