#include "DrillController.h"

DrillController Drill;

/**
 * @brief Construct a new Drill Controller:: Drill Controller object
 *
 */
DrillController::DrillController()
{
}

DrillController::~DrillController()
{
}
/**
 * @brief Setup du système de percage du sol
 *
 */
void DrillController::begin()
{
	pinMode(this->StepperPas, OUTPUT); // STEPPER
	pinMode(this->StepperDir, OUTPUT);

	pinMode(this->MoteurDIR1, OUTPUT); // DC
	pinMode(this->MoteurPW1, OUTPUT);

	digitalWrite(this->MoteurDIR1, 1);
}

/**
 * @brief Descente du forêt pour creuser
 *
 * @param nb_tour que le stepper fait pour descendre à un endroit précis
 * @param descendre direction du stepper pour descendre
 * @param delay permet la rapidité de descente du système
 */
void DrillController::Descendre(uint32_t nb_tour = 10000, bool descendre = 1, uint16_t delay = 200)
{
	digitalWrite(this->StepperDir, descendre);
	for (uint32_t x = 0; x < nb_tour; x++)
	{
		digitalWrite(this->StepperPas, HIGH);
		delayMicroseconds(delay);
		digitalWrite(this->StepperPas, LOW);
		delayMicroseconds(delay);
	}
}

/**
 * @brief descendre le forêt avant qu'il soit dans le sol
 *
 * @param nb_tour
 */
void DrillController::DescendreRapide(uint32_t nb_tour = 10000)
{
	this->Descendre(nb_tour, 1, 50);
}

/**
 * @brief Remonte le forêt pour être rangé dans le chassis
 *
 * @param nb_tour pour revenir à l'endroit initial
 */
void DrillController::Remonter(uint32_t nb_tour = 10000, uint16_t delay = 200)
{
	this->Descendre(nb_tour, 0, delay);
}

/**
 * @brief remonte le forêt après être sorti du sol
 *
 * @param nb_tour
 */
void DrillController::RemonterRapide(uint32_t nb_tour = 10000)
{
	this->Remonter(nb_tour, 50);
}

/**
 * @brief faire tourner le forêt pour creuser
 *
 */
void DrillController::ActiverRotation()
{
	digitalWrite(this->MoteurPW1, 1);
}

/**
 * @brief désactive le moteur pour remonter la terre
 *
 */
void DrillController::DesactiverRotation()
{
	analogWrite(this->MoteurPW1, 0);
}

/**
 * @brief Système forage du début à la fin
 *
 */
void DrillController::Creuser(uint16_t tours_air = 20000, uint16_t tours_terre = 30000)
{
	this->DescendreRapide(tours_air);
	this->ActiverRotation();
	this->Descendre(tours_terre);
	this->DesactiverRotation();
	this->Remonter(tours_terre);
	this->RemonterRapide(tours_air);
}
