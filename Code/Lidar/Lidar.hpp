#ifndef LIDAR_H
#define LIDAR_H

// Includes
#include <Servo.h>
#include <Wire.h>
#include <LIDARLite_v3HP.h>

// Servos
#define SERVO_G_PIN 6
#define SERVO_D_PIN 9
#define SERVO_POS_NEUTRAL 90
#define SERVO_POS_MIN SERVO_POS_NEUTRAL - 40
#define SERVO_POS_MAX SERVO_POS_NEUTRAL + 40

// Stepper
#define DIR_PIN 2 
#define STEP_PIN 3
#define STEPS_PER_REV 200
#define PULSE_PER_REV 3200 // PPR_motor * Gear_reduction * Microstepping = 200*1*16
#define TIME_PER_REV 500.0f // ms

class Lidar   /// Definition de ma classe Lidar
{

private:
    // External communication
    char serial_buffer[15];
    float theta,phi,rho;

    // Scanning function. Adapt to your needs!
    uint16_t pulses = 0;
    int8_t servo_dir = 1;
    int8_t offset = 0;

public:
    // Lidar
    LIDARLite_v3HP myLidarLite;
    uint16_t distance = 0;

    //Servo
    Servo servo_g, servo_d;
    int servo_angle = SERVO_POS_MIN;

    //Stepper
    const int TIME_PER_PULSE = (TIME_PER_REV * 1000.0f)/ PULSE_PER_REV; // us
    const int PULSE_PER_DATAPOINT = 1;

    void send_pos();
    void servo_pos(int angle);
    uint8_t getDistance(uint16_t * distance);

};

#endif