
#ifndef TEMPMENU_H
#define TEMPMENU_H

#include "Arduino.h"
#include "Menu.h"


class TempMenu: public virtual Menu {

private:
   float _inletTemp;
   float _hotExhaustTemp;
   float _coldExhaustTemp;
   float _hotPeltierTemp;
   float _coldPeltierTemp;

   float roundNumber(float number);

public:
   TempMenu(Adafruit_SSD1306 *display, int FPS);
   void sayHi();
   void refreshDisplay();

   void setInletTemp(float temp, bool refresh = false);
   void setHotExhaustTemp(float temp, bool refresh = false);
   void setColdExhaustTemp(float temp, bool refresh = false);
   void setHotPeltierTemp(float temp, bool refresh = false);
   void setColdPeltierTemp(float temp, bool refresh = false);
};



#endif
