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

#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include "Maxbotix.h"

ros::NodeHandle  nh;

sensor_msgs::Range range_msgL;
ros::Publisher pub_rangeL( "/ultrasoundL", &range_msgL);
char frameidL[] = "/ultrasoundL";

sensor_msgs::Range range_msgR;
ros::Publisher pub_rangeR( "/ultrasoundR", &range_msgR);
char frameidR[] = "/ultrasoundR";

sensor_msgs::Range range_msgC;
ros::Publisher pub_rangeC( "/ultrasoundC", &range_msgC);
char frameidC[] = "/ultrasoundC";

Maxbotix rangeSensorPWL(8, Maxbotix::PW, Maxbotix::HRLV);
Maxbotix rangeSensorPWR(6, Maxbotix::PW, Maxbotix::HRLV);
Maxbotix rangeSensorPWC(7, Maxbotix::PW, Maxbotix::HRLV);


const int N = 10;

const int period = 100;


long range_time = 0;

void setup()
{
  //Initiating nodes
  nh.initNode();
  nh.advertise(pub_rangeL);
  nh.advertise(pub_rangeR);
  nh.advertise(pub_rangeC);



  //Setting up information of range messages
  range_msgL.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msgL.header.frame_id =  frameidL;
  range_msgL.field_of_view = 0.1;  // fake
  range_msgL.min_range = 25.0;
  range_msgL.max_range = 500.0;

  range_msgR.radiation_type = range_msgL.radiation_type;
  range_msgR.header.frame_id =  frameidR;
  range_msgR.field_of_view = range_msgL.field_of_view;
  range_msgR.min_range = range_msgL.min_range;
  range_msgR.max_range = range_msgL.max_range;
  
  range_msgC.radiation_type = range_msgL.radiation_type;
  range_msgC.header.frame_id =  frameidC;
  range_msgC.field_of_view = range_msgL.field_of_view;
  range_msgC.min_range = range_msgL.min_range;
  range_msgC.max_range = range_msgL.max_range;

}

void loop()
{
  if ( millis() >= range_time ){
    range_time = millis() + period;
    
    range_msgL.range = rangeSensorPWL.getRange();
    range_msgR.range = rangeSensorPWR.getRange();
    range_msgC.range = rangeSensorPWC.getRange();

    range_msgL.header.stamp = nh.now();
    range_msgR.header.stamp = range_msgL.header.stamp;
    range_msgC.header.stamp = range_msgL.header.stamp;

    pub_rangeL.publish(&range_msgL);
    pub_rangeR.publish(&range_msgR);
    pub_rangeC.publish(&range_msgC);

  }
  nh.spinOnce();
}
