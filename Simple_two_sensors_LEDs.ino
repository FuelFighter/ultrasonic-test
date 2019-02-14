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

Maxbotix rangeSensorPWL(8, Maxbotix::PW, Maxbotix::HRLV);
Maxbotix rangeSensorPWR(6, Maxbotix::PW, Maxbotix::HRLV);
const int ledPINR = 9;
const int ledPINL = 10;
const int ledPINC = 11;
const float epsilon = 15;
unsigned long pinR=30, pinL=30;
const int N = 10;
 
void setup()
{
  Serial.begin(9600);
  pinMode(ledPINR , OUTPUT);
  pinMode(ledPINL , OUTPUT);
  pinMode(ledPINC , OUTPUT);
  
}
void loop()
{
  unsigned long start;
 
  Serial.println("/nReading...");
  
  pinL=rangeSensorPWL.getRange();
  pinR=rangeSensorPWR.getRange();
  delay(10);
 
  double sumL = pinL;
  double varL = 0;
  double avgL = 0;
  double sum_square_errorL = 0;
  double measurementL = 0;
  
  double sumR = pinR;
  double varR = 0;
  double avgR = 0;
  double sum_square_errorR = 0;
  double measurementR = 0;
  
  start = millis();
  for (int i = 2; i < N; i++) { 
    measurementL = rangeSensorPWL.getRange();
    sumL += measurementL;
    avgL = sumL/i;
    sum_square_errorL += (measurementL-avgL)*(measurementL-avgL);
    
    measurementR = rangeSensorPWR.getRange();
    sumR += measurementR;
    avgR = sumR/i;
    sum_square_errorR += (measurementR-avgR)*(measurementR-avgR);
    delay(10); 
  }
  varR = sum_square_errorR/(N-2);
  varL = sum_square_errorL/(N-2);
  Serial.print("\nAvgR: ");
  Serial.print(avgR);
  Serial.print("\nvarR: ");
  Serial.print(varR);
  Serial.print("\nAvgL: ");
  Serial.print(avgL);
  Serial.print("\nvarL: ");
  Serial.print(varL);

  if (avgL<(avgR-epsilon)) {
    //turn right light on
    digitalWrite(ledPINR , HIGH);   //Pin in HIGH
    digitalWrite(ledPINL , LOW);    //Pin in LOW
    digitalWrite(ledPINC , LOW);    // Pin in LOW
    Serial.println("/nright...");
  }
  else if ((avgL-epsilon)>avgR) {
    //turn left light on
    digitalWrite(ledPINL , HIGH);   //Pin in HIGH
    digitalWrite(ledPINR , LOW);    //Pin in LOW
    digitalWrite(ledPINC , LOW);    // Pin in LOW
   
  }
  else {
    //turn center light on
    digitalWrite(ledPINC , HIGH);   // Pin in HIGH
    digitalWrite(ledPINL , LOW);    //Pin en LOW
    digitalWrite(ledPINR , LOW);    // Pin en LOW
  
  }
}
