#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int pin = 9;
int pos = 0;  // variable to store the servo position

void setup() {
  Serial.begin(9600);
  myservo.attach(pin);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 0; pos <= 360; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Serial.println(pos);
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(30);           // waits 15ms for the servo to reach the position
  }
  for (pos = 360; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    Serial.println(pos);
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(30);           // waits 15ms for the servo to reach the position
  }
}