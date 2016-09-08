#include "TempMenu.h"
#include <SPI.h>
#include <Wire.h>


#define OLED_RESET 4

TempMenu::TempMenu(Adafruit_SSD1306 *display, int FPS) : Menu(display, FPS) {

}

void TempMenu::sayHi() {

   this->display->clearDisplay();
   this->display->setTextSize(1);
   this->display->setTextColor(WHITE);
   this->display->setCursor(0,10);
   this->display->print("      Booting...");
   this->display->display();

}


void TempMenu::setInletTemp(float temp, bool refresh) {
   this->_inletTemp = temp;
   if (refresh) {
      this->refreshDisplay();
   }
}

void TempMenu::setHotExhaustTemp(float temp, bool refresh) {
   this->_hotExhaustTemp = temp;
   if (refresh) {
      this->refreshDisplay();
   }
}

void TempMenu::setColdExhaustTemp(float temp, bool refresh) {
   this->_coldExhaustTemp = temp;
   if (refresh) {
      this->refreshDisplay();
   }
}

void TempMenu::setHotPeltierTemp(float temp, bool refresh) {
   this->_hotPeltierTemp = temp;
   if (refresh) {
      this->refreshDisplay();
   }
}

void TempMenu::setColdPeltierTemp(float temp, bool refresh) {
   this->_coldPeltierTemp = temp;
   if (refresh) {
      this->refreshDisplay();
   }
}

void TempMenu::refreshDisplay() {
   this->display->clearDisplay();
   this->display->setTextSize(1);

   // Print Table Header
   this->display->setCursor(12,0);
   this->display->print("EXHST");

   this->display->setCursor(55,0);
   this->display->print("PLTR");

   this->display->setCursor(95,0);
   this->display->print("INLT");

   // Print H and C indicators
   this->display->setCursor(0,10);
   this->display->print("H");

   this->display->setCursor(0,21);
   this->display->print("C");

   // Hot Exhaust Temp
   this->display->setCursor(12, 10);
   this->display->print(this->roundNumber(this->_hotExhaustTemp), 1);
   // Cold Exhaust Temp
   this->display->setCursor(12, 21);
   this->display->print(this->roundNumber(this->_coldExhaustTemp), 1);

   // Hot Peltier Temp
   this->display->setCursor(55, 10);
   this->display->print(this->roundNumber(this->_hotPeltierTemp), 1);
   // Cold Peltier Temp
   this->display->setCursor(55, 21);
   this->display->print(this->roundNumber(this->_coldPeltierTemp), 1);

   // Inlet Temp
   this->display->setCursor(95, 10);
   this->display->print(this->roundNumber(this->_inletTemp), 1);


   this->display->display();
}

float TempMenu::roundNumber(float number) {
   return  round(number * 10) / 10.0;
}
