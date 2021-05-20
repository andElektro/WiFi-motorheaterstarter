#include "sensor.h"



Sensor::Sensor()
  : oneWire(ONE_WIRE_BUS), sensTemp(&oneWire)
{
  //Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
  //Pass our oneWire reference to Dallas Temperature.
  sensTemp.begin(); //Start up the library
  sensTemp.setResolution(9);
}

Sensor::~Sensor()
{
}

float Sensor::getTemp(){
  sensTemp.requestTemperatures(); //Send the command to get temperatures
  celcius = sensTemp.getTempCByIndex(0); //We use the function ByIndex, and 0 is the first sensor.
  return celcius;
}
