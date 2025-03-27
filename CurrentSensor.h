#ifndef CURRENT_SENSOR_H_
#define CURRENT_SENSOR_H_

#include <cstdint>             // For fixed-width integer types
#include "ERROR_STATE.h"       // Include errorState for error handling

// Macros for ADC and sensor configuration
#define ADC_REF_VOLTAGE    5.0       // Reference voltage of the ADC (in volts)
#define ADC_RESOLUTION     4096      // ADC resolution (12-bit for ESP32)
#define ACS712_SENSITIVITY 185.0     // Sensitivity of ACS712 sensor (mV/A for 5A version)

// Function to calculate the average current value
// Parameters:
//   adcPin - The ADC pin number to read from
//   averageCurrent - A reference to a float variable where the calculated average current will be stored
//   sampleCount - The number of samples to average
// Returns:
//   errorState - ES_OK if the current is calculated successfully, ES_OUT_OF_RANGE if the pin is invalid
errorState calculateCurrent(int8_t adcPin, float &averageCurrent, int16_t sampleCount);

// Function to initialize the zero current voltage
// Parameters:
//   adcPin - The ADC pin number to read from
//   sampleCount - The number of samples to average for zero current voltage calculation
// Returns:
//   errorState - ES_OK if the initialization is successful, ES_OUT_OF_RANGE if the pin is invalid
errorState initializeZeroCurrentVoltage(int8_t adcPin, int16_t sampleCount);

#endif /* CURRENT_SENSOR_H_ */