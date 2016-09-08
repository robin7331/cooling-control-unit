
#ifndef MENU_H
#define MENU_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Menu {

private:
   uint8_t m_fps;
   unsigned long m_refreshTimer;

public:
   Adafruit_SSD1306 *display;
   Menu(Adafruit_SSD1306 *display = NULL, int FPS = 1);
   virtual void refreshDisplay() = 0;
   virtual bool handleRotaryPress();
   virtual void handleRotaryIncrease(int amount);
   virtual void handleRotaryDecrease(int amount);
   virtual void update();
};

#endif
