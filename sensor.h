#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class Sensor
{
  private:
    const short int ONE_WIRE_BUS = 2;
    OneWire oneWire;
    DallasTemperature sensTemp;
    float celcius;

  public:
    Sensor();
    ~Sensor(); //Destructor.
    float getTemp();
};

#endif
