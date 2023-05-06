#ifndef BT_CONTROLLER_H
#define BT_CONTROLLER_H

#include <stdint.h>
#include <Arduino.h>

class BTController {
private:
  //  const uint8_t nb_letters = 26;
  //  const char lowercase[nb_letters] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  //  const char uppercase[nb_letters] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  //  WheelController *wheel_controller;
  const char NEGATIVE_SIGN = '-';
  static const uint8_t NB_SINGLE_COMMANDS = 2;
  const char SINGLE_COMMANDS[NB_SINGLE_COMMANDS] = { 'F', 'B' };

  char current_command = ' ';
  int16_t current_value = 0;
  int8_t current_sign = 1;

  static const uint8_t RETURN_COMMAND_LENGTH = 7;
  char return_command[RETURN_COMMAND_LENGTH] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0' };

public:
  uint8_t toInt(char c);
  void appendStrValue(char value);
  bool isNumber(char c);
  //  void begin(WheelController *wc);
  void begin();
  bool isEndOfCommand(char c);
  void resetCommand();
  void returnCommand(const char command);
  void execute(char command);
  void checkCommand();
};

extern BTController Controller;

#endif