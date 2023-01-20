#ifndef WHEELS_HPP
#define WHEELS_HPP

#include <stdint.h>

class Wheels{
  private:


  // Directions of left and right side motors
  uint8_t _directions[] = {0, 0}; // {left direction, Right direction}

  static const uint8_t _max_nb_of_motors = 6;
  uint8_t _nb_of_motors = 0;

  uint8_t _dir_pins[_max_nb_of_motors];  // direction pins for each motor
  uint8_t _pwd_pins[_max_nb_of_motors];  // pwd pins for each motor
  uint8_t _max_speed = 255;
  uint8_t _motor_speeds[_max_nb_of_motors]; // speed of each motor (255 max)
  uint8_t _motor_dir[_max_nb_of_motors];

  public:
  wheels(uint8_t pins[],uint8_t size);
  // wheels():wheels([1,2,3,4,5,6], 6);
  ~wheels();

  void setSpeed(uint8_t percent_speed);

  uint8_t getNumberOfMotors();
  uint8_t* getDirections();
  uint8_t* getSpeeds();

  void forward();
  void forward(uint8_t speed);

}
#endif