

void setup() {
Serial.begin(115200);
pinMode(Pas,OUTPUT);
pinMode(Dir,OUTPUT);                ///setup moteur stepper du tuto Masson
digitalWrite(Dir,HIGH);

pinMode(dir, OUTPUT);
pinMode(pwm, OUTPUT);               ///setup du moteur cc du tuto Masson
digitalWrite(pwm, LOW);
digitalWrite(dir, LOW);
Serial.begin(9600);
}

void loop() {
    translation(Pas, Dir);
    rotation(pwm, dir)
}