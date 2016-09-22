
#include "MenuScroller.h"

MenuScroller::MenuScroller() {

}

void MenuScroller::handleRotaryTurn(bool clockwise, int amount, RotaryDriver *rotaryDriver) {
      if (clockwise) {
         this->currentMenu()->handleRotaryIncrease(amount);
      } else {
         this->currentMenu()->handleRotaryDecrease(amount);
      }
}

void MenuScroller::handleButtonPress(RotaryDriver *rotaryDriver) {
   if (this->currentMenu()->handleRotaryPress()) {
      this->nextMenu();
   }
}

void MenuScroller::setMenu(uint8_t index) {
   if (index <= (MENU_COUNT - 1)) {
      this->m_currentIndex = index;
   } else {
      this->m_currentIndex = 0;
   }
}

void MenuScroller::nextMenu() {
   this->m_currentIndex ++;

   if (this->m_currentIndex > (MENU_COUNT - 1))
      this->m_currentIndex = 0;

   this->currentMenu()->refreshDisplay();
}

void MenuScroller::previousMenu() {
   this->m_currentIndex --;
   if (this->m_currentIndex < 0)
      this->m_currentIndex = (MENU_COUNT - 1);
}

Menu* MenuScroller::currentMenu() {
   return this->m_menus[this->m_currentIndex];
}

void MenuScroller::addMenu(Menu *menu, uint8_t index) {
   this->m_menus[index] = menu;
}
