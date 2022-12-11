#include <Servo.h>

Servo ESC;     // create servo object to control the ESC
Servo m2;

int potValue;  // value from the analog pin

void setup() {
  // Attach the ESC on pin 9
   m3.attach(10,1000,2000);
  m1.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
// (pin, min pulse width, max pulse width in microseconds) 

  // Attempt to arm the speed controller
  m1.write(0);
  delay(500);

  m1.write(90);
  delay(500);

  m1.write(0);
  delay(500);
  
  

  // (pin, min pulse width, max pulse width in microseconds) 
// (pin, min pulse width, max pulse width in microseconds) 

  // Attempt to arm the speed controller
  m3.write(0);
  delay(500);

  m3.write(90);
  delay(500);

   m3.write(0);
  delay(500);
  
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
   
}

void loop() {
  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  // ESC.write(potValue);    // Send the signal to the ESC
  m1.write(120);
  delay(3000);
  m1.write(0);
  delay(1000);
  
  m3.write(120);
  delay(5000);
  m3.write(0);
  delay(10000);

  

  
}
