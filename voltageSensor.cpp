#include "voltageSensor.h"
#include "ERROR_STATE.h" // Include ERROR_STATE.h for error handling
#include <Arduino.h>
#include <cstdint> // For fixed-width integer types

// Define valid ADC pins for ESP32 (excluding GPIO0 to avoid boot mode conflicts)
static const int8_t validAdcPins[] = {36, 39, 34, 35, 32, 33, 2, 4, 12, 13, 14, 15, 25, 26, 27};
static const int8_t numAdcPins = sizeof(validAdcPins) / sizeof(validAdcPins[0]); // Calculate the number of valid ADC pins

// Static function to validate if the pin is an ADC pin
// Parameters:
//   pinNumber - The GPIO pin number to validate
// Returns:
//   true if the pin is a valid ADC pin, false otherwise
static bool isAdcPinValid(int8_t pinNumber)
{
    for (int8_t i = 0; i < numAdcPins; i++)
    {
        if (pinNumber == validAdcPins[i])
        {
            return true; // Pin is valid
        }
    }
    return false; // Pin is not valid
}

// Function to calculate the voltage from an ADC pin
// Parameters:
//   pinNumber - The ADC pin number to read the voltage from
//   voltage - A reference to a float variable where the calculated voltage will be stored
// Returns:
//   errorState - ES_OK if the voltage is calculated successfully, ES_OUT_OF_RANGE if the pin is invalid
errorState CalculateVoltage(int8_t pinNumber, float &voltage)
{
    // Validate if the pin number is an ADC pin
    if (!isAdcPinValid(pinNumber))
    {
        return ES_OUT_OF_RANGE; // Return ES_OUT_OF_RANGE if the pin is not a valid ADC pin
    }

    // Read the analog input from the specified ADC pin
    int16_t adc_value = analogRead(pinNumber); // Use int16_t as ADC values are typically 10-bit or 12-bit

    // Determine the voltage at the ADC input
    float voltage_adc = ((float)adc_value * REF_VOLTAGE) / ADC_RESOLUTION;

    // Calculate the voltage at the sensor input
    voltage = voltage_adc * 5.0f; // Adjust for the voltage divider ratio
    voltage += 0.6f; // Add 0.6V to account for the voltage drop across the diode

    return ES_OK; // Return ES_OK if the voltage is calculated successfully
}