#include <Servo.h>

Servo down_left;     // create servo object to control the ESC
Servo down_right;
Servo turn_left;     // create servo object to control the ESC
Servo turn_right;

int potValue;  // value from the analog pin

void setup() {
  // Attach the ESC on pin 9
   down_left.attach(10,1000,2000);
  down_right.attach(9,1000,2000);
  turn_left.attach(8,1000,2000);
  turn_right.attach(7,1000,2000);// (pin, min pulse width, max pulse width in microseconds) 
// (pin, min pulse width, max pulse width in microseconds) 

  // Attempt to arm the speed controller
  down_left.write(0);
  delay(500);

  down_left.write(90);
  delay(500);

  down_left.write(0);
  delay(500);
  
  

  // (pin, min pulse width, max pulse width in microseconds) 
// (pin, min pulse width, max pulse width in microseconds) 

  // Attempt to arm the speed controller
  down_right.write(0);
  delay(500);

  down_right.write(90);
  delay(500);

   down_right.write(0);
  delay(500);

  /////////////////////////

  turn_left.write(0);
  delay(500);

  turn_left.write(90);
  delay(500);

   turn_left.write(0);
  delay(500);

  //////////////////

  turn_right.write(0);
  delay(500);

  turn_right.write(90);
  delay(500);

   turn_right.write(0);
  delay(500);
  

  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
   
}

void loop() {
  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  // ESC.write(potValue);    // Send the signal to the ESC
  down_left.write(120);
  down_right.write(120);
  delay(1000);
  down_left.write(0);
  down_right.write(0);
  turn_left.write(120);
  turn_right.write(120);

  /*takes a picture */

  delay(1000);

  turn_left.write(0);
  turn_right.write(0);

  delay(2000);
  
  down_left.write(120);
  down_right.write(120);

  delay(1000);

  while(1)
  {
    down_left.write(0);
    down_right.write(0);
    turn_left.write(0);
    turn_right.write(0);
    }
}
