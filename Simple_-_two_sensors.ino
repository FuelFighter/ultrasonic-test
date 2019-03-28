/*
  Maxbotix simple test
  
  Instructions:
  - At least one of: (comment the appropriate code below)
    * PW is digital pin 8
    * TX is digital pin 6
    * AN is analog pin A0
  - Change code below according to your model (LV, XL and
  HRLV supported)
  
  Note:
  For convenience, the getRange method will always return centimeters.
  You can use convert fuctions to convert to another unit (toInches and
  toCentimeters are available)
  
*/
#include "Maxbotix.h"

Maxbotix rangeSensorPW1(8, Maxbotix::PW, Maxbotix::HRLV);
Maxbotix rangeSensorPW2(6, Maxbotix::PW, Maxbotix::HRLV);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  unsigned long start;
  
  Serial.println("Reading...");
  
  // PW1
  start = millis();
  Serial.print("PW1: ");
  Serial.print(rangeSensorPW1.getRange());
  Serial.print("cm - ");
  Serial.print(millis() - start);
  Serial.println("ms");

  start = millis();
  Serial.print("PW2: ");
  Serial.print(rangeSensorPW2.getRange());
  Serial.print("cm - ");
  Serial.print(millis() - start);
  Serial.println("ms");
  
  Serial.println();
  delay(100);
}
