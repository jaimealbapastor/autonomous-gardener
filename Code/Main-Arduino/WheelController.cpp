#include "WheelController.h"

WheelController Wheels;

// ======= CONSTRUCTORS =======

/**
 * @brief Construct a new WheelController object.
 * It controls the 6 DC motors and 4 servo motors of the E-Gaia autonomous robot.
 * Pins are specified as constants within the source code.
 */
WheelController::WheelController() {

  uint8_t servo_counter = 0;
  for (uint8_t i = 0; i < this->NB_OF_WHEELS; i++) {
    // create servo controllers
    if (this->SERVO_PINS[i]) {
      this->servos[servo_counter] = Servo();
      this->servos_in_pos[i] = &(this->servos[servo_counter++]);
    } else
      this->servos_in_pos[i] = nullptr;
  }
}

WheelController::~WheelController() {}

// ======= PRIVATE =======

/**
 * @brief Returns the direction of a given speed: 1 meaning forwards, 0 backwards.
 * @param speed the speed in int16_t : from -255 to 255
 */
bool WheelController::directionOf(uint8_t motor_index) {

  if (this->robot_direction == this->MOTOR_DIRECTIONS[motor_index])  // the return values depend on how we have connected the wires
    return 0;                                                        // 0 goes forwards
  return 1;                                                          // while 1 goes backwards
}

void WheelController::write() {
  for (uint8_t motor_index = 0; motor_index < this->NB_OF_WHEELS; motor_index++) {
    digitalWrite(this->DIR_PINS[motor_index], this->directionOf(motor_index));
    analogWrite(this->PWM_PINS[motor_index], this->robot_speed);
  }
}

// ======= PUBLIC =======
/**
 * @brief Initializes the pinModes and servo controllers.
 */
void WheelController::begin() {
  for (uint8_t i = 0; i < this->NB_OF_WHEELS; i++) {

    pinMode(this->DIR_PINS[i], OUTPUT);
    pinMode(this->PWM_PINS[i], OUTPUT);

    if (this->servos_in_pos[i] != nullptr) {
      pinMode(this->SERVO_PINS[i], OUTPUT);
      this->servos_in_pos[i]->attach(this->SERVO_PINS[i]);
      this->servos_in_pos[i]->write(this->REST_ANGLE);
    }
  }

  this->turn_straight();
}

uint8_t WheelController::getSpeed() {
  return this->robot_speed;
}

/**
 * @brief Set speed for all motors
 *
 * @param pwm_speed [uint8_t] the speed in pwm (-255 to 255)
 */
void WheelController::setSpeed(uint8_t pwm_speed) {
  // TODO create token for most used combinations (all, right, left)

  if (pwm_speed > this->MAX_SPEED)
    this->robot_speed = this->MAX_SPEED;  // if the speed is to high, set it to the maximum
  else
    this->robot_speed = pwm_speed;

  // this->motor_dir = this->directionOf(pwm_speed);
  this->write();
}

/**
 * @brief Changes the direction of the robot only if speed equals 0
 *
 */
void WheelController::setDirection(int8_t dir) {
  if (!this->robot_speed)  // only change direction if the robot has no speed
  {
    this->robot_direction = (dir > 0 ? 1 : 0);
    this->write();
  }
}

/**
 * @brief Changes the direction of the robot only if speed equals 0
 *
 */
void WheelController::changeDirection() {
  this->slowStop();
  this->setDirection(-this->robot_direction + 1);
}

/**
 * @brief Adds an increment to the current speed of the motors
 *
 * @param speed_increment [int8_t] The increment to ba added
 */
void WheelController::incrementSpeed(int8_t speed_increment) {
  this->setSpeed(this->getSpeed() + speed_increment);
}

/**
 * @brief Set the absolute angle of a single servo motor
 *
 * @param servo_index [uint8_t] The index of the servo motor concerned
 * @param angle [uint8_t] The angle to be set (0 to 180)
 */
void WheelController::turn_abs(uint8_t servo_index, int8_t angle) {
  if (this->servos_in_pos[servo_index] != nullptr) {
    // TODO add: and this->robot_speeds[servo_index] >= this->MIN_SPEED_TO_TURN

    int fixed_angle = angle * this->ANGLE_RATIOS[servo_index] + this->SERVO_OFFSETS[servo_index];
    this->servos_in_pos[servo_index]->write(this->REST_ANGLE + fixed_angle);
  }
}

/**
 * @brief Sets the absolute angle of the whole robot
 *
 * @param angle [uint8_t]
 */
void WheelController::turn_abs(int8_t angle) {
  if (abs(angle) > this->REST_ANGLE)  // make sure the sum is always positive
    angle = this->REST_ANGLE;

  // TODO descomentar esto
  // if (this->getSpeed() < this->MIN_SPEED_TO_TURN)
  //   this->setSpeed(this->MIN_SPEED_TO_TURN);

  this->robot_angle = angle;

  this->turn_abs(0, angle);
  this->turn_abs(1, angle);
  this->turn_abs(4, -angle);
  this->turn_abs(5, -angle);
}

/**
 * @brief Turns all the robots to their resting position (forwards)
 */
void WheelController::turn_straight() {
  this->turn_abs(0);
}

/**
 * @brief Sets all the motors to a specific speed forwards
 *
 * @param speed [uint8_t] from 0 to 255
 */
void WheelController::forward(uint8_t speed, int8_t dir = 1) {
  if (this->robot_direction != dir)
    this->changeDirection();

  this->turn_straight();
  // TODO make delay with millis
  this->setSpeed(speed);
}

/**
 * @brief sets all the motors to a specific speed backwards
 *
 * @param speed (uint8_t) 0 to 255
 */
void WheelController::backward(uint8_t speed) {
  this->forward(speed, 0);
}

void WheelController::stop() {
  this->setSpeed(0);
}
void WheelController::stop(uint32_t milliseconds) {
  // TODO change delay to millis
  this->stop();
  delay(milliseconds);
}

void WheelController::slowStop() {
  while (this->getSpeed()) {
    this->setSpeed((uint8_t)this->getSpeed() * 0.95);
    delay(50);
  }
}

void WheelController::slowStop(uint32_t milliseconds) {
  this->slowStop();
  delay(milliseconds);
}

void WheelController::slowToSpeed_async(int16_t speed, int16_t newSpeed) {
  int step = 1;
  if (speed > newSpeed)
    step = -1;
  for (int i = speed; i != newSpeed; i += step) {
    // analogWrite(pwdPin, i);
    delay(20);

    if ((i < 0) || (i > 256)) {
      // analogWrite(pwdPin, 0);
      speed = 0;
      return;
    }
  }
  speed = newSpeed;
}

void WheelController::emergencyShotDown() {
  // TODO gradually slow down the motors before stopping them completely
  this->slowStop();
}
