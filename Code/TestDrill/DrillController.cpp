#include "DrillController.h"

DrillController::DrillController() {}

DrillController::~DrillController() {}

/**
 * @brief Initialize les pinMode des moteurs
 *
 */
void DrillController::begin()
{
    pinMode(this->stepper_dir, OUTPUT);
    pinMode(this->stepper_step, OUTPUT);

    pinMode(this->dc_dir, OUTPUT);
    pinMode(this->dc_pwm, OUTPUT);
}

/**
 * @brief Translation du stepper pour descendre le drill
 *
 */
void DrillController::translation(Pas, Dir) // FIXME il manque le type des arguments
{
    for (int nb_tour = 0; nb_tour < 600; nb_tour++) // TODO le type int functionne mais n'est pas le plus adapté (demande à Jaime)
    {
        digitalWrite(Pas, HIGH);
        delayMicroseconds(500);
        digitalWrite(Pas, LOW);
        delayMicroseconds(500);
    }
    delay(1000);
}

/**
 * @brief Rotation du drill pour creuser
 *
 */
void DrillController::rotation(pwm, dir) // FIXME il manque le type des arguments
{
    for (int motor_cc = 0; motor_cc > 255; motor_cc++) // BUG il y a une petite erreur, la boucle ne s'executera pas
    {
        digitalWrite(pwm, HIGH);
        Serial.println("avant");
        delay(300);
    }
}

// TODO décrire et expliquer ce que fait cette fonction
void DrillController::systemdrill()
{
    /// position 0 : drill rangé
    /// position 1 : drill en bas
    /// changement position 0 à 1 et drill tourne

    /// premiere idée:
    if (position == 0) // FIXME 'position' n'est pas défini
    {
        translation(Pas, Dir); // FIXME 'Pas' et 'Dir' ne sont pas définis
        rotation(pwm, dir);    // FIXME 'pwm' et 'dir' ne sont pas définis
    }
}

// TODO décrire et expliquer ce que fait cette fonction
void DrillController::stop()
{
}
