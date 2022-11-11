/*
        Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
*/

#include <Servo.h>

Servo ESC;     // create servo object to control the ESC

int potValue;  // value from the analog pin

void setup() {
  // Attach the ESC on pin 9
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC.attach(10,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 

  // Attempt to arm the speed controller
  ESC.write(0);
  delay(500);

  ESC.write(90);
  delay(500);

  ESC.write(0);
  delay(500);
  
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT); 
}

void loop() {
  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  // ESC.write(potValue);    // Send the signal to the ESC
  ESC.write(120);
}
