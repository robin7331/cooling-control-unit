
#include "Arduino.h"
#include "Sensor.h"


Sensor::Sensor(int Pin, int numOfSamples, int samplesPerSecond) {
   this->Pin = Pin;
   this->nominalValue = SENSOR_NOMINAL_RESISTANCE;
   this->nominalTemperature = SENSOR_NOMINAL_TEMP;
   this->betaValue = SENSOR_BETA_VALUE;
   this->seriesResistorValue = SERIES_RESISTOR_VALUE;
   this->numOfSamples = numOfSamples;
   this->m_sampleBuffer = new int[this->numOfSamples];
   this->m_samplesPerSecond = samplesPerSecond;

   Serial.print("New Sensor created on Pin ");
   Serial.println(this->Pin);
};

void Sensor::update() {

   if ((millis() - this->m_startProcessingTimer) >= (1000UL / this->m_samplesPerSecond) && this->m_processing == false) {
      this->m_currentSampleIndex = 0;
      this->m_processing = true;
      this->m_sampleTimer = millis();
   }

   unsigned long sampleEvery = ((1000UL / this->m_samplesPerSecond) / this->numOfSamples) - 5UL;

   if ((millis() - this->m_sampleTimer) >= sampleEvery && this->m_processing == true) {

      this->m_sampleBuffer[this->m_currentSampleIndex] = analogRead(this->Pin);

      if (this->m_currentSampleIndex >= this->numOfSamples) {
         this->m_processing = false;
         this->m_startProcessingTimer = millis();
         this->processSamples(this->m_sampleBuffer);
      }

      this->m_currentSampleIndex ++;
      this->m_sampleTimer = millis();

   }
}

float Sensor::processSamples(int samples[]) {
   //
   float average = 0;
   uint8_t i;

   for (i = 0; i < this->numOfSamples; i++) {
      average += samples[i];
   }
   average /= this->numOfSamples;

   // // convert the value to resistance
   average = 1023 / average - 1;
   average = this->seriesResistorValue / average;

   float steinhart;
   steinhart = average / this->nominalValue;     // (R/Ro)
   steinhart = log(steinhart);                  // ln(R/Ro)
   steinhart /= this->betaValue;                   // 1/B * ln(R/Ro)
   steinhart += 1.0 / (this->nominalTemperature + 273.15); // + (1/To)
   steinhart = 1.0 / steinhart;                 // Invert
   steinhart -= 273.15;                         // convert to C

   this->currentCelsiusTemperature = steinhart;

   return steinhart;
};
