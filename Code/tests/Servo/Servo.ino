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

void rotation(){
    for (pos = 0; pos <= 120; pos++) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Serial.println(pos);
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(30);  // waits 15ms for the servo to reach the position
  }
  for (pos = 120; pos >= 0; pos--) {  // goes from 180 degrees to 0 degrees
    Serial.println(pos);
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(30);  // waits 15ms for the servo to reach the position
  }
}

void setup() {

  Serial.begin(9600);
  pinMode(pin1, OUTPUT);
  ///pinMode(pin2,OUTPUT);
  ///pinMode(pin3,OUTPUT);
  //pinMode(pin4,OUTPUT);
  myservo.attach(pin4);  // attaches the servo on pin1 9 to the servo object
  //myservo2.attach(pin2);
  //myservo3.attach(pin3);
  //myservo4.attach(pin4);
  myservo.write(0);
}

void loop() {
rotation();

}

void txrfg() {
  for (pos = 0; pos <= 270; pos++) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Serial.println(pos);
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    myservo2.write(pos);
    myservo3.write(pos);
    myservo4.write(pos);
    delay(30);  // waits 15ms for the servo to reach the position
  }
  for (pos = 360; pos >= 0; pos--) {  // goes from 180 degrees to 0 degrees
    Serial.println(pos);
    for (int j = 0; j <= 3; j++) {
      myservo.write(pos);  // tell servo to go to position in variable 'pos'
      myservo2.write(pos);
      myservo3.write(pos);
      myservo4.write(pos);
    }
    delay(30);  // waits 15ms for the servo to reach the position
  }
}