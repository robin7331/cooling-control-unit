#ifndef SENSOR_H
#define SENSOR_H

#include "inttypes.h"

#define SENSOR_NOMINAL_TEMP 25
#define SENSOR_NOMINAL_RESISTANCE 100000L
#define SENSOR_BETA_VALUE 3950
#define SERIES_RESISTOR_VALUE 100000L

class Sensor {

private:
   float processSamples(int samples[]);

   unsigned long m_startProcessingTimer;
   unsigned long m_sampleTimer;
   bool m_processing;
   uint8_t m_currentSampleIndex;
   int *m_sampleBuffer;
   int m_samplesPerSecond;

public:
   int Pin;
   long nominalValue;
   int nominalTemperature;
   int betaValue;
   long seriesResistorValue;
   int numOfSamples;
   float currentCelsiusTemperature;

   Sensor(int Pin, int numOfSamples, int samplesPerSecond);
   void sample();
   void update();
};

#endif
