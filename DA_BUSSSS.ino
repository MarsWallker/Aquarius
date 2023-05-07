#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include "VL53L1X.h"
#include <Servo.h>

#define ONE_WIRE_BUS 8 //external temperature sensor pin

byte servo1Pin = 9; // signal pins for the motors.
byte servo2Pin = 10;
byte servo3Pin = 12;
byte servo4Pin = 13;

Servo servo1; Servo servo2; Servo servo3; Servo servo4;

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

//variables for values returned by external temperature sensor
float Celsius = 0;
float Fahrenheit = 0;

//declare a distance sensor
VL53L1X Distance_sensor;


//variables for pressure sensor
  const float offset = 0.483 ;
  float v , p ;

int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {

  sensors.begin();
  

  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  Serial.begin(9600); 
  
  Serial.println("VL53L1X Distance Sensor tests in medium distance mode(up to 3m).");
  Distance_sensor.setTimeout(500);
Distance_sensor.setTimeout(500);
  if (!Distance_sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }

    Distance_sensor.setDistanceMode(VL53L1X::Medium);
  Distance_sensor.setMeasurementTimingBudget(50000);

  
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

void loop() {
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


  while(T > 10.5)
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
    Serial.println(T);

  }


      
      
    v = analogRead(1) *  5.00 /  1024 ;
    p = (v - offset ) * 400 ;

  //weird stuff Malia wrote for pressure sensor   
    Serial.print('a');
    Serial.print(analogRead(1));
    Serial.print('b');
    Serial.print(v);
    Serial.print('c');
    Serial.println(p);

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
  
      
      
  delay(100);
}
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include "VL53L1X.h"
#include <Servo.h>

#define ONE_WIRE_BUS 8 //external temperature sensor pin

byte servo1Pin = 9; // signal pins for the motors.
byte servo2Pin = 10;
byte servo3Pin = 12;
byte servo4Pin = 13;

Servo servo1; Servo servo2; Servo servo3; Servo servo4;

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

//variables for values returned by external temperature sensor
float Celsius = 0;
float Fahrenheit = 0;

//declare a distance sensor
VL53L1X Distance_sensor;


//variables for pressure sensor
  const float offset = 0.483 ;
  float v , p ;

int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {

  sensors.begin();
  

  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  Serial.begin(9600); 
  
  Serial.println("VL53L1X Distance Sensor tests in medium distance mode(up to 3m).");
  Distance_sensor.setTimeout(500);
Distance_sensor.setTimeout(500);
  if (!Distance_sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }

    Distance_sensor.setDistanceMode(VL53L1X::Medium);
  Distance_sensor.setMeasurementTimingBudget(50000);

  
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

void loop() {
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


  while(T > 10.5)
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
    Serial.println(T);

  }


      
      
    v = analogRead(1) *  5.00 /  1024 ;
    p = (v - offset ) * 400 ;

  //weird stuff Malia wrote for pressure sensor   
    Serial.print('a');
    Serial.print(analogRead(1));
    Serial.print('b');
    Serial.print(v);
    Serial.print('c');
    Serial.println(p);

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
  
      
      
  delay(100);
}
