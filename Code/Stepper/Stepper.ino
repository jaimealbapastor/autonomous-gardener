const int Pas = 3;        //STEPPER
const int Dir = 2;

int MoteurDIR1 = 10;    //DC
int MoteurPW1 = 9;



void setup() {
Serial.begin(115200);

pinMode(Pas,OUTPUT);    //STEPPER
pinMode(Dir,OUTPUT);
digitalWrite(Dir,HIGH);

pinMode(MoteurDIR1, OUTPUT);    //DC
pinMode(MoteurPW1, OUTPUT);
}

void AvancerStepper(){
for(int x = 0; x < 600; x++) { ///x = nombre de tours
digitalWrite(Pas,HIGH);
delayMicroseconds(500);
digitalWrite(Pas,LOW);
delay(4);
}
delay(1000);
}

void ReculerStepper(){

}

void AvancerDC() {

  analogWrite(MoteurDIR1, 0);  ///tourner vers l'avant moteur
  analogWrite(MoteurPW1, 127);
}

void ReculerDC() {

  analogWrite(MoteurDIR1, 127);  ///tourner vers l'arrière moteur
  analogWrite(MoteurPW1, 127);
}


void loop() {
  //if robot à l'arrêt alors
  AvancerStepper();
  AvancerDC();
  delay(4000);
  ReculerDC();
  ReculerStepper();
}