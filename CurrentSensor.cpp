#include <Arduino.h>
#include <cstdint>             // For fixed-width integer types
#include "ERROR_STATE.h"       // Include errorState for error handling
#include "CurrentSensor.h"     // Include CurrentSensor header for macros and function declarations

// Zero current voltage (in volts)
static float g_zeroCurrentVoltage = 0.0f;

// List of valid ADC pins for ESP32
static const int8_t g_validAdcPins[] = {36, 39, 34, 35, 32, 33, 2, 4, 12, 13, 14, 15, 25, 26, 27};
static const int8_t g_numValidAdcPins = sizeof(g_validAdcPins) / sizeof(g_validAdcPins[0]);

// Static function to validate if the pin is an ADC pin
static bool isAdcPinValid(int8_t pinNumber)
{
    for (int8_t i = 0; i < g_numValidAdcPins; i++)
    {
        if (pinNumber == g_validAdcPins[i])
        {
            return true; // Pin is valid
        }
    }
    return false; // Pin is not valid
}

// Static function to calculate the average of multiple ADC readings
static float calculateAdcAverage(int8_t adcPin, int16_t sampleCount)
{
    float adcSum = 0.0f;

    for (int16_t i = 0; i < sampleCount; i++)
    {
        adcSum += analogRead(adcPin);
        delay(1); // Small delay for stable readings
    }

    return adcSum / sampleCount;
}

// Static function to calculate the average current over multiple readings
static float calculateAverageCurrent(int8_t adcPin, int16_t sampleCount)
{
    // Calculate the average ADC value using the calculateAdcAverage function
    float avgAdcValue = calculateAdcAverage(adcPin, sampleCount);

    // Convert the ADC value to voltage
    float voltage = avgAdcValue * (ADC_REF_VOLTAGE / ADC_RESOLUTION);

    // Calculate and return the average current (Amps)
    return (voltage - g_zeroCurrentVoltage) / (ACS712_SENSITIVITY / 1000.0f); // Convert mV to V
}

// Function to calculate the average current value
errorState calculateCurrent(int8_t adcPin, float &averageCurrent, int16_t sampleCount)
{
    // Validate if the pin number is an ADC pin
    if (!isAdcPinValid(adcPin))
    {
        return ES_OUT_OF_RANGE; // Return error if the pin is invalid
    }

    // Use the static function to calculate the average current
    averageCurrent = calculateAverageCurrent(adcPin, sampleCount);

    return ES_OK; // Return success
}

// Function to initialize the zero current voltage
errorState initializeZeroCurrentVoltage(int8_t adcPin, int16_t sampleCount)
{
    // Validate if the pin number is an ADC pin
    if (!isAdcPinValid(adcPin))
    {
        return ES_OUT_OF_RANGE; // Return error if the pin is invalid
    }

    // Calculate and update the zero current voltage
    g_zeroCurrentVoltage = calculateAdcAverage(adcPin, sampleCount) * (ADC_REF_VOLTAGE / ADC_RESOLUTION);

    return ES_OK; // Return success
}
