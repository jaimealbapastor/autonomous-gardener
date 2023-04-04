## Rapports de séance Brice Mabille

- 04/04/2023 : Setup du projet GitHub partagé

# Séance 19

During this session, I linked the servo. 

I made the arduino code:

````arduino

#include <Servo.h>

Servo myservo;
Servo myservo2;
Servo myservo3;
Servo myservo4;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int pin1 = 21;
const int pin2 = 20;
const int pin3 = 19;
const int pin4 = 18;
int pos = 0;  // variable to store the servo position

void setup() {

  Serial.begin(9600);
  for (int i = 0; i <= 3; i++){
    pinMode(pin[i],OUTPUT);
    myservo[i].attach(pin[i]);          // attaches the servo on pin1 9 to the servo object
  } 
}

void loop() {
  for (pos = 0; pos <= 360; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Serial.println(pos);
    for (int j = 0; j <= 3; j++){
      myservo[j].write(pos);      // tell servo to go to position in variable 'pos'
    }
    delay(30);           // waits 15ms for the servo to reach the position
  }
  for (pos = 360; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    Serial.println(pos);
    for (int j = 0; j <= 3; j++){
      myservo[j].write(pos);     // tell servo to go to position in variable 'pos'
    }
    delay(30);      // waits 15ms for the servo to reach the position
  }
}

````

But the electronics don't worked well because it was not the right alimentation for the servo.

So I searched a converter to change 12V to 6V and make the servo work.

For the next session, we would like to re-make the mechanics of the robot to avoid too much tightening torque.
