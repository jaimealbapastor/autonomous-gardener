#include "DrillController.h"

DrillController::DrillController()
{
}

DrillController::~DrillController()
{
}

void DrillController::begin()
{
	pinMode(this->StepperPas, OUTPUT); // STEPPER
	pinMode(this->StepperDir, OUTPUT);

	pinMode(this->MoteurDIR1, OUTPUT); // DC
	pinMode(this->MoteurPW1, OUTPUT);
}

void DrillController::AvancerStepper(bool descendre = 1, uint32_t nb_tour = 10000)
{
	digitalWrite(this->StepperDir, descendre);
	for (uint32_t x = 0; x < nb_tour; x++)
	{
		digitalWrite(this->StepperPas, HIGH);
		delayMicroseconds(50);
		digitalWrite(this->StepperPas, LOW);
		delayMicroseconds(50);
	}
}

void DrillController::ReculerStepper(uint32_t nb_tour = 10000)
{
	this->AvancerStepper(0, nb_tour);
}

void DrillController::AvancerDC(bool droite = 1)
{
	digitalWrite(this->MoteurDIR1, droite); /// tourner vers l'avant moteur
	analogWrite(this->MoteurPW1, 255);
	delay(3000);
	analogWrite(this->MoteurPW1, 0);
}

void DrillController::ReculerDC()
{
	this->AvancerDC(0);
}