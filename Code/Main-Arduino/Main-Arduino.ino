#include "WheelController.h"
#include "BTController.h"
#include "DrillController.h"

void setup()
{
	Serial.begin(9600);
	Wheels.begin();
	Drill.begin();
	Bluetooth.begin();
}

void loop()
{
	Bluetooth.checkCommand();
}