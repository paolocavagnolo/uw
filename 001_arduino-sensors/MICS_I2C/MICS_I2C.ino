
#include "DFRobot_MICS.h"       //The library used for this sensor

#define CALIBRATION_TIME   3     // Default calibration time is three minutes

// When using I2C communication, use the following program to construct an object by DFRobot_MICS_I2C
/**
 * select i2c device address 
 * MICS_ADDRESS_0               0x75
 * MICS_ADDRESS_1               0x76
 * MICS_ADDRESS_2               0x77
 * MICS_ADDRESS_3               0x78
 */
#define MICS_I2C_ADDRESS MICS_ADDRESS_0
DFRobot_MICS_I2C mics(&Wire, MICS_I2C_ADDRESS);

void setup() 
{
  Serial.begin(9600);       //Begin serial communication
  

  /**
   * Gets the power mode of the sensor
   * The sensor is in sleep mode when power is on,so it needs to wake up the sensor. 
   * The data obtained in sleep mode is wrong
   */
  uint8_t mode = mics.getPowerState();
  if(mode == SLEEP_MODE){
    mics.wakeUpMode();
    Serial.println("wake up sensor success!");
  }else{
    Serial.println("The sensor is wake up mode");
  }

  /**
   * Do not touch the sensor probe when preheating the sensor.
   * Place the sensor in clean air.
   * The default calibration time is 3 minutes.
   */
  while(!mics.warmUpTime(CALIBRATION_TIME)){
    Serial.println("Please wait until the warm-up time is over!");
    delay(1000);
  }
}

void loop() 
{
  /**
   * Gas type:
   * MICS-4514 You can get all gas concentration
   * MICS-5524 You can get the concentration of CH4, C2H5OH, H2, NH3, CO
   * MICS-2714 You can get the concentration of NO2
   *   CO       = 0x01  (Carbon Monoxide)  (1    - 1000)PPM
   *   CH4      = 0x02  (Methane)          (1000 - 25000)PPM
   *   C2H5OH   = 0x03  (Ethanol)          (10   - 500)PPM
   *   H2       = 0x06  (Hydrogen)         (1    - 1000)PPM
   *   NH3      = 0x08  (Ammonia)          (1    - 500)PPM
   *   NO2      = 0x0A  (Nitrogen Dioxide) (0.1  - 10)PPM
   */
  float gasCH4 = mics.getGasData(CH4);    //THIS LINE READ THE MICS
  float gasC2H5OH = mics.getGasData(C2H5OH);
  float gasH2 = mics.getGasData(H2);
  float gasNH3 = mics.getGasData(NH3);
  float gasCO = mics.getGasData(CO);
  Serial.print(gasCH4,1);
  Serial.print(",");
  Serial.print(gasC2H5OH,1);
  Serial.print(",");
  Serial.print(gasH2,1);
  Serial.print(",");
  Serial.print(gasNH3,1);
  Serial.print(",");
  Serial.print(gasCO,1);
  Serial.println(" PPM");
  delay(1000);
  //mics.sleepMode();
}