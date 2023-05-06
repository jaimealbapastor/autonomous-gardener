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

WheelController w;

void test_speed() {
  w.forward(100);
  delay(2000);
  w.stop(2000);

  w.backward(100);
  delay(2000);
  w.stop(2000);
}

void test_servos() {
  w.turn(10);
  delay(4000);
  w.turn(-10);
  delay(4000);
}

void test_turn_round() {
  // w.setSpeed(uint8_t *motors, int8_t *pwm_speeds, uint8_t size);
  w.forward(200);
  delay(2000);
  w.stop(1000);
  w.backward(200);
  delay(2000);

  w.stop(1000);

  w.setSpeed(200);
  w.turn_abs(20);
  delay(2000);
  w.stop(1000);
  w.setSpeed(-200);
  delay(2000);

  w.stop(1000);

  w.setSpeed(200);
  w.turn_abs(-20);
  delay(2000);
  w.stop(1000);
  w.setSpeed(-200);
  delay(2000);
}

void setup() {
  Serial.begin(9600);
  w.begin();

  for (uint8_t i = 8; i <= 11; i++)
    pinMode(i, OUTPUT);

  delay(2000);
}

int int_received;

void loop() {

  test_turn_round();


  // test_servos()
  // test_class();
}