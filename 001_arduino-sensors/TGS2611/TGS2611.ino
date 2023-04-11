#define TGS2611_PIN A1
#define TGS_CALIBRATION_TIME 3

float R0 = 0;
float Rs = 0;
float RL = 1000; //OHM

float VC = 5;
float VRL = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while(millis() < TGS_CALIBRATION_TIME * 60000) {
    Serial.println("TGS CALIBRATION ONGOING. WAIT PLEASE.");
  }

  //Get the data of R0 just after the calibration
  VRL = map(analogRead(TGS2611_PIN),0,1024,0,5);
  R0 = ((VC - VRL)/VRL) * RL;
}

void loop() {
  // put your main code here, to run repeatedly:
  VRL = map(analogRead(TGS2611_PIN),0,1024,0,5);
  Rs = ((VC - VRL)/VRL) * RL;

  Serial.print("Rs: ");
  Serial.print(Rs);
  Serial.print(", Beta: ");
  Serial.println(Rs/R0);

  delay(2000); //Delay between measure
}
