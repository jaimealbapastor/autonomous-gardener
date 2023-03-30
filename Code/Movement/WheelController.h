#ifndef WHEEL_CONTROLLER_H
#define WHEEL_CONTROLLER_H

#include <stdint.h>

class WheelController
{
private:
  static const uint8_t _nb_of_motors = 6;

  uint8_t _dir_pins[_nb_of_motors]; // direction pins for each motor
  uint8_t _pwd_pins[_nb_of_motors]; // pwd pins for each motor
  const uint8_t _max_speed = 255;
  uint8_t _motor_speeds[_nb_of_motors]; // speed of each motor (255 max)
  int8_t _motor_dir[_nb_of_motors];     // direction of each motor (0 or 1)

public:
  WheelController(uint8_t direction_pins[], uint8_t pwd_pins[]);
  // WheelController(uint8_t pins[],uint8_t size);
  // WheelController():WheelController([1,2,3,4,5,6], 6);
  ~WheelController();

  void setSpeed(uint8_t motors[], int8_t pwm_speeds[], uint8_t size);
  void incrementSpeed(uint8_t motors[], int8_t increments[], uint8_t size);

  uint8_t getNumberOfMotors();
  uint8_t *getDirections();
  uint8_t *getSpeeds();

  void forward(uint8_t speed);
  void backward(uint8_t speed);

  void slowToSpeed_async(uint8_t speed, uint8_t newSpeed);
  void emergencyShotDown();
};

#endif