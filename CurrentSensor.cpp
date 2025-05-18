#include <Arduino.h>
#include <cstdint>             // For fixed-width integer types
#include "ERROR_STATE.h"       // Include errorState for error handling
#include "CurrentSensor.h"     // Include CurrentSensor header for macros and function declarations

// ACS712 5A Sensor Pin (adjust to your ESP32 pin)
const int ACS712_PIN = 13; // Example: GPIO 36

// ACS712 Sensitivity (mV/A) for 5A version
const float SENSITIVITY = 185.0; // mV/A

// Zero Current Voltage (V)
float zeroVoltage;

// VCC of the ACS712 (usually 5V or 3.3V)
const float VCC = 5; // Adjust if needed

// ADC Resolution of ESP32 (4096 for 12-bit)
const int ADC_RESOLUTION = 4096;

errorState currentInitialize()
{
    errorState error_state = ES_NOK;

    // Calculate the zero current voltage by averaging multiple readings
    float sum = 0;
    for (int i = 0; i < 100; i++) {
        sum += analogRead(ACS712_PIN);
        delay(1); // Small delay for stable readings
    }
    zeroVoltage = (sum / 100.0) * (VCC / ADC_RESOLUTION);

    Serial.print("Zero Voltage: ");
    Serial.print(zeroVoltage);
    Serial.println(" V");

    error_state = ES_OK;
    return error_state;
}

errorState currentMeasure(float &current)
{
    errorState error_state = ES_NOK;

    // Read the analog voltage from the ACS712
    int sensorValue;
    float sum = 0;
    for (int i = 0; i < 1000; i++) {
        sensorValue = analogRead(ACS712_PIN); // Store the raw ADC reading
        // Convert the analog reading to voltage
        float voltage = sensorValue * (VCC / ADC_RESOLUTION);
        // Calculate the current (Amps)
        float measured_current = (voltage - zeroVoltage) / (SENSITIVITY / 1000.0); // Convert mV to V
        sum += measured_current;
    }
    sum /= 1000.0;
    current = sum;

    // Print the current and ADC value to the Serial Monitor
    Serial.print(" , Current: ");
    Serial.print(current);
    Serial.println(" A");

    error_state = ES_OK;
    return error_state;
}
