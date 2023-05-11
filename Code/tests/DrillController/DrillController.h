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
	void Descendre(uint32_t nb_tour = 10000, bool descendre = 1);
	void Remonter(uint32_t nb_tour = 10000);

	void DescendreRapide(uint32_t nb_tour = 10000);
	void RemonterRapide(uint32_t nb_tour = 10000);

	void ActiverRotation();
	void DesactiverRotation();

	void Creuser(uint16_t tours_air = 20000, uint16_t tours_terre = 30000);
};

#endif
