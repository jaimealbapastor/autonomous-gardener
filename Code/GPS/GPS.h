#ifndef GPS_HPP
#define GPS_HPP

#include <stdint.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

class GPS {
private:


public:

 static const int RXPin = 2, TXPin = 3;
 static const uint32_t GPSBaud = 9600;
 // The TinyGPS++ object
 TinyGPSPlus gps;
 // The serial connection to the GPS device
 SoftwareSerial ss(RXPin, TXPin);

 void smartDelay();
 void printFloat();
 void printInt();
 void printDateTime();
 void printStr();  

};

#endif