
#include "Menu.h"


Menu::Menu(Adafruit_SSD1306 *display, int FPS) {
   this->display = display;
   this->m_fps = FPS;

}

void Menu::update() {

   if (millis() - this->m_refreshTimer >= (1000UL / this->m_fps )) {
      this->refreshDisplay();
      this->m_refreshTimer = millis();
   }
}

bool Menu::handleRotaryPress() {
   return true;
}

void Menu::handleRotaryDecrease(int amount) {}
void Menu::handleRotaryIncrease(int amount) {}
