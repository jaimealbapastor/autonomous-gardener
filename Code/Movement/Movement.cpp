#include "Wheels.hpp"

/**
 * @brief Construct a new Wheels::wheels object
 *
 * @param direction_pins, pwd_pins (uint8_t []) dir and pwd pins for each motor
 * @param size (uint8_t)
 */
Wheels::wheels(uint8_t direction_pins[], uint8_t pwd_pins[], uint8_t size)
{
    for (uint8_t i = 0; i < size and i < this->_max_nb_of_motors; i++)
    {
        this->_dirPins[i] = direction_pins[i];
        this->_pwdPins[i] = pwd_pins[i] this->_motor_speeds[i] = this->_max_speed;
        this->_motor_dir[i] = 1;
        this->_nb_of_motors++;
    }
}

Wheels::wheels()
{
}

/**
 * @brief Destroy the Wheels::wheels object
 *
 */
Wheels::~wheels()
{
}

void Wheels::setSpeed(uint8_t motors[], int8_t percent_speeds[], uint8_t size)
{
    // compute the sign and pwm-speeds (255) of each speed

    for (uint8_t i = 0; i < size; i++)
    {
        uint8_t mi = motors[i]; // mi stands for "motor index"

        this->_motor_dir[mi] = (percent_speeds[i] > 0) - (percent_speeds[i] < 0); // sign of the speed, i.e. 1 for positive speed and -1 for negative speed
        percent_speeds[i] *= signature[mi];                                       // make speed positive

        if (percent_speeds[i] >= 100)
            this->_motor_speeds[mi] = this->_max_speed; // set speed limit
        else
            this->_motor_speeds[mi] = percent_speeds[i] * this->_max_speed / 100; // cross product : from % to 255
    }
}

uint8_t Wheels::getNumberOfMotors()
{
    return this->_nb_of_motors;
}

uint8_t *Wheels::getDirections()
{
    return this->_motor_dir;
}

uint8_t *Wheels::getSpeeds()
{
    return this->_motor_speeds;
}

void Wheels::forward()
{
}
