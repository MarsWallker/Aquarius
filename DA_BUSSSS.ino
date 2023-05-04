#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include "VL53L1X.h"

#define ONE_WIRE_BUS 8 //external temperature sensor pin

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

//variables for values returned by external temperature sensor
float Celsius = 0;
float Fahrenheit = 0;

//declare a distance sensor
VL53L1X Distance_Sensor;

//variables for pressure sensor
  const float offset = 0.483 ;
  float v , p ;

void setup() {

  sensors.begin();
  

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

  Distance_Sensor.setDistanceMode(VL53L1X::Medium);
  Distance_Sensor.setMeasurementTimingBudget(50000);

  
  Distance_Sensor.startContinuous(50);
} 

void loop() {
  sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celsius);

  Serial.print(Celsius);
  Serial.print(" C  ");
  Serial.print(Fahrenheit);
  Serial.println(" F");

  Distance_Sensor.read();
  Serial.print("Distance(mm): ");
  Serial.print(Distance_Sensor.ranging_data.range_mm);
   Serial.print("\tStatus: ");
  Serial.print(VL53L1X::rangeStatusToString(Distance_Sensor.ranging_data.range_status));
  Serial.println();
      
      
    v = analogRead(0) *  5.00 /  1024 ;
    p = (v - offset ) * 400 ;

  //weird stuff Malia wrote for pressure sensor   
    Serial.print('a');
    Serial.print(analogRead(0));
    Serial.print('b');
    Serial.print(v);
    Serial.print('c');
    Serial.println(p);
      
      
      
  delay(1000);
}
