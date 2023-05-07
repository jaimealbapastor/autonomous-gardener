#ifndef DRILL_CONTROLLER_H
#define DRILL_CONTROLLER_H

#include <Arduino.h>
#include <stdint.h>

class DrillController
{
private:
	/* data */
	const uint8_t StepperPas = 39; // STEPPER
	const uint8_t StepperDir = 38;

	const uint8_t MoteurDIR1 = 40; // DC
	const uint8_t MoteurPW1 = 41;

	void Descendre(uint32_t nb_tour = 10000, bool descendre = 1, uint16_t delay = 200);
	void Remonter(uint32_t nb_tour = 10000, uint16_t delay = 200);

	void ActiverRotation();
	void DesactiverRotation();

public:
	DrillController();
	~DrillController();
	void begin();

	void DescendreRapide(uint32_t nb_tour = 10000);
	void RemonterRapide(uint32_t nb_tour = 10000);
	void Creuser(uint16_t tours_air = 20000, uint16_t tours_terre = 30000);
};

extern DrillController Drill;

#endif
