#include "WheelController.h"

// ======= CONSTRUCTORS =======

/**
 * @brief Construct a new WheelController:: WheelController object.
 * It controls the 6 DC motors and 4 servo motors of the E-Gaia autonomous robot.
 */
WheelController::WheelController() {

  uint8_t servo_counter = 0;
  for (uint8_t i = 0; i < this->NB_OF_WHEELS; i++) {
    // initialize speeds to 0
    this->robot_speeds[i] = 0;

    // create servo controllers
    if (SERVO_PINS[i]) {
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
bool WheelController::direction(int16_t speed) {
  if (speed >= 0)  // the return values depend on how we have connected the wires
    return 0;      // 0 goes forwards
  return 1;        // while 1 goes backwards
}

// ======= PUBLIC =======
/**
 * @brief Initializes the pinModes, servo controllers, etc
 */
void WheelController::begin() {
  for (uint8_t i = 0; i < this->NB_OF_WHEELS; i++) {

    pinMode(this->DIR_PINS[i], OUTPUT);
    pinMode(this->PWM_PINS[i], OUTPUT);
    pinMode(this->SERVO_PINS[i], OUTPUT);

    if (this->servos_in_pos[i] != nullptr) {
      this->servos_in_pos[i]->attach(this->SERVO_PINS[i]);
      this->servos_in_pos[i]->write(this->REST_ANGLE);
    }
  }
}

/**
 * @brief Set speed of the specified motor
 *
 * @param motor [uint8_t] the motor which speed will be changed
 * @param pwm_speed [unint_8] the speed in pwm (0 to 255)
 */
void WheelController::setSpeed(uint8_t motor_index, int16_t pwm_speed) {
  // TODO create token for most used combinations (all, right, left)

  if (pwm_speed > this->MAX_SPEED)
    this->robot_speeds[motor_index] = this->MAX_SPEED;  // if the speed is to high, set it to the maximum

  else if (pwm_speed < -this->MAX_SPEED)
    this->robot_speeds[motor_index] = -this->MAX_SPEED;  // if the speed is to high (backwards), set it to the maximum (backwards)

  else
    this->robot_speeds[motor_index] = pwm_speed;

  bool dir = this->direction(pwm_speed);
  int16_t abs_speed = abs(this->robot_speeds[motor_index]);

  digitalWrite(this->DIR_PINS[motor_index], dir);
  analogWrite(this->PWM_PINS[motor_index], abs_speed);
}

/**
 * @brief Set speed of the specified motors
 *
 * @param motors uint8_t list of the motors which speed will be changed
 * @param pwm_speeds unint_8 list of the speeds in pwm (0 to 255)
 * @param size the size 'motors' and 'pwm_speeds'
 */
void WheelController::setSpeeds(uint8_t motors[], int16_t pwm_speeds[], uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {
    this->setSpeed(motors[i], pwm_speeds[i]);
  }
}

/**
 * @brief sets all the motors to a specific speed
 *
 * @param speed (uint8_t) 0 to 255
 */
void WheelController::setSpeed(int16_t speed) {
  uint8_t motors[] = { 0, 1, 2, 3, 4, 5 };
  int16_t speeds[] = { speed, -speed, speed, -speed, speed, -speed };
  this->setSpeeds(motors, speeds, this->NB_OF_WHEELS);
}

void WheelController::incrementSpeed(uint8_t motor_index, int16_t speed_increment) {
  int16_t speed = this->getSpeed(motor_index);
  this->setSpeed(motor_index, speed + speed_increment);
}

int16_t WheelController::getSpeed(uint8_t motor_index = 0) {
  return this->robot_speeds[motor_index];
}

uint8_t WheelController::getMaxSpeed() {
  uint8_t max = 0;
  for (uint8_t i = 0; i < this->NB_OF_WHEELS; i++) {
    if (abs(this->robot_speeds[i]) > max)
      max = abs(this->robot_speeds[i]);
  }
  return max;
}

/**
 * @brief sets all the motors to a specific speed forwards
 *
 * @param speed (uint8_t) 0 to 255
 */
void WheelController::forward(int16_t speed) {
  this->setSpeed(this->MIN_SPEED_TO_TURN);
  this->turn_forward();
  // TODO make delay with millis
  this->setSpeed(speed);
}

/**
 * @brief sets all the motors to a specific speed backwards
 *
 * @param speed (uint8_t) 0 to 255
 */
void WheelController::backward(int16_t speed) {
  this->forward(-speed);
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
  int16_t speed;
  while (this->getMaxSpeed()) {
    for (uint8_t motor_index = 0; motor_index < this->NB_OF_WHEELS; motor_index++) {
      speed = this->getSpeed(motor_index);
      this->incrementSpeed(motor_index, speed / 2);
    }
  }
}

void WheelController::turn_abs(uint8_t servo_index, uint8_t angle) {
  if (this->servos_in_pos[servo_index] != nullptr) {
    // TODO add: and this->robot_speeds[servo_index] >= this->MIN_SPEED_TO_TURN
    this->servos_in_pos[servo_index]->write(angle);
  }
}

void WheelController::turn_abs(uint8_t angle) {
  this->turn_abs(0, this->REST_ANGLE + angle);
  this->turn_abs(1, this->REST_ANGLE + angle);
  this->turn_abs(4, this->REST_ANGLE - angle);
  this->turn_abs(5, this->REST_ANGLE - angle);
}

void WheelController::turn_forward() {
  this->turn_abs(0);
}

void WheelController::turn(uint8_t servo_index, uint8_t angle) {
  uint8_t pos = this->servos_in_pos[servo_index]->read();
  this->turn_abs(servo_index, pos + angle);
}

void WheelController::turn(uint8_t angle) {
  this->turn(0, angle);
  this->turn(1, angle);
  this->turn(4, -angle);
  this->turn(5, -angle);
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
  this->forward(0);
  while (1) {
  }
}
