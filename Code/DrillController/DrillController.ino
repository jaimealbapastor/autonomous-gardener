#include "DrillController.h"

DrillController Drill;

void setup()
{
  Serial.begin(9600);
  Drill.begin();
}

void loop()
{
  Drill.ActiverRotation();
  Drill.Descendre();
  Drill.DesactiverRotation();
  Drill.Remonter();
  delay(2000);
}
