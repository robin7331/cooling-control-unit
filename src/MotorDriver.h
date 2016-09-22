#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include "Arduino.h"


class MotorDriver {

private:
   bool m_motorADirection;
   bool m_motorBDirection;

public:
   enum Motor
   {
      MOTOR_A,
      MOTOR_B
   };
   MotorDriver();
   void setSpeed(Motor motor, float percentage);
   void setDirection(Motor motor, bool clockwise);
   void stop();

};

#endif
