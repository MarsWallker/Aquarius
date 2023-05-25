#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Servo.h>
#include "VL53L1X.h"
#define ONE_WIRE_BUS 8 //external temperature sensor pin

byte servo1Pin = 0; // signal pins for the motors.
byte servo2Pin = 1;
byte servo3Pin = 2;
byte servo4Pin = 3;

Servo servo1; Servo servo2; Servo servo3; Servo servo4;

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

VL53L1X Distance_sensor;
//variables for values returned by external temperature sensor
float Celsius = 0;
float Fahrenheit = 0;

//declare a distance sensor



//variables for pressure sensor
  const float offset = 0.483 ;
  float v , p ;

int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int lower_motor_one_value, lower_motor_two_value;
int distance;

int onMotors_lower(Servo A, Servo B)
{
 int valA = 0;

  ////motors accelerate throughout 3 seconds

  while(valA < 180)
  {
    A.write(valA);
    B.write(valA);
    Serial.println(valA);
    //Serial.println((valA));
    delay(500);
    
    valA+=1;

  }
  return 0;
}

int onMotors_horizontal(Servo A, Servo B, VL53L1X distance)
{
 int valA = 40;
 int proximity = distance.read(); 
  //motors accelerate throughout 3 seconds

  while(valA < 60)
  {
    A.write(valA);
    B.write(valA + 40);
    Serial.println(valA);
    Serial.println((valA));
    delay(500);
    
    valA+=2;
  proximity = distance.read();
  while(proximity < 500)
  {
    B.write(0);
    delay(2000);
    
    proximity = distance.read();

    if(proximity > 500)
    {
      onMotors_horizontal(A,B,distance);
    }


  }
  

  }
  return 0;
}

void setup() {

  sensors.begin();
  
Distance_sensor.setTimeout(500); 
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  Serial.begin(9600); 
  if (!Distance_sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }
  Distance_sensor.setDistanceMode(VL53L1X::Medium);
  Distance_sensor.setMeasurementTimingBudget(50000);

  
  Distance_sensor.startContinuous(50);

  servo1.attach(servo1Pin);
//servo1.writeMicroseconds(1500);

servo2.attach(servo2Pin);
//servo2.writeMicroseconds(1500);

 servo3.attach(servo3Pin);
//servo3.writeMicroseconds(1500);

servo4.attach(servo4Pin);
//servo4.writeMicroseconds(1500);
} 

void loop() {

  servo3.write(0);
  servo4.write(0);
  sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celsius);

  Serial.print(Celsius);
  Serial.print(" C  ");
  Serial.print(Fahrenheit);
  Serial.println(" F");

   Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature (thermistor): "); 
  Serial.print(T);
  Serial.println(" F"); 

  
 
    v = analogRead(1) *  5.00 /  1024 ;
    p = (v - offset ) * 400 ;

  //weird stuff Malia wrote for pressure sensor   
    Serial.print('a');
    Serial.print(analogRead(1));
    Serial.print('b');
    Serial.print(v);
    Serial.print('c');
    Serial.println(p);

  distance = Distance_sensor.read();

  while(T > 15 || distance < 500)
  {
    servo1.write(0);  
    servo2.write(0);  
    servo3.write(0);
    servo4.write(0); 
    Vo = analogRead(ThermistorPin);
    R2 = R1 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
    T = T - 273.15;
    T = (T * 9.0)/ 5.0 + 32.0; 
    delay(1000);
    Serial.println("Thermistor overheated or distance:");
    Serial.println(T);
    Serial.println(distance);
    distance = Distance_sensor.read();
  }


  onMotors_lower(servo2, servo1);

  delay(2000);
  servo1.write(0);
  servo2.write(0);
 
  servo3.write(0);
  servo4.write(0);
  delay(3000);

  while(T > 15 || distance < 500)
  {
    servo1.write(0);  
    servo2.write(0);  
    servo3.write(0);
    servo4.write(0); 
    Vo = analogRead(ThermistorPin);
    R2 = R1 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
    T = T - 273.15;
    T = (T * 9.0)/ 5.0 + 32.0; 
    delay(1000);
    Serial.println("Thermistor overheated or distance:");
    Serial.println(T);
    Serial.println(distance);
    distance = Distance_sensor.read();
  }
  
   onMotors_horizontal(servo3, servo4, Distance_sensor);
  delay(7000);

 servo1.write(0);
  servo2.write(0);
 
  servo3.write(0);
  servo4.write(0);

  delay(3000);




  Serial.println();
  
      
      
  delay(100);
}
