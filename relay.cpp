#include "relay.h"

//Constructors
Relay::Relay(short int _pin)
  : relayPin(_pin)
{
  pinMode(relayPin, OUTPUT);
}

Relay::~Relay()
{
}

void Relay::relayOn()
{
  digitalWrite(relayPin, HIGH);
}

void Relay::relayOff()
{
  digitalWrite(relayPin, LOW);
}

short int Relay::getRelayPin()
{
  return relayPin;
}

bool Relay::getRelayState()
{
  return digitalRead(relayPin);
}
