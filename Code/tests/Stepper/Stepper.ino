const int StepperPas = 2;  //STEPPER
const int StepperDir = 3;

int MoteurDIR1 = 9;  //DC
int MoteurPW1 = 10;



void setup() {
  Serial.begin(9600);

  pinMode(StepperPas, OUTPUT);  //STEPPER
  pinMode(StepperDir, OUTPUT);
  digitalWrite(StepperDir, HIGH);

  pinMode(MoteurDIR1, OUTPUT);  //DC
  pinMode(MoteurPW1, OUTPUT);
}

void AvancerStepper() {
  digitalWrite(StepperDir, HIGH);
  for (int x = 0; x < 6000; x++) {  ///x = nombre de tours
    digitalWrite(StepperPas, HIGH);
    delayMicroseconds(500);
    digitalWrite(StepperPas, LOW);
    delay(4);
  }
}

void ReculerStepper() {
  digitalWrite(StepperDir, LOW);
  for (int x = 0; x < 6000; x++) {  ///x = nombre de tours
    digitalWrite(StepperPas, HIGH);
    delayMicroseconds(50);
    digitalWrite(StepperPas, LOW);
    delayMicroseconds(50);
  }
}

void AvancerDC() {

  digitalWrite(MoteurDIR1, 1);  ///tourner vers l'avant moteur
  analogWrite(MoteurPW1, 255);
  delay(3000);
  analogWrite(MoteurPW1, 0);
}

void ReculerDC() {

  digitalWrite(MoteurDIR1, 0);  ///tourner vers l'arrière moteur
  analogWrite(MoteurPW1, 255);
  delay(3000);
  analogWrite(MoteurPW1, 0);
}


void loop() {
  //if robot à l'arrêt alors
  //AvancerStepper();
  //AvancerDC();
  ReculerStepper();
  delay(4000);  
}
