#ifndef CHOOSEINTEGERMENU_H
#define CHOOSEINTEGERMENU_H

#include "Arduino.h"
#include "Menu.h"
#include "MotorDriver.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class ChooseIntegerMenu: public virtual Menu {

private:
   int m_minValue, m_maxValue;
   String m_title;
   MotorDriver *m_motorDriver;
   MotorDriver::Motor m_motor;

public:
   ChooseIntegerMenu(Adafruit_SSD1306 *display, int FPS, String title, int startingValue, int motorNo, int minValue = 0, int maxValue = 100);
   int currentValue;
   virtual void refreshDisplay();
   void handleRotaryIncrease(int amount);
   void handleRotaryDecrease(int amount);
};


#endif
