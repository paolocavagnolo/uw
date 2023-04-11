//
//    FILE: Sensors_for_Jake.ino
//  AUTHOR: Paolo Cavagnolo
//

#include "DHTStable.h"          //library used for DHT22
#include "DFRobot_MICS.h"       //The library used for this sensor

#define DHT22_PIN 5               //here where you plug the sensor
#define MICS_CALIBRATION_TIME   3      // Default calibration time is three minutes

DHTStable DHT;            //here you define the object used to retrieve the data from the sensor

// When using the Breakout version, use the following program to construct an object from DFRobot_MICS_ADC
/**
 * adcPin is A0~A5
 * powerPin is General IO
 */
#define ADC_PIN   A0
#define POWER_PIN 10
DFRobot_MICS_ADC mics(ADC_PIN, POWER_PIN);

#define TGS2611_PIN A1
#define TGS_CALIBRATION_TIME 3


float R0 = 0;
float Rs = 0;
float RL = 1000; //OHM

float VC = 5;
float VRL = 0;


void setup()
{
  Serial.begin(9600);     //start a serial communication

  uint8_t mode = mics.getPowerState();
  if(mode == SLEEP_MODE){
    mics.wakeUpMode();
    Serial.println("wake up sensor success!");
  }else{
    Serial.println("The sensor is wake up mode");
  }

  while(!mics.warmUpTime(MICS_CALIBRATION_TIME)){
    Serial.println("Please wait until the warm-up time is over!");
    delay(1000);
  }
  while(millis() < TGS_CALIBRATION_TIME * 60000) {
    Serial.println("TGS CALIBRATION ONGOING. WAIT PLEASE.");
  }
  //Get the data of R0 just after the calibration
  VRL = map(analogRead(TGS2611_PIN),0,1024,0,5);
  R0 = ((VC - VRL)/VRL) * RL;
}


void loop()
{
  VRL = map(analogRead(TGS2611_PIN),0,1024,0,5);
  Rs = ((VC - VRL)/VRL) * RL;

  // DISPLAY DATA
  Serial.print("H: ");                       
  Serial.print(DHT.getHumidity(), 1);         
  Serial.print(",\tT: ");                     
  Serial.print(DHT.getTemperature(), 1);      
  Serial.print(",\tCH4: ");                
  Serial.print(mics.getGasData(CH4), 1);      
  Serial.print(",\tC2H5OH: ");                
  Serial.print(mics.getGasData(C2H5OH), 1);   
  Serial.print(",\tNH3: ");                
  Serial.print(mics.getGasData(NH3), 1);         
  Serial.print(",\tCO: ");                     
  Serial.print(mics.getGasData(CO), 1); 
  Serial.print(",\tRs: ");
  Serial.print(Rs);
  Serial.print(",\tBeta: ");
  Serial.println(Rs/R0);     

  delay(2000);                                //WAIT 2 SECONDS BETWEEN MEASURE
}
