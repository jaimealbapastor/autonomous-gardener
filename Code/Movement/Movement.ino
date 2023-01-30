#include "Wheels.h"

/**
 * @brief Print an array of uint8_t in the serial monitor
 * 
 * @param arrayList 
 * @param size 
 */
void printList(uint8_t *arrayList, int size) {
  Serial.print("[ ");
  for (int i = 0; i < size; i++) {
    Serial.print(*(arrayList + i));
    if (i != size - 1) Serial.print(", ");
  }
  Serial.print(" ]");
}

uint8_t nbMotors = 6;

uint8_t dir_pins[6] = { 1, 2, 3, 4, 5, 6 }; // pins for direction
uint8_t pwd_pins[6] = { 7, 8, 9, 10, 11, 12 };  // pins for speed

uint8_t someMotors[3] = { 1, 4, 5 };  // motors to change speed
int8_t new_speeds[3] = { -50, 50, 200 };  // new speeds for motors

Wheels w(dir_pins, pwd_pins, nbMotors);

void setup() {
  Serial.begin(9600);

  Serial.print("Speed: ");
  printList(w.getSpeeds(), nbMotors); // display speed for all motors

  Serial.print("\nDirection: ");
  printList(w.getDirections(), nbMotors); // display direction for all motors

  w.setSpeed(someMotors, new_speeds, nbMotors); // set speed for some motors

  Serial.print("\nModified speed: ");
  printList(w.getSpeeds(), nbMotors); // display modified speed for all motors
  Serial.print("\nModified directions: ");
  printList(w.getDirections(), nbMotors); // display modified direction for all motors
}
void loop() {
}