#ifndef ROTARYDRIVER_H
#define ROTARYDRIVER_H

#include "Arduino.h"

#define BUTTONDEBOUNCE 100

class RotaryDriver {

private:
   volatile boolean m_turnDetected;
   volatile boolean m_up;
   bool m_buttonPressed;
   unsigned long m_lastButtonPress;
   int m_pinCLK;
   int m_pinDT;
   int m_pinSW;


public:
   RotaryDriver(int pinCLK, int pinDT, int pinSW, void (*interruptDispatch)(void));
   bool swapDirection = false;
   void update();
   void onInterrupt();
   void (*onRotaryTurn)(bool clockwise, int amount, RotaryDriver *driver);
   void (*onRotaryButton)(RotaryDriver *driver);
};

#endif
