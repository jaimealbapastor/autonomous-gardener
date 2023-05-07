#include "DrillController.h"

DrillController::DrillController() {
}

DrillController::~DrillController() {
}

void DrillController::begin() {
  pinMode(this->StepperPas, OUTPUT);  // STEPPER
  pinMode(this->StepperDir, OUTPUT);

  pinMode(this->MoteurDIR1, OUTPUT);  // DC
  pinMode(this->MoteurPW1, OUTPUT);

  digitalWrite(this->MoteurDIR1, 1);
}

void DrillController::Descendre(uint32_t nb_tour = 10000, bool descendre = 1) {
  digitalWrite(this->StepperDir, descendre);
  for (uint32_t x = 0; x < nb_tour; x++) {
    digitalWrite(this->StepperPas, HIGH);
    delayMicroseconds(50);
    digitalWrite(this->StepperPas, LOW);
    delayMicroseconds(50);
  }
}

void DrillController::Remonter(uint32_t nb_tour = 10000) {
  this->Descendre(nb_tour, 0);
}

void DrillController::ActiverRotation() {
  analogWrite(this->MoteurPW1, 255);
}

void DrillController::DesactiverRotation() {
  analogWrite(this->MoteurPW1, 0);
}
