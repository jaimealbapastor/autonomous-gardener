#include "DrillController.h"

DrillController Drill;

void setup()
{
  Serial.begin(9600);
  Drill.begin();
}

void loop()
{
  Drill.AvancerStepper();
  Drill.AvancerDC();
  Drill.ReculerStepper();
  delay(2000);
}
