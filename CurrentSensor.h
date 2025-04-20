#ifndef CURRENT_SENSOR_H_
#define CURRENT_SENSOR_H_

#include <cstdint>             // For fixed-width integer types
#include "ERROR_STATE.h"       // Include errorState for error handling

/*
// ACS712 5A Sensor Pin (adjust to your ESP32 pin)
#define ACS712_PIN 13 // Example: GPIO 36

// ACS712 Sensitivity (mV/A) for 5A version
#define SENSITIVITY 185.0 // mV/A

// VCC of the ACS712 (usually 5V or 3.3V)
#define VCC 5 // Adjust if needed

// ADC Resolution of ESP32 (4096 for 12-bit)
#define ADC_RESOLUTION 4096
*/
errorState currentInitialize();
errorState currentMeasure(float &current);

#endif /* CURRENT_SENSOR_H_ */
