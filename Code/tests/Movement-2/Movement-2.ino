#include "WheelController.h"

// I am doing 2 printing functions because of this:
// https://stackoverflow.com/questions/5739888/what-is-the-difference-between-signed-and-unsigned-int

/**
 * @brief Print an array of int8_t in the serial monitor
 *
 * @param arrayList
 * @param size
 */
void printSignedList(int8_t *arrayList, int size) {
  Serial.print("[ ");
  for (int i = 0; i < size; i++) {
    Serial.print(*(arrayList + i));
    if (i != size - 1)
      Serial.print(", ");
  }
  Serial.print(" ]");
}

/**
 * @brief Print an array of uint8_t in the serial monitor
 *
 * @param arrayList
 * @param size
 */
void printUnsignedList(uint8_t *arrayList, int size) {
  Serial.print("[ ");
  for (int i = 0; i < size; i++) {
    Serial.print(*(arrayList + i));
    if (i != size - 1)
      Serial.print(", ");
  }
  Serial.print(" ]");
}

void test_forward() {
  Wheels.forward(100);
  ;
}

void test_speed() {
  Wheels.forward(100);
  delay(2000);
  Wheels.stop(2000);

  Wheels.backward(100);
  delay(2000);
  Wheels.stop(2000);
}

void test_slowstop() {
  Wheels.forward(100);
  delay(2000);
  Wheels.slowStop();

  Wheels.backward(100);
  delay(2000);
  Wheels.slowStop();
}

void test_servos() {
  Wheels.turn_abs(10);
  delay(4000);
  Wheels.turn_abs(-10);
  delay(4000);
}

void test_turn_round() {
  // Wheels.setSpeed(uint8_t *motors, int8_t *pwm_speeds, uint8_t size);
  Wheels.forward(200);
  delay(2000);
  Wheels.backward(200);
  delay(2000);

  Wheels.slowStop(1000);

  Wheels.setSpeed(200);
  Wheels.turn_abs(20);
  delay(2000);
  Wheels.changeDirection();
  Wheels.setSpeed(200);
  delay(2000);

  Wheels.slowStop(1000);

  Wheels.setSpeed(200);
  Wheels.turn_abs(-20);
  delay(2000);
  Wheels.changeDirection();
  Wheels.setSpeed(200);
  delay(2000);

  Wheels.slowStop(1000);
}

void test_angles() {
  Wheels.turn_abs(20);
  Wheels.setSpeed(20);
  delay(10000);
  Wheels.changeDirection();
  Wheels.setSpeed(20);
  delay(10000);
}

void setup() {
  Serial.begin(9600);
  Wheels.begin();

  // test_forward();
}
void loop() {
  if (Serial.available()) {
    char incomming = Serial.read();
    switch (incomming) {
      case 'A':
        Wheels.turn_abs(0);
        break;
      case 'B':
        Wheels.turn_abs(30);
        break;
      case 'C':
        Wheels.turn_abs(-30);
        break;
      case 'D':
        Wheels.setSpeed(40);
        delay(15000);
        Wheels.stop();
        break;
      case 'E':
        Wheels.changeDirection();
        break;
      default:
        break;
    }
  }
  //test_angles();
  // test_speed();
  // test_slowstop();
  //test_turn_round();

  // test_servos()
  // test_class();
}