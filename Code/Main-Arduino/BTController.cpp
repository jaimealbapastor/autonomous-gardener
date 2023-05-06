#include "BTController.h"

BTController Bluetooth;

// void BTController::begin(WheelController *wc)
void BTController::begin()
{
  // this->wheel_controller = wc;
  Serial1.begin(9600);
}

bool BTController::isNumber(char c)
{
  return ('0' <= c and c <= '9');
}

uint8_t BTController::toInt(char c)
{
  return c - '0'; // the distance between the ASCII value of '0' and c
}

void BTController::appendStrValue(char value)
{
  for (uint8_t i = 2; i < this->RETURN_COMMAND_LENGTH; i++)
  {
    if (this->return_command[i] == '\0')
    {
      this->return_command[i] = value;
      return;
    }
  }
}

bool BTController::isEndOfCommand(char command)
{
  for (uint8_t i = 0; i < this->NB_SINGLE_COMMANDS; i++)
    if (command == this->SINGLE_COMMANDS[i])
      return true;
  return command == this->current_command;
}

void BTController::resetCommand()
{
  this->current_command = ' ';
  this->current_value = 0;
  this->current_sign = 1;
  for (uint8_t i = 0; i < this->RETURN_COMMAND_LENGTH; i++)
    this->return_command[i] = '\0';
}

void BTController::returnCommand(const char command)
{
  this->return_command[0] = '*';
  this->return_command[1] = command;
  for (uint8_t i = 2; i < this->RETURN_COMMAND_LENGTH; i++)
  {
    if (this->return_command[i] == '\0')
    {
      this->return_command[i] = '*';
      break;
    }
  }
  Serial1.write(this->return_command);
}

void BTController::execute(char command)
{
  switch (command)
  {
  case 'F': // Forward
    Serial.println("Forward");
    Wheels.setDirection(1);
    break;
  case 'B': // Backward
    Serial.println("Backward");
    Wheels.setDirection(0);
    break;
  case 'S': // Speed
    Serial.print("Speed ");
    Serial.println(this->current_value);
    Wheels.setSpeed(this->current_value);
    this->returnCommand('V');
    break;
  case 'A': // Angle
    Serial.print("Angle ");
    Serial.println(this->current_value);
    Wheels.turn_abs(this->current_value);
    this->returnCommand('T');
    break;
  case 'E': // Emergency
    Serial.println("Emergency stop");
    Wheels.emergencyShotDown();
  default:
    break;
  }
}

void BTController::checkCommand()
{
  if (!Serial1.available())
    return;

  char command = Serial1.read();

  if (this->isNumber(command))
  { // if it's number, then it's not a command, just giving the value of a command
    this->current_value = this->current_value * 10 + this->current_sign * this->toInt(command);
    this->appendStrValue(command);
    return;
  }

  if (command == this->NEGATIVE_SIGN)
  {
    this->current_sign = -1;
    this->appendStrValue(this->NEGATIVE_SIGN);
    return;
  }

  if (this->isEndOfCommand(command))
  {
    this->execute(command);
    this->resetCommand();
    return;
  }

  this->current_command = command;
}