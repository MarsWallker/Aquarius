
#include <Wire.h>
#include "VL53L1X.h"
#include <Servo.h>

byte servo1Pin = 9; // signal pins for the motors.
byte servo2Pin = 10;
byte servo3Pin = 12;
byte servo4Pin = 13;

Servo servo1; Servo servo2; Servo servo3; Servo servo4;

VL53L1X Distance_sensor;

void setup()
{
  while (!Serial) {}
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000); 

  Distance_sensor.setTimeout(500);
  if (!Distance_sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }

  Distance_sensor.setDistanceMode(VL53L1X::Medium);
  Distance_sensor.setMeasurementTimingBudget(50000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  Distance_sensor.startContinuous(50);

  servo1.attach(servo1Pin);
servo1.writeMicroseconds(1500);

servo2.attach(servo2Pin);
servo2.writeMicroseconds(1500);

 servo3.attach(servo3Pin);
servo3.writeMicroseconds(1500);

servo4.attach(servo4Pin);
servo4.writeMicroseconds(1500);
}

void loop()
{


  
  Serial.println();


int potVal1 = Distance_sensor.read(); // read input from distance sensor and assign it to a variable that will control the speed of the motors
int potVal2 = Distance_sensor.read();
int potVal3 = Distance_sensor.read(); 
int potVal4 = Distance_sensor.read();



Serial.print("Distance(mm): ");
  Serial.println(potVal1);
  Serial.println(potVal2);
  Serial.println("///////////////");
  int pwmVal2 = map(potVal2,0, 1600, 50, 90); //map the value recieved from distance sensor to the working range of the motors. 
  int pwmVal1 = map(potVal1,0, 1600, 50, 180);
  int pwmVal3 = map(potVal2,0, 1600, 1100, 1800); 
  int pwmVal4 = map(potVal1,0, 1600, 1100, 1800);

Serial.println(pwmVal1); 
Serial.println(pwmVal2);
Serial.println(pwmVal3); 
Serial.println(pwmVal4);

servo1.write(pwmVal1);  //assign the mapped value to the motors
servo2.write(pwmVal2);  
servo3.write(pwmVal3);
servo4.write(pwmVal4);  


  Serial.println();
}
