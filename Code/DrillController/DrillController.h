#ifndef DRILL_CONTROLLER_H
#define DRILL_CONTROLLER_H

#include <Arduino.h>
#include <stdint.h>

class DrillController
{
private:
	/* data */
	const uint8_t StepperPas = 2; // STEPPER
	const uint8_t StepperDir = 3;

	const uint8_t MoteurDIR1 = 9; // DC
	const uint8_t MoteurPW1 = 10;

public:
	DrillController();
	~DrillController();
	void begin();
	void Descendre(bool descendre = 1, uint32_t nb_tour = 10000);
	void Remonter(uint32_t nb_tour = 10000);
	void ActiverRotation();
	void DesactiverRotation();
};

#endif
