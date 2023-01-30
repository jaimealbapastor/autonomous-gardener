#ifndef WHEELS_HPP
#define WHEELS_HPP

#include <stdint.h>

class Wheels {
private:

  static const uint8_t _max_nb_of_motors = 6;
  uint8_t _nb_of_motors = 0;

  uint8_t _dir_pins[_max_nb_of_motors];  // direction pins for each motor
  uint8_t _pwd_pins[_max_nb_of_motors];  // pwd pins for each motor
  uint8_t _max_speed = 255;
  uint8_t _motor_speeds[_max_nb_of_motors];  // speed of each motor (255 max)
  int8_t _motor_dir[_max_nb_of_motors];

public:
  Wheels(uint8_t direction_pins[], uint8_t pwd_pins[], uint8_t size);
  // wheels(uint8_t pins[],uint8_t size);
  // wheels():wheels([1,2,3,4,5,6], 6);
  ~Wheels();

  void setSpeed(uint8_t motors[], int8_t percent_speeds[], uint8_t size);

  uint8_t getNumberOfMotors();
  uint8_t* getDirections();
  uint8_t* getSpeeds();

  void forward(uint8_t speed, uint32_t duration = 0);
  void backward(uint8_t speed, uint32_t duration = 0);

};

#endif