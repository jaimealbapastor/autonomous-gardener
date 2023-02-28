#include "DRILL.h"

DRILL::~DRILL() {}


void DRILL::translation(Pas, Dir){
    for(int nb_tour = 0; nb_tour < 600; nb_tour++) {    ///translation du stepper pour descendre le drill
    digitalWrite(Pas,HIGH);
    delayMicroseconds(500);
    digitalWrite(Pas,LOW);
    delay(4);
    }
delay(1000);
}

void DRILL::rotation(pwm, dir){     
    for (int motor_cc = 0; motor_cc > 255; motor_cc++){     ///rotation du drill pour creuser
        digitalWrite(pwm, HIGH);
        Serial.println("avant");
        delay(300);
  }
}

void DRILL::stop(){

}
