#include "DrillController.h"

void setup()
{
    Serial.begin(9600);
    Drill.begin(); // FIXME 'Drill' n'est pas défini, il faut le créer avant setup
}

void loop()
{
    Drill.translation(Pas, Dir); // FIXME 'Pas' et 'Dir' ne sont pas définis
    Drill.rotation(pwm, dir);    // FIXME 'pwm' et 'dir' ne sont pas définis
}