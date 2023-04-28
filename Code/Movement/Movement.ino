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

WheelController w(dir_pins, pwd_pins);

void test_1() {
  Serial.println(" === Test 1 | Changing speeds and directions ===");

  static const uint8_t nbMotorsChange = 3;
  uint8_t someMotors[nbMotorsChange] = { 0, 2, 4 };      // motors to change speed
  int8_t new_speeds[nbMotorsChange] = { -75, 50, -25 };  // new speeds for motors

  Serial.print("Speed: ");
  printUnsignedList(w.getSpeeds(), nbMotors);  // display speed for all motors

  Serial.print("\nDirection: ");
  printSignedList(w.getDirections(), nbMotors);  // display direction for all motors

  w.setSpeed(someMotors, new_speeds, nbMotorsChange);  // set speed for some motors

  Serial.print("\nModified speed: ");
  printUnsignedList(w.getSpeeds(), nbMotors);  // display modified speed for all motors
  Serial.print("\nModified directions: ");
  printSignedList(w.getDirections(), nbMotors);  // display modified direction for all motors
}

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

void setup() {
  Serial.begin(9600);

  pinMode(right_pwm_pin, OUTPUT);
  pinMode(right_dir_pin, OUTPUT);
  pinMode(left_pwm_pin, OUTPUT);
  pinMode(left_dir_pin, OUTPUT);

  
}
void loop() {
  
  test_class();
}