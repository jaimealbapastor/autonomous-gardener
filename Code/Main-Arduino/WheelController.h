#ifndef WHEEL_CONTROLLER_H
#define WHEEL_CONTROLLER_H

#include <stdint.h>
#include <Servo.h>  // https://github.com/arduino-libraries/Servo/blob/master/docs/api.md
#include <Arduino.h>

class WheelController {
private:
  static const uint8_t NB_OF_WHEELS = 6;
  static const uint8_t NB_OF_SERVO = 4;

  const uint8_t RIGHT_PWM_PIN = 5;
  const uint8_t LEFT_PWM_PIN = 4;
  const uint8_t RIGHT_DIR_PIN = 2;
  const uint8_t LEFT_DIR_PIN = 3;

  // pwd pins for each motor
  const uint8_t PWM_PINS[NB_OF_WHEELS] = { LEFT_PWM_PIN, RIGHT_PWM_PIN,
                                           LEFT_PWM_PIN, RIGHT_PWM_PIN,
                                           LEFT_PWM_PIN, RIGHT_PWM_PIN };

  // direction pins for each motor
  const uint8_t DIR_PINS[NB_OF_WHEELS] = { LEFT_DIR_PIN, RIGHT_DIR_PIN,
                                           LEFT_DIR_PIN, RIGHT_DIR_PIN,
                                           LEFT_DIR_PIN, RIGHT_DIR_PIN };

  // the sense of each motor
  const int8_t MOTOR_DIRECTIONS[NB_OF_WHEELS] = { 1, 0,
                                                  1, 0,
                                                  1, 0 };

  // pins of each servo motor, 0 meaning there is no servo motor
  const uint8_t SERVO_PINS[NB_OF_WHEELS] = { 9, 11,
                                             0, 0,
                                             8, 10 };

  const float ANGLE_RATIOS[NB_OF_WHEELS] = { 1, 1,
                                             0, 0,
                                             0.5, 0.5 };

  const int8_t SERVO_OFFSETS[NB_OF_WHEELS] = { -3, -6,
                                               0, 0,
                                               3, -5 };

  const uint8_t MAX_SPEED = 255;
  const uint8_t MIN_SPEED_TO_TURN = 20;  // Minimum speed required in order to turn
  const uint8_t REST_ANGLE = 90;         // The angle where all wheels are pointing forward

  uint8_t robot_speed = 0;
  bool robot_direction = 1;
  int8_t robot_angle = 0;

  Servo servos[NB_OF_SERVO];           // Servo objects to control each servo motor
  Servo *servos_in_pos[NB_OF_WHEELS];  // Servo pointers in the same index as the DC motor

  bool directionOf(uint8_t motor_index);
  void write();

public:
  WheelController();
  ~WheelController();
  void begin();

  uint8_t getSpeed();

  void setSpeed(uint8_t pwm_speed);
  void setDirection(int8_t dir);
  void changeDirection();

  void incrementSpeed(int8_t speed_increment);

  void turn_abs(uint8_t servo_index, int8_t angle);
  void turn_abs(int8_t angle);
  void turn_straight();

  void forward(uint8_t speed, int8_t dir = 1);
  void backward(uint8_t speed);
  void stop();
  void stop(uint32_t milliseconds);
  void slowStop();
  void slowStop(uint32_t milliseconds);

  void slowToSpeed_async(int16_t speed, int16_t newSpeed);
  void emergencyShotDown();
};

extern WheelController Wheels;

#endif