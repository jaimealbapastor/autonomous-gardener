#ifndef WHEEL_CONTROLLER_H
#define WHEEL_CONTROLLER_H

#include <stdint.h>
#include <Servo.h>  // https://github.com/arduino-libraries/Servo/blob/master/docs/api.md
#include <Arduino.h>

class WheelController {
private:
  static const uint8_t nb_of_wheels = 6;

  uint8_t dir_pins[nb_of_wheels];  // direction pins for each motor
  uint8_t pwm_pins[nb_of_wheels];  // pwd pins for each motor
  const uint8_t max_speed = 255;
  int16_t motor_speeds[nb_of_wheels];  // speed of each motor (255 max)
  // TODO a single int8_t instead of direction list

  static const uint8_t nb_of_servo = 4;
  Servo servos[nb_of_servo];  // Servo objects to control each servo motor
  Servo *servos_in_pos[nb_of_wheels];

  const uint8_t min_speed_to_turn = 20;

  static bool direction(int16_t n);

public:
  WheelController(uint8_t direction_pins[], uint8_t pwd_pins[], uint8_t servo_pins[]);
  // WheelController(uint8_t pins[],uint8_t size);
  // WheelController():WheelController([1,2,3,4,5,6], 6);
  ~WheelController();

  void setSpeed(uint8_t motor_index, int16_t pwm_speed);
  void setSpeeds(uint8_t motors[], int16_t pwm_speeds[], uint8_t size);
  void setSpeed(int16_t speed);
  void incrementSpeed(uint8_t motor_index, int16_t speed_increment);

  int16_t getSpeed(uint8_t motor_index = 0);
  uint8_t getMaxSpeed();

  void forward(uint8_t speed);
  void backward(uint8_t speed);
  void stop();
  void stop(uint32_t milliseconds);
  void slowStop();

  void turn_abs(uint8_t servo_index, uint8_t angle);
  void turn_abs(uint8_t angle);
  void turn_forward();
  void turn(uint8_t servo_i, uint8_t angle);
  void turn(uint8_t angle);

  void slowToSpeed_async(uint8_t speed, uint8_t newSpeed);
  void emergencyShotDown();
};

#endif