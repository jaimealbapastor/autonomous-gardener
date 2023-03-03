#ifndef DRILL_HPP
#define DRILL_HPP

#include <stdint.h>

class DRILL {
///private:


 /// uint8_t _nb_of_motors = 0;


public:

 const int Pas = 3;
 const int Dir = 2;

 int dir = 8;
 int pwm = 9;

 void translation();
 void rotation();
 void systemdrill();
 void stop();



};

#endif