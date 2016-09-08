
#ifndef MENUSCROLLER_H
#define MENUSCROLLER_H

#include "Menu.h"

#include "Menus.h"
#include "RotaryDriver.h"


class MenuScroller {

private:
   uint8_t m_currentIndex;
   Menu *m_menus[MENU_COUNT];

public:
   MenuScroller();

   void nextMenu();
   void previousMenu();
   void setMenu(uint8_t index);
   Menu* currentMenu();
   void addMenu(Menu *menu, uint8_t index);


   void handleRotaryTurn(bool clockwise, int amount, RotaryDriver *rotaryDriver);
   void handleButtonPress(RotaryDriver *rotaryDriver);
};

#endif
