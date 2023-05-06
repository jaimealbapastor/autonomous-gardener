#ifndef WHEEL_CONTROLLER_H
#define WHEEL_CONTROLLER_H

#include <stdint.h>
#include <Servo.h>  // https://github.com/arduino-libraries/Servo/blob/master/docs/api.md
#include <Arduino.h>

class WheelController {
private:
  static const uint8_t nb_of_wheels = 6;

  const uint8_t right_pwm_pin = 5;
  const uint8_t left_pwm_pin = 4;
  const uint8_t right_dir_pin = 2;
  const uint8_t left_dir_pin = 3;

  // direction pins for each motor
  const uint8_t dir_pins[nb_of_wheels] = { left_dir_pin, right_dir_pin,
                                           left_dir_pin, right_dir_pin,
                                           left_dir_pin, right_dir_pin };

  // pwd pins for each motor
  const uint8_t pwm_pins[nb_of_wheels] = { left_pwm_pin, right_pwm_pin,
                                           left_pwm_pin, right_pwm_pin,
                                           left_pwm_pin, right_pwm_pin };

  // pins of each servo motor, 0 meaning there is no servo motor
  const uint8_t servo_pins[nb_of_wheels] = { 9, 11,
                                             0, 0,
                                             8, 10 };

  const uint8_t max_speed = 255;
  int16_t motor_speeds[nb_of_wheels];  // speed of each motor (-255 to 255 pwm)

  static const uint8_t nb_of_servo = 4;

  Servo servos[nb_of_servo];           // Servo objects to control each servo motor
  Servo *servos_in_pos[nb_of_wheels];  // Servo pointers in the same index as the DC motor

  const uint8_t min_speed_to_turn = 20;  // Minimum speed required in order to turn
  const uint8_t rest_angle = 90;         // The angle where all wheels are pointing forward

  bool direction(int16_t speed);

public:
  WheelController();
  ~WheelController();
  void begin();

  void setSpeed(uint8_t motor_index, int16_t pwm_speed);
  void setSpeeds(uint8_t motors[], int16_t pwm_speeds[], uint8_t size);
  void setSpeed(int16_t speed);
  void incrementSpeed(uint8_t motor_index, int16_t speed_increment);

  int16_t getSpeed(uint8_t motor_index = 0);
  uint8_t getMaxSpeed();

  void forward(int16_t speed);
  void backward(int16_t speed);
  void stop();
  void stop(uint32_t milliseconds);
  void slowStop();

  void turn_abs(uint8_t servo_index, uint8_t angle);
  void turn_abs(uint8_t angle);
  void turn_forward();
  void turn(uint8_t servo_i, uint8_t angle);
  void turn(uint8_t angle);

  void slowToSpeed_async(int16_t speed, int16_t newSpeed);
  void emergencyShotDown();
};

#endif