#include "Wheels.h"

uint8_t dir_pins[6] = { 1, 2, 3, 4, 5, 6 };
uint8_t pwd_pins[6] = { 7, 8, 9, 10, 11, 12 };

uint8_t motors[3] = { 1, 4, 5 };
int8_t new_speeds[3] = { -50, 50, 200 };

void printArray(uint8_t *arrayList, int size) {
  Serial.print("[ ");
  for (int i = 0; i < size; i++) {
    Serial.print(*(arrayList + i));
    if (i != size - 1) Serial.print(", ");
  }
  Serial.print(" ]");
}

Wheels w(dir_pins, pwd_pins, 6);


void setup() {
  Serial.begin(9600);

  Serial.print("Speed: ");
  printArray(w.getSpeeds(), 6);

  Serial.print("\nDirection: ");
  printArray(w.getDirections(), 6);


  w.setSpeed(motors, new_speeds, 6);
  Serial.print("\nChanges speeds: ");
  printArray(w.getSpeeds(), 6);
  printArray(w.getDirections(), 6);
}
void loop() {
}