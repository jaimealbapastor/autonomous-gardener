#include "Lidar.hpp" ///Importation des fichiers

Lidar Ld;         ///abréviation pour pouvoir faire référence au classe lors d'appel de fonction

void setup(){

  // Serial ports
  Serial.begin(9600); // USB
  Serial.println("Go!");
  
  //Lidar
  Wire.begin();
    #ifdef FAST_I2C
        #if ARDUINO >= 157
            Wire.setClock(400000UL); // Set I2C frequency to 400kHz (for Arduino Due)
        #else
            TWBR = ((F_CPU / 400000UL) - 16) / 2; // Set I2C frequency to 400kHz
        #endif
    #endif

    // Configure the LidarLite internal parameters so as to lend itself to
    // various modes of operation by altering 'configure' input integer to
    // anything in the range of 0 to 5. See LIDARLite_v3HP.cpp for details.
    myLidarLite.configure(0);
    
  // Stepper
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  digitalWrite(DIR_PIN, HIGH);
  
  // Servos
  servo_g.attach(SERVO_G_PIN);
  servo_d.attach(SERVO_D_PIN);
  Ld.servo_pos(servo_angle);
}

void loop(){

  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(TIME_PER_PULSE);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(TIME_PER_PULSE);
  pulses ++;

  if((pulses + offset)%PULSE_PER_DATAPOINT == 0){
    getDistance(&distance);
    Ld.send_pos();
  }

  if(pulses == PULSE_PER_REV) {
    pulses = 0;
    servo_angle += servo_dir;
    if(servo_angle > SERVO_POS_MAX || servo_angle < SERVO_POS_MIN){
      servo_dir = -servo_dir;
    }
    Ld.servo_pos(servo_angle);
  }
}