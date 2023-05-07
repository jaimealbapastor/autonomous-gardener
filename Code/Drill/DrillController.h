#ifndef DRILL_CONTROLLER_H
#define DRILL_CONTROLLER_H

#include <Arduino.h>
#include <stdint.h>

class DrillController
{
private:
	const uint8_t stepper_dir = 2;
	const uint8_t stepper_pas = 3;

	const uint8_t dc_dir = 8;
	const uint8_t dc_pwm = 9;

	/// uint8_t _nb_of_motors = 0;

public:
	// Constructors
	void DrillController();
	void ~DrillController();

	void begin();

	void translation();
	void rotation();
	void systemdrill();
	void stop();
};

#endif