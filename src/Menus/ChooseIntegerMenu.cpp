#include "ChooseIntegerMenu.h"




ChooseIntegerMenu::ChooseIntegerMenu(Adafruit_SSD1306 *display, int FPS, String title, int startingValue, int motorNo, int minValue, int maxValue) : Menu(display, FPS) {
   this->m_minValue = minValue;
   this->m_maxValue = maxValue;
   this->m_title = title;
   this->currentValue = startingValue;
   this->m_motor = (motorNo == 0) ? MotorDriver::MOTOR_A : MotorDriver::MOTOR_B;


}

void ChooseIntegerMenu::handleRotaryIncrease(int amount) {
   this->currentValue += amount;

   if (this->currentValue > this->m_maxValue)
      this->currentValue = this->m_maxValue;

   this->m_motorDriver->setSpeed(this->m_motor, ((this->currentValue * 1.0) / this->m_maxValue));

   this->refreshDisplay();
}

void ChooseIntegerMenu::handleRotaryDecrease(int amount) {
   this->currentValue -= amount;

   if (this->currentValue < this->m_minValue)
      this->currentValue = this->m_minValue;

   this->m_motorDriver->setSpeed(this->m_motor, ((this->currentValue * 1.0) / this->m_maxValue));

   this->refreshDisplay();
}


void ChooseIntegerMenu::refreshDisplay() {

   // Serial.println(this->display);

   this->display->clearDisplay();
   this->display->setTextSize(1);
   // this->display->setTextColor(WHITE);

   // Print Table Header
   this->display->setCursor(12,0);
   this->display->print(this->m_title);


   this->display->setTextSize(2);
   this->display->setCursor(12, 10);
   this->display->print(this->currentValue);
   this->display->print("%");

   uint8_t percentage = ((this->currentValue * 1.0) / this->m_maxValue) * 127;
   this->display->drawLine(0, 25, 0, 31, WHITE);

   this->display->drawLine(31, 28, 31, 31, WHITE);
   this->display->drawLine(63, 27, 63, 31, WHITE);
   this->display->drawLine(94, 28, 94, 31, WHITE);

   this->display->drawLine(127, 25, 127, 31, WHITE);

   this->display->drawLine(0, 29, percentage, 29, WHITE);
   this->display->drawLine(0, 30, percentage, 30, WHITE);
   this->display->drawLine(0, 31, 127, 31, WHITE);
   //
   //
   this->display->display();
}
