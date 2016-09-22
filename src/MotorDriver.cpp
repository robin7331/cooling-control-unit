#include "MotorDriver.h"

#define STBY 17 // A3

#define PWMA 9 // D9
#define AIN1 5  // D5
#define AIN2 7 // D7

#define PWMB 6  // D6
#define BIN1 8 // D8
#define BIN2 16 // A2

MotorDriver::MotorDriver() {

   pinMode(STBY, OUTPUT); //standby

   // Motor A
   pinMode(PWMA, OUTPUT); //Speed control
   pinMode(AIN1, OUTPUT); //Direction
   pinMode(AIN2, OUTPUT); //Direction

   // Motor B
   pinMode(PWMB, OUTPUT); //Speed control
   pinMode(BIN1, OUTPUT); //Direction
   pinMode(BIN2, OUTPUT); //Direction

   this->setDirection(MOTOR_A, true);
   this->setDirection(MOTOR_B, true);
}
void MotorDriver::setSpeed(Motor motor, float percentage) {
   digitalWrite(STBY, HIGH); //disable standby

   this->setDirection(MOTOR_A, true);
   this->setDirection(MOTOR_B, true);

   if (motor == MOTOR_A) {
      analogWrite(PWMA, round(255.0 * percentage));
      Serial.print("Writing PWMA ");
      Serial.println(round(255.0 * percentage));
   } else {
      analogWrite(PWMB, round(255.0 * percentage));
      Serial.print("Writing PWMB ");
      Serial.println(round(255.0 * percentage));
   }
}

void MotorDriver::setDirection(Motor motor, bool clockwise) {
   if (motor == MOTOR_A) {
      digitalWrite(AIN1, clockwise);
      digitalWrite(AIN2, !clockwise);
   } else {
      digitalWrite(BIN1, clockwise);
      digitalWrite(BIN2, !clockwise);
   }
}

void MotorDriver::stop() {
   digitalWrite(STBY, LOW);
}
