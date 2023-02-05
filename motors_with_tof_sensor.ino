/*
  Reading distance from the laser based VL53L1X
  By: kaloha
  CQRobot
  VL53L1X Distance Sensor from CQRobot: http://www.cqrobot.wiki/index.php/VL53L1X_Distance_Sensor
  This example demonstrates how to read the distance in medium mode(up to 4m) and the measurement status.
*/

#include <Wire.h>
#include "VL53L1X.h"
#include <Servo.h>

byte servoPin = 9; // signal pin for the ESC.
byte potentiometerPin = A0; // analog input pin for the potentiometer.
Servo servo;


VL53L1X Distance_Sensor;

void setup()
{
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  Serial.begin(9600);
  Serial.println("VL53L1X Distance Sensor tests in medium distance mode(up to 3m).");
  Distance_Sensor.setTimeout(500);
  if (!Distance_Sensor.init())
  {
    Serial.println("Failed to initialize VL53L1X Distance_Sensor!");
    while (1);
  }

  
  
  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 33 ms for medium and long distance mode
  Distance_Sensor.setDistanceMode(VL53L1X::Medium);
  Distance_Sensor.setMeasurementTimingBudget(50000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  Distance_Sensor.startContinuous(50);

  servo.attach(servoPin);
servo.writeMicroseconds(1500);
}

void loop()
{
  Distance_Sensor.read();
  Serial.print("Distance(mm): ");
  Serial.print(Distance_Sensor.ranging_data.range_mm);
   Serial.print("\tStatus: ");
  Serial.print(VL53L1X::rangeStatusToString(Distance_Sensor.ranging_data.range_status));
  Serial.println();

  servo.writeMicroseconds(1100);
servo.writeMicroseconds(0);

int potVal = analogRead(Distance_Sensor.ranging_data.range_mm); // read input from distance sensor.

  int pwmVal = map(potVal,0, 1500, 1100, 1900); //map the value recieved from distance sensor to the working range of the motors. 

servo.writeMicroseconds(pwmVal);  
delay(20);
}
