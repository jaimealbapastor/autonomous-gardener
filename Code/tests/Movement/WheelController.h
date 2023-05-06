#ifndef WHEEL_CONTROLLER_H
#define WHEEL_CONTROLLER_H

#include <stdint.h>
#include <Servo.h>  // https://github.com/arduino-libraries/Servo/blob/master/docs/api.md
#include <Arduino.h>

class WheelController {
private:
  static const uint8_t NB_OF_WHEELS = 6;

  const uint8_t RIGHT_PWM_PIN = 5;
  const uint8_t LEFT_PWM_PIN = 4;
  const uint8_t RIGHT_DIR_PIN = 2;
  const uint8_t LEFT_DIR_PIN = 3;

  // direction pins for each motor
  const uint8_t DIR_PINS[NB_OF_WHEELS] = { LEFT_DIR_PIN, RIGHT_DIR_PIN,
                                           LEFT_DIR_PIN, RIGHT_DIR_PIN,
                                           LEFT_DIR_PIN, RIGHT_DIR_PIN };

  // pwd pins for each motor
  const uint8_t PWM_PINS[NB_OF_WHEELS] = { LEFT_PWM_PIN, RIGHT_PWM_PIN,
                                           LEFT_PWM_PIN, RIGHT_PWM_PIN,
                                           LEFT_PWM_PIN, RIGHT_PWM_PIN };

  // pins of each servo motor, 0 meaning there is no servo motor
  const uint8_t SERVO_PINS[NB_OF_WHEELS] = { 9, 11,
                                             0, 0,
                                             8, 10 };

  const uint8_t MAX_SPEED = 255;
  int16_t robot_speeds[NB_OF_WHEELS];  // speed of each motor (-255 to 255 pwm)

  static const uint8_t NB_OF_SERVO = 4;

  Servo servos[NB_OF_SERVO];           // Servo objects to control each servo motor
  Servo *servos_in_pos[NB_OF_WHEELS];  // Servo pointers in the same index as the DC motor

  const uint8_t MIN_SPEED_TO_TURN = 20;  // Minimum speed required in order to turn
  const uint8_t REST_ANGLE = 90;         // The angle where all wheels are pointing forward

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