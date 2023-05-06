#include "WheelController.h"
#include "BTController.h"

void setup()
{
	Serial.begin(9600);
	Wheels.begin();
	Bluetooth.begin();
}

void loop()
{
	Bluetooth.checkCommand();
}