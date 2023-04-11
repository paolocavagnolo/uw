//
//    FILE: dht22_EASY.ino
//  AUTHOR: Paolo Cavagnolo
// PURPOSE: DHT library test sketch for DHT22 && Arduino - easy version
//

#include "DHTStable.h"    //library used for this sensor

DHTStable DHT;            //here you define the object used to retrieve the data from the sensor

#define DHT22_PIN 5       //here where you plug the sensor

void setup()
{
  Serial.begin(9600);     //start a serial communication
}


void loop()
{

  float hum = DHT.getHumidity();      //READ THE HUMIDITY!
  float temp = DHT.getTemperature()   //READ THE TEMPERATURE!

  // DISPLAY DATA
  Serial.print("H: ")           //PRINT AN "H: "
  Serial.print(hum, 1);         //PRINT the value of humidity
  Serial.print(",\tT: ");       //PRINT ",    T: "
  Serial.println(temp, 1);      //PRINT the value of temperature

  delay(2000);                                //WAIT 2 SECONDS BETWEEN MEASURE
}
