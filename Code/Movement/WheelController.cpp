#include "WheelController.h"

// ======= CONSTRUCTORS =======

/**
 * @brief Construct a new WheelController:: WheelController object.
 * It controls the 6 motors of the E-Gaia autonomous robot.
 *
 * @param direction_pins 6 element list of uint8_t
 * @param pwd_pins 6 element list of uint8_t
 */
WheelController::WheelController(uint8_t direction_pins[], uint8_t pwd_pins[], uint8_t servo_pins[]) {
  for (uint8_t i = 0; i < this->nb_of_wheels; i++) {
    this->dir_pins[i] = direction_pins[i];
    this->pwm_pins[i] = pwd_pins[i];
    this->motor_speeds[i] = 0;
  }

  uint8_t servo_counter = 0;
  for (uint8_t i = 0; i < this->nb_of_wheels; i++) {
    if (servo_pins[i]) {

      this->servos[i] = Servo();
      this->servos_in_pos[i] = &this->servos[i];

      this->servos[i].attach(servo_pins[servo_counter++]);
      this->servos[i].write(90);
    } else {
      this->servos_in_pos[i] = nullptr;
    }
  }
}

WheelController::~WheelController() {}

// ======= PRIVATE =======
static bool direction(int16_t n) {
  if (n >= 0) return 1;
  return 0;
}

// ======= PUBLIC =======


/**
 * @brief Set speed of the specified motor
 *
 * @param motor [uint8_t] the motor which speed will be changed
 * @param pwm_speed [unint_8] the speed in pwm (0 to 255)
 */
void WheelController::setSpeed(uint8_t motor_index, int16_t pwm_speed) {
  // TODO create token for most used combinations (all, right, left)


  if (pwm_speed > this->max_speed)
    this->motor_speeds[motor_index] = this->max_speed;  // if the speed is to high, set it to the maximum
  else if (pwm_speed < -this->max_speed)
    this->motor_speeds[motor_index] = -this->max_speed;  // if the speed is to high (backwards), set it to the maximum (backwards)
  else
    this->motor_speeds[motor_index] = pwm_speed;

  bool dir = this->direction(pwm_speed);
  int16_t abs_speed = abs(this->motor_speeds[motor_index]);

  digitalWrite(this->dir_pins[motor_index], dir);
  analogWrite(this->pwm_pins[motor_index], abs_speed);
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
  this->setSpeeds(motors, speeds, this->nb_of_wheels);
}

void WheelController::incrementSpeed(uint8_t motor_index, int16_t speed_increment) {
  int16_t speed = this->getSpeed(motor_index);
  this->setSpeed(motor_index, speed + speed_increment);
}

int16_t WheelController::getSpeed(uint8_t motor_index = 0) {
  return this->motor_speeds[motor_index];
}

uint8_t WheelController::getMaxSpeed() {
  uint8_t max = 0;
  for (uint8_t i = 0; i < this->nb_of_wheels; i++) {
    if (abs(this->motor_speeds[i]) > max)
      max = abs(this->motor_speeds[i]);
  }
  return max;
}

/**
 * @brief sets all the motors to a specific speed forwards
 *
 * @param speed (uint8_t) 0 to 255
 */
void WheelController::forward(uint8_t speed) {
  this->setSpeed(this->min_speed_to_turn);
  this->turn_forward();
  // TODO make delay with millis
  this->setSpeed(speed);
}

/**
 * @brief sets all the motors to a specific speed backwards
 *
 * @param speed (uint8_t) 0 to 255
 */
void WheelController::backward(uint8_t speed) {
  this->forward(-speed);
}

void WheelController::stop() {
  this->forward(0);
}
void WheelController::stop(uint32_t milliseconds) {
  // TODO change delay to millis
  this->stop();
  delay(milliseconds);
}

void WheelController::slowStop() {
  int16_t speed;
  while (this->getMaxSpeed()) {
    for (uint8_t motor_index = 0; motor_index < this->nb_of_wheels; motor_index++) {
      speed = this->getSpeed(motor_index);
      this->incrementSpeed(motor_index, speed/2);
    }
  }
}

void WheelController::turn_abs(uint8_t servo_index, uint8_t angle) {
  if (this->servos_in_pos[servo_index] != nullptr and this->motor_speeds[servo_index] >= this->min_speed_to_turn) {
    this->servos_in_pos[servo_index]->write(angle);
  }
}

void WheelController::turn_abs(uint8_t angle) {
  this->turn_abs(0, 90 + angle);
  this->turn_abs(1, 90 + angle);
  this->turn_abs(4, 90 - angle);
  this->turn_abs(5, 90 - angle);
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

void WheelController::slowToSpeed_async(uint8_t speed, uint8_t newSpeed) {
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
  this->forward(0);
  while (1) {
  }
}
