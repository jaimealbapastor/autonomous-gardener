#include "WheelController.h"
#include "Async.h"

// ======= CONSTRUCTORS =======

/**
 * @brief Construct a new WheelController:: WheelController object.
 * It controls the 6 motors of the E-Gaia autonomous robot.
 *
 * @param direction_pins 6 element list of uint8_t
 * @param pwd_pins 6 element list of uint8_t
 */
WheelController::WheelController(uint8_t direction_pins[], uint8_t pwd_pins[]) {
  for (uint8_t i = 0; i < this->_nb_of_motors; i++) {
    this->_dir_pins[i] = direction_pins[i];
    this->_pwm_pins[i] = pwd_pins[i];
    this->_motor_speeds[i] = 0;
    this->_motor_dir[i] = 1;
  }
}

WheelController::~WheelController() {}

// ======= PRIVATE =======

// ======= PUBLIC =======

/**
 * @brief Set speed of the specified motors
 *
 * @param motors uint8_t list of the motors which speed will be changed
 * @param pwm_speeds unint_8 list of the speeds in pwm (0 to 255)
 * @param size the size 'motors' and 'pwm_speeds'
 */
void WheelController::setSpeed(uint8_t motors[], int8_t pwm_speeds[], uint8_t size) {
  // TODO create token for most used combinations (all, right, left)

  // compute the sign and pwm-speeds (255) of each speed

  for (uint8_t i = 0; i < size; i++) {
    uint8_t mi = motors[i];  // mi stands for "motor index", aka the indexes of _dir_pins, _pwm_pins, _motor_speeds and _motor_dir

    if (pwm_speeds[i] > 0)
      this->_motor_dir[mi] = 1;  // sign of the speed, i.e. 1 for positive speed and -1 for negative speed
    else
      this->_motor_dir[mi] = -1;

    pwm_speeds[i] = pwm_speeds[i] * this->_motor_dir[mi];  // absolute value of the speed

    this->_motor_speeds[mi] = pwm_speeds[i];
    if (pwm_speeds[i] >= this->_max_speed)
      this->_motor_speeds[mi] = this->_max_speed;  // if the speed is too high, set it to the maximum
  }

  // Separate the loops so all motors start at the 'same' time
  for (uint8_t i = 0; i < size; i++) {
    uint8_t mi = motors[i];
    // WRITE IN PINS
    // TODO SEPARAR EN OTRA FUNCCION DE CLASE
    analogWrite(this->_pwm_pins[mi], this->_motor_speeds[mi]);

    Serial.print("Motor ");
    Serial.print(mi);
    Serial.print(" (pin ");
    Serial.print(this->_pwm_pins[mi]);
    Serial.print(") \ta velocidad ");
    Serial.print(this->_motor_speeds[mi]);
    Serial.print(" \tdireccion ");
    Serial.println(this->_motor_dir[mi]);

    if (this->_motor_dir[mi] == 1)
      digitalWrite(this->_dir_pins[mi], 1);
    else
      digitalWrite(this->_dir_pins[mi], 0);
  }

  // TODO add arduino : analogueWrite()
}

void WheelController::incrementSpeed(uint8_t motors[], int8_t increments[], uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {
    uint8_t mi = motors[i];  // mi stands for "motor index"
    if (this->getSpeeds()[mi] + increments[i] >= 0 || this->getSpeeds()[mi] + increments[i] <= this->_max_speed)
      this->getSpeeds()[mi] += increments[i];
  }
}

/**
 * @return uint8_t the number of motors
 */
uint8_t WheelController::getNumberOfMotors() {
  return this->_nb_of_motors;
}

uint8_t *WheelController::getDirections() {
  return this->_motor_dir;
}

uint8_t *WheelController::getSpeeds() {
  return this->_motor_speeds;
}

/**
 * @brief sets all the motors to a specific speed forwards
 *
 * @param speed (uint8_t) 0 to 255
 */
void WheelController::forward(uint8_t speed) {
  uint8_t motors[] = { 0, 1, 2, 3, 4, 5 };
  int8_t speeds[] = { speed, -speed, speed, -speed, speed, -speed };
  this->setSpeed(motors, speeds, this->_nb_of_motors);
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

void WheelController::slowToSpeed_async(uint8_t speed, uint8_t newSpeed) {
  int step = 1;
  if (speed > newSpeed)
    step = -1;
  for (int i = speed; i != newSpeed; i += step) {
    //analogWrite(pwdPin, i);
    delay(20);

    if ((i < 0) || (i > 256)) {
      //analogWrite(pwdPin, 0);
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
