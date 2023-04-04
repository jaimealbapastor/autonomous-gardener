#include <Servo.h>

//Servo myservo;
Servo myservo2;
//Servo myservo3;
Servo myservo4;  // create servo object to control a servo
// twelve servo objects can be created on most boards

//const int pin1 = 21;
const int pin2 = 20;
//const int pin3 = 19;
const int pin4 = 18;
int pos = 0;  // variable to store the servo position

void setup() {
  //pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  //pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  Serial.begin(9600);
  //myservo.attach(pin1);
  myservo2.attach(pin2);
  //myservo3.attach(pin3);
  myservo4.attach(pin4);  // attaches the servo on pin1 9 to the servo object
}

void loop() {
  for (pos = 0; pos <= 360; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Serial.println(pos);
    //myservo.write(pos);
    myservo2.write(pos);
    //myservo3.write(pos);
    myservo4.write(pos);  // tell servo to go to position in variable 'pos'
    delay(30);           // waits 15ms for the servo to reach the position
  }
  for (pos = 360; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    Serial.println(pos);
    //myservo.write(pos);
    myservo2.write(pos);
    //myservo3.write(pos);
    myservo4.write(pos);  // tell servo to go to position in variable 'pos'
    delay(30);           // waits 15ms for the servo to reach the position
  }
}