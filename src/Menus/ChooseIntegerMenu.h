#ifndef CHOOSEINTEGERMENU_H
#define CHOOSEINTEGERMENU_H

#include "Arduino.h"
#include "Menu.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class ChooseIntegerMenu: public virtual Menu {

private:
   String m_title;

public:
   ChooseIntegerMenu(Adafruit_SSD1306 *display, int FPS, String title, int startingValue);
   int currentValue;
   void refreshDisplay();
   void handleRotaryIncrease(int amount);
   void handleRotaryDecrease(int amount);
};


#endif
