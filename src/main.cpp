
#include "Arduino.h"
#include "Menus/Menus.h"
#include "Sensor.h"
#include "I2CScanner.h"
#include "RotaryDriver.h"

#define NUMOFTEMPSAMPLES 4
#define TEMPSAMPLESPERSECOND 10
#define DISPLAYFPS 8
#define OLED_RESET 4
#define DISPLAY_ADRESS 0x3C


const int PinCLK = PD2;                   // Used for generating interrupts using CLK signal
const int PinDT = PD4;                    // Used for reading DT signal
const int PinSW = PD3;                    // Used for the push button switch


I2CScanner *scanner;

MenuScroller *menuScroller;

TempMenu *tempMenu;
ChooseIntegerMenu *hotFanSettingsMenu;
ChooseIntegerMenu *coldFanSettingsMenu;

Sensor *hotExhaustSensor;
Sensor *coldExhaustSensor;
Sensor *hotPeltierSensor;
Sensor *coldPeltierSensor;
Sensor *inletSensor;

RotaryDriver *rotaryDriver;


void ISRDispatch ()  {
   rotaryDriver->onInterrupt();
}

void onRotaryTurn(bool clockwise, int amount, RotaryDriver *driver) {
   menuScroller->handleRotaryTurn(clockwise, amount, driver);
}

void onRotaryButton(RotaryDriver *driver) {
   menuScroller->handleButtonPress(driver);
}

void setup() {

   Serial.begin(115200);
   while(!Serial);

   scanner = new I2CScanner();
   scanner->startScanning();
   // free(scanner);

   Adafruit_SSD1306 *display = new Adafruit_SSD1306(OLED_RESET);
   display->begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADRESS);
   display->setTextWrap(false);


   menuScroller = new MenuScroller();

   tempMenu = new TempMenu(display, DISPLAYFPS);
   tempMenu->sayHi();
   menuScroller->addMenu(tempMenu, 0);

   hotFanSettingsMenu = new ChooseIntegerMenu(display, 1, "HOT FAN", 0, 0);
   menuScroller->addMenu(hotFanSettingsMenu, 1);

   coldFanSettingsMenu = new ChooseIntegerMenu(display, 1, "COLD FAN", 0, 1);
   menuScroller->addMenu(coldFanSettingsMenu, 2);


   menuScroller->setMenu(0);

   rotaryDriver = new RotaryDriver(PD2, PD4, PD3, &ISRDispatch);
   rotaryDriver->onRotaryButton = &onRotaryButton;
   rotaryDriver->onRotaryTurn = &onRotaryTurn;

   analogReference(EXTERNAL);

   hotExhaustSensor = new Sensor(A0, NUMOFTEMPSAMPLES, TEMPSAMPLESPERSECOND);
   coldExhaustSensor = new Sensor(A1, NUMOFTEMPSAMPLES, TEMPSAMPLESPERSECOND);
   hotPeltierSensor = new Sensor(A2, NUMOFTEMPSAMPLES, TEMPSAMPLESPERSECOND);
   coldPeltierSensor = new Sensor(A3,  NUMOFTEMPSAMPLES, TEMPSAMPLESPERSECOND);
   inletSensor = new Sensor(A6,  NUMOFTEMPSAMPLES, TEMPSAMPLESPERSECOND);


   Serial.println("Setup finished");
}

void loop() {

   menuScroller->currentMenu()->update();

   rotaryDriver->update();

   hotExhaustSensor->update();
   coldExhaustSensor->update();
   hotPeltierSensor->update();
   coldPeltierSensor->update();
   inletSensor->update();


   tempMenu->setHotExhaustTemp(hotExhaustSensor->currentCelsiusTemperature);
   tempMenu->setColdExhaustTemp(coldExhaustSensor->currentCelsiusTemperature);
   tempMenu->setHotPeltierTemp(hotPeltierSensor->currentCelsiusTemperature);
   tempMenu->setColdPeltierTemp(coldPeltierSensor->currentCelsiusTemperature);
   tempMenu->setInletTemp(inletSensor->currentCelsiusTemperature);

}
