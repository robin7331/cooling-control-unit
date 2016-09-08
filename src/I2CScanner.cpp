
#include "I2CScanner.h"
#include "Arduino.h"
#include <Wire.h>

I2CScanner::I2CScanner() {}

void I2CScanner::startScanning() {

   byte error, address;
   int nDevices;

   Serial.println("I2C Scanner starting...");

   nDevices = 0;
   for(address = 1; address < 127; address++ )
   {
      // The i2c_scanner uses the return value of
      // the Write.endTransmisstion to see if
      // a device did acknowledge to the address.
      Wire.beginTransmission(address);
      error = Wire.endTransmission();

      if (error == 0)
      {
         Serial.print("I2C device found at address 0x");
         if (address<16)
         Serial.print("0");
         Serial.print(address,HEX);
         Serial.println("  !");

         nDevices++;
      }
      else if (error==4)
      {
         Serial.print("Unknow error at address 0x");
         if (address<16)
         Serial.print("0");
         Serial.println(address,HEX);
      }
   }
   if (nDevices == 0)
   Serial.println("I2CScanner did not find any device!\n");
   else
   Serial.println("I2CScanner finished!\n");
}
