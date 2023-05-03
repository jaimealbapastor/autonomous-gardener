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

const uint8_t nbMotors = 6;

const uint8_t right_pwm_pin = 5;
const uint8_t right_dir_pin = 2;
const uint8_t left_pwm_pin = 4;
const uint8_t left_dir_pin = 3;

uint8_t dir_pins[6] = { left_dir_pin, right_dir_pin,
                        left_dir_pin, right_dir_pin,
                        left_dir_pin, right_dir_pin };  // pins for direction

uint8_t pwd_pins[6] = { left_pwm_pin, right_pwm_pin,
                        left_pwm_pin, right_pwm_pin,
                        left_pwm_pin, right_pwm_pin };  // pins for speed
uint8_t servo_pins[6] = { 9, 11,
                          0, 0,
                          8, 10 };



WheelController w(dir_pins, pwd_pins, servo_pins);


void test_class() {
  w.forward(100);
  delay(2000);
  w.stop();
  delay(2000);
  w.backward(100);
  delay(2000);
  w.stop();
  delay(2000);
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
  w.turn_abs(10);
  delay(2000);
  w.stop(1000);
  w.setSpeed(-200);
  delay(1000);

  w.stop(1000);

  w.setSpeed(200);
  w.turn_abs(-10);
  delay(2000);
  w.stop(1000);
  w.setSpeed(-200);
  delay(1000);
}

void setup() {
  Serial.begin(9600);

  pinMode(right_pwm_pin, OUTPUT);
  pinMode(right_dir_pin, OUTPUT);
  pinMode(left_pwm_pin, OUTPUT);
  pinMode(left_dir_pin, OUTPUT);

  for (uint8_t i = 8; i <= 11; i++)
    pinMode(i, OUTPUT);

  delay(2000);
}

int int_received;

void loop() {
  if (Serial.available()) {
    int_received = Serial.parseInt();
    w.turn(int_received);
  }

  //test_servos()
  //test_class();
}