/*
  Maxbotix simple test

  Instructions:
  - At least one of: (comment the appropriate code below)
      PW is digital pin 8
      TX is digital pin 6
      AN is analog pin A0
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
Maxbotix rangeSensorPWC(7, Maxbotix::PW, Maxbotix::HRLV);

const int ledPINR = 9;
const int ledPINL = 10;
const int ledPINC = 11;

const float epsilon = 15;
unsigned long pinR = 30, pinL = 30, pinC = 30;
const int N = 10;
const int center_distance_threshold = 50;

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
  int measurment_listL[N];
  int measurment_listR[N];
  int measurment_listC[N];
  int xL = 0, xR = 0, xC = 0;
  Serial.println("/nReading...");

  pinL = rangeSensorPWL.getRange();
  pinR = rangeSensorPWR.getRange();
  pinC = rangeSensorPWC.getRange();
  measurment_listL[0] = pinL;
  measurment_listR[0] = pinR;
  measurment_listC[0] = pinC;

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

  double sumC = pinC;
  double varC = 0;
  double avgC = 0;
  double sum_square_errorC = 0;
  double measurementC = 0;

  start = millis();
  for (int i = 1; i < N; i++) {
    
    measurementL = rangeSensorPWL.getRange();
    sumL += measurementL;
    measurment_listL[i] = measurementL;

    measurementR = rangeSensorPWR.getRange();
    sumR += measurementR;
    measurment_listR[i] = measurementR;

    measurementC = rangeSensorPWC.getRange();
    sumC += measurementC;
    measurment_listC[i] = measurementC;

    delay(10);
  }

  avgL = sumL / N;
  avgR = sumR / N;
  avgC = sumC / N;

  for (int v = 0; v < N; v++) {
    xL = measurment_listL[v];
    sum_square_errorL += (xL - avgL) * (xL - avgL);

    xR = measurment_listR[v];
    sum_square_errorR += (xR - avgR) * (xR - avgR);

    xC = measurment_listC[v];
    sum_square_errorC += (xC - avgC) * (xC - avgC);
  }

  varR = sum_square_errorR / N;
  varL = sum_square_errorL / N;
  varC = sum_square_errorC / N;

  Serial.print("\nAvgR: ");
  Serial.print(avgR);
  Serial.print("\nvarR: ");
  Serial.print(varR);

  Serial.print("\nAvgL: ");
  Serial.print(avgL);
  Serial.print("\nvarL: ");
  Serial.print(varL);

  Serial.print("\nAvgC: ");
  Serial.print(avgC);
  Serial.print("\nvarC: ");
  Serial.print(varC);

  if (avgC > center_distance_threshold) {
    //turn center light on
    digitalWrite(ledPINC , HIGH);   // Pin in HIGH
    digitalWrite(ledPINL , LOW);    //Pin en LOW
    digitalWrite(ledPINR , LOW);    // Pin en LOW
  }
  else if (avgL < (avgR - epsilon)) {
    
    //turn right light on
    digitalWrite(ledPINR , HIGH);   //Pin in HIGH
    digitalWrite(ledPINL , LOW);    //Pin in LOW
    digitalWrite(ledPINC , LOW);    // Pin in LOW
    Serial.println("/nright...");
  }
  else if ((avgL - epsilon) > avgR)  {
    //turn left light on
    digitalWrite(ledPINL , HIGH);   //Pin in HIGH
    digitalWrite(ledPINR , LOW);    //Pin in LOW
    digitalWrite(ledPINC , LOW);    // Pin in LOW
    Serial.println("/nleft...");
  }
}
