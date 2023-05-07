#ifndef BT_CONTROLLER_H
#define BT_CONTROLLER_H

#include <stdint.h>
#include <Arduino.h>
#include "WheelController.h"
#include "DrillController.h"

class BTController {
private:
  const char NEGATIVE_SIGN = '-';
  static const uint8_t NB_SINGLE_COMMANDS = 6;
  const char SINGLE_COMMANDS[NB_SINGLE_COMMANDS] = { 'F', 'B', 'E', 'D', 'U', 'G' };

  char current_command = ' ';
  int16_t current_value = 0;
  int8_t current_sign = 1;

  static const uint8_t RETURN_COMMAND_LENGTH = 7;
  char return_command[RETURN_COMMAND_LENGTH] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0' };

  uint8_t toInt(char c);
  void appendStrValue(char value);
  bool isNumber(char c);

  bool isEndOfCommand(char c);
  void resetCommand();
  void returnCommand(const char command);
  void execute(char command);

public:
  void begin();
  void checkCommand();
};

extern BTController Bluetooth;

#endif