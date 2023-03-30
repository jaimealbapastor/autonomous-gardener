#include "WheelController.h"

// I am doing 2 printing functions because of this:
// https://stackoverflow.com/questions/5739888/what-is-the-difference-between-signed-and-unsigned-int

/**
 * @brief Print an array of int8_t in the serial monitor
 *
 * @param arrayList
 * @param size
 */
void printSignedList(int8_t *arrayList, int size)
{
  Serial.print("[ ");
  for (int i = 0; i < size; i++)
  {
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
void printUnsignedList(uint8_t *arrayList, int size)
{
  Serial.print("[ ");
  for (int i = 0; i < size; i++)
  {
    Serial.print(*(arrayList + i));
    if (i != size - 1)
      Serial.print(", ");
  }
  Serial.print(" ]");
}

uint8_t nbMotors = 6;

uint8_t dir_pins[6] = {1, 2, 3, 4, 5, 6};    // pins for direction
uint8_t pwd_pins[6] = {7, 8, 9, 10, 11, 12}; // pins for speed

WheelController w(dir_pins, pwd_pins);

void test_1()
{
  Serial.println(" === Test 1 | Changing speeds and directions ===");

  static const uint8_t nbMotorsChange = 3;
  uint8_t someMotors[nbMotorsChange] = {0, 2, 4};     // motors to change speed
  int8_t new_speeds[nbMotorsChange] = {-75, 50, -25}; // new speeds for motors

  Serial.print("Speed: ");
  printUnsignedList(w.getSpeeds(), nbMotors); // display speed for all motors

  Serial.print("\nDirection: ");
  printSignedList(w.getDirections(), nbMotors); // display direction for all motors

  w.setSpeed(someMotors, new_speeds, nbMotorsChange); // set speed for some motors

  Serial.print("\nModified speed: ");
  printUnsignedList(w.getSpeeds(), nbMotors); // display modified speed for all motors
  Serial.print("\nModified directions: ");
  printSignedList(w.getDirections(), nbMotors); // display modified direction for all motors
}

void setup()
{
  Serial.begin(9600);

  test_1();
}
void loop()
{
}