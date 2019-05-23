## ultrasonic-test
### Purpose
Basic Arduino code to check the variance and test the ultrasionic sensors.



### Getting started
- Download libraries for use [teensy Arduino](https://www.pjrc.com/teensy/td_download.html) following all the steps in the web page
- Download the [library for the ultrasonic sensors](https://playground.arduino.cc/Main/MaxSonar/)

### Connections information
- Connect every pin with the correct pin in the ultrasonic sensor
- [Datasheet ultrasonic sensor](https://www.maxbotix.com/documents/HRLV-MaxSonar-EZ_Datasheet.pdf)
- [Pins information Teensy 3.2](https://www.pjrc.com/teensy/card7a_rev1.pdf)


[download the Arduino program](https://www.arduino.cc/en/Main/Software)

### Little Explication for each code

#### Measure_of_variance
Added file that measures variance

#### Simple__two_sensors
Simple code example from the Teensy and adapted for 2 sensors. It reads the cm of right and left and then is showed in the monitor.

#### Simple_two_sensors_LEDs
Simple code example with two sensors(right and left) and 3 LEDs(right, left and central).

#### Simple_three_sensors_LEDs
Simple code example  adapted for 3 sensors and 3 LEDs. The cm are showed in the monitor.

#### Three_sensors_3LEDs
Code calculation and comparing with three sensors and 3 LEDs(right, left and central)

#### 1D-ex-rosserial
Single sensor ros file

#### Three_sensor_ros
Publishes in Ros distance for all three ultrasonic sensors
