
// Includes
#include <Servo.h>
#include <Wire.h>
#include <LIDARLite_v3HP.h>

// Lidar
LIDARLite_v3HP myLidarLite;
uint16_t distance = 0;

// Servos
Servo servo_g, servo_d;
#define SERVO_G_PIN 6
#define SERVO_D_PIN 9
#define SERVO_POS_NEUTRAL 90
#define SERVO_POS_MIN SERVO_POS_NEUTRAL - 40
#define SERVO_POS_MAX SERVO_POS_NEUTRAL + 40
int servo_angle = SERVO_POS_MIN;

// Stepper
#define DIR_PIN 2 
#define STEP_PIN 3
#define STEPS_PER_REV 200
#define PULSE_PER_REV 3200 // PPR_motor * Gear_reduction * Microstepping = 200*1*16
#define TIME_PER_REV 500.0f // ms
const int TIME_PER_PULSE = (TIME_PER_REV * 1000.0f)/ PULSE_PER_REV; // us
const int PULSE_PER_DATAPOINT = 1;

// External communication
char serial_buffer[15];
float theta,phi,rho;

// the setup function runs once when you press reset or power the board
void setup() {
  // Serial ports
  Serial.begin(9600); // USB
  Serial.println("Yolo!");
  
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
  servo_pos(servo_angle);
}

// Scanning fuction. Adapt to your needs!
uint16_t pulses = 0;
int8_t servo_dir = 1;
int8_t offset = 0;
void loop() {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(TIME_PER_PULSE);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(TIME_PER_PULSE);
  pulses ++;

  if((pulses + offset)%PULSE_PER_DATAPOINT == 0){
    getDistance(&distance);
    send_pos();
  }

  if(pulses == PULSE_PER_REV) {
    pulses = 0;
    servo_angle += servo_dir;
    if(servo_angle > SERVO_POS_MAX || servo_angle < SERVO_POS_MIN){
      servo_dir = -servo_dir;
    }
    servo_pos(servo_angle);
  }
}

// Send X Y Z STRENGTH to the computer
// @TODO: reverse kinematics
void send_pos(){
  if(distance == 0) return;
  
  theta = (float)pulses*360.0f/PULSE_PER_REV; //compute angle from motor pulses
  theta *= PI / 180.0f; // convert to radians
  
  phi = (float)servo_angle*-0.3f+71; // compute angle from servo geometry
  phi = 2*phi - 90.0f; // compute mirror bounce angle
  phi *= PI / 180.0f; // convert to radians
  
  rho = distance - 5.5f; // rho is the LIDAR distance
  
  sprintf(serial_buffer,"%d\t%d\t%d\t",(int)(rho*cos(phi)*cos(theta)),(int)(rho*cos(phi)*sin(theta)),(int)(rho*sin(phi)));
  Serial.println(serial_buffer);
}

// Move both servos to change the mirror angle
void servo_pos(int angle){
  if(angle > SERVO_POS_MAX || angle < SERVO_POS_MIN)
  return;
    servo_g.write(180 - angle);
    servo_d.write(angle);
}

// Fetchs data from the Lidar
uint8_t getDistance(uint16_t * distance)
{
    uint8_t newDistance = 0;

    // Check on busyFlag to indicate if device is idle
    // (meaning = it finished the previously triggered measurement)
    if (myLidarLite.getBusyFlag() == 0)
    {
        // Trigger the next range measurement
        myLidarLite.takeRange();
  
        // Read new distance data from device registers
        *distance = myLidarLite.readDistance();
  
        // Report to calling function that we have new data
        newDistance = 1;
    }

    return newDistance;
}