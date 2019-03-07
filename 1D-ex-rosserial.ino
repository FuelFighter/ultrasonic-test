

#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include "Maxbotix.h"

ros::NodeHandle  nhL;
sensor_msgs::Range range_msgL;
ros::Publisher pub_rangeL( "/ultrasoundL", &range_msgL);
char frameidL[] = "/ultrasoundL";


Maxbotix rangeSensorPWL(8, Maxbotix::PW, Maxbotix::HRLV);

const int period = 100;

long range_time = 0;

void setup()
{
  //Initiating nodes
  nhL.initNode();
  nhL.advertise(pub_rangeL);



  //Setting up information of range messages
  range_msgL.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msgL.header.frame_id =  frameidL;
  range_msgL.field_of_view = 0.1;  // fake
  range_msgL.min_range = 25.0;
  range_msgL.max_range = 500.0;

}

void loop()
{
  if ( millis() >= range_time ){
    range_time = millis() + period;
    
    range_msgL.range = rangeSensorPWL.getRange();
    range_msgL.header.stamp = nhL.now();
    pub_rangeL.publish(&range_msgL);
  }
  nhL.spinOnce();
}
