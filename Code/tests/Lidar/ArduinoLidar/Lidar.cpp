#include "Lidar.h"

Lidar::Lidar(){}  ///Constructeur

// Send X Y Z STRENGTH to the computer
// @TODO: reverse kinematics

void Lidar::send_pos(){
  if(distance == 0) return;
  uint16_t pulses = 0;
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

void Lidar::servo_pos(int angle){

  if(angle > SERVO_POS_MAX || angle < SERVO_POS_MIN)
  return;
    servo_g.write(180 - angle);
    servo_d.write(angle);
}

// Fetchs data from the Lidar
uint8_t getDistance(uint16_t * distance){

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