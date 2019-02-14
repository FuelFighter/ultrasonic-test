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

int N = 12;

void setup()
{
  
  Serial.begin(9600);
  delay(100);
  
}

void loop()
{
  unsigned long start;
  double measurement = rangeSensorPW1.getRange();
  double sum = measurement;
  double var = 0;
  double avg = 0;
  double sum_square_error = 0;

  Serial.println("Reading...\n");
  
  start = millis();
  for (int i = 2; i < N; i++) { 
    measurement = rangeSensorPW1.getRange();
    sum += measurement;
    avg = sum/i;
    sum_square_error += (measurement-avg)*(measurement-avg);
    delay(10); 
  }
  var = sum_square_error/(N-2);
  
  Serial.print(millis() - start);
  Serial.println("ms\n");
  Serial.print("Mean: ");
  Serial.print(avg);
  Serial.print("\nVariance: ");
  Serial.print(var);
  Serial.print("\nStandard deviation: ");
  Serial.print(sqrt(var));
  Serial.print("");
  Serial.print("\n");
  Serial.print("");
  
  
  
  delay(5000);
}
