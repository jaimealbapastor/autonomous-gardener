#include "BTController.h"

void setup()
{
  Controller.begin();
  Serial.begin(9600);
  Serial.println("ATcommand"); // ATcommand Start
}

char msg;

void loop()
{
  Controller.checkCommand();
  // if (Serial1.available()) {

  //   msg = Serial1.read();
  //   Serial.print(msg);

  //   Serial.print("\t isNumber ");
  //   Serial.print(BTCommander::isNumber(msg) ? "True" : "False");

  //   if (BTCommander::isNumber(msg)) {
  //     Serial.print("\t -> ");
  //     Serial.print(BTCommander::toInt(msg));
  //   }
  //   Serial.println("\t|");
  // }
}