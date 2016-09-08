#include "ChooseIntegerMenu.h"
#include <SPI.h>
#include <Wire.h>


#define OLED_RESET 4

ChooseIntegerMenu::ChooseIntegerMenu(Adafruit_SSD1306 *display, int FPS, String title, int startingValue) : Menu(display, FPS) {
   this->m_title = title;
   this->currentValue = startingValue;
}

void ChooseIntegerMenu::handleRotaryIncrease(int amount) {
   this->currentValue += amount;
   this->refreshDisplay();
}

void ChooseIntegerMenu::handleRotaryDecrease(int amount) {
   this->currentValue -= amount;
   this->refreshDisplay();
}


void ChooseIntegerMenu::refreshDisplay() {

   this->display->clearDisplay();
   this->display->setTextSize(1);
   // this->display->setTextColor(WHITE);

   // Print Table Header
   this->display->setCursor(12,0);
   this->display->print(this->m_title);


   this->display->setTextSize(2);
   this->display->setCursor(12, 12);
   this->display->print(this->currentValue);
   this->display->print("%");

   this->display->display();
}
