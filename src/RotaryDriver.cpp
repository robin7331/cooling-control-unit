
#include "RotaryDriver.h"


const int PinCLK = PD2;                   // Used for generating interrupts using CLK signal
const int PinDT = PD4;                    // Used for reading DT signal
const int PinSW = PD3;                    // Used for the push button switch


RotaryDriver::RotaryDriver(int pinCLK, int pinDT, int pinSW, void (*interruptDispatch)(void)) {
   this->m_pinCLK = pinCLK;
   this->m_pinDT = pinDT;
   this->m_pinSW = pinSW;

   this->onRotaryTurn = NULL;
   this->onRotaryButton = NULL;

   pinMode(pinCLK,INPUT);
   pinMode(pinDT,INPUT);
   pinMode(pinSW,INPUT);
   attachInterrupt(0, interruptDispatch, FALLING);
}

void RotaryDriver::onInterrupt() {
   if (digitalRead(this->m_pinCLK)) {
      this->m_up = !digitalRead(this->m_pinDT);
   } else {
      this->m_up = digitalRead(this->m_pinDT);
   }

   this->m_turnDetected = true;
}


void RotaryDriver::update() {

   if (this->m_turnDetected)  {		    // do this only if rotation was detected
      if (this->swapDirection) {
         this->m_up = !this->m_up;
      }

      if (this->onRotaryTurn != NULL) {
         if (this->m_up) {
            this->onRotaryTurn(true, 1, this);
         } else {
            this->onRotaryTurn(false, 1, this);
         }
      }
      this->m_turnDetected = false;          // do NOT repeat IF loop until new rotation detected
   }

   if (digitalRead(this->m_pinSW) == false) {      // check if pushbutton is pressed
      if (millis() - this->m_lastButtonPress >= BUTTONDEBOUNCE) {

         if (this->m_buttonPressed == true) {
            return;
         }

         if (this->onRotaryButton != NULL) {
            this->onRotaryButton(this);
         }

         this->m_buttonPressed = true;
         this->m_lastButtonPress = millis();

      }
   } else {
      this->m_buttonPressed = false;
   }

}
