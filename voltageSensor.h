#ifndef VOLT_H_ // Include guard to prevent multiple inclusions of this header file
#define VOLT_H_

#include "ERROR_STATE.h" // Include ERROR_STATE.h for error handling

// Reference voltage of the ADC (Analog-to-Digital Converter) in volts
#define REF_VOLTAGE    3.3

// Resolution of the ADC (e.g., 12-bit ADC has 2^12 = 4096 steps)
#define ADC_RESOLUTION 4096.0

// Resistor values in the voltage divider circuit (in ohms)
#define R1             30000.0 // Resistor R1 in the voltage divider
#define R2             7500.0  // Resistor R2 in the voltage divider

// Function to calculate the voltage from an ADC pin
// Parameters:
//   pinNumber - The ADC pin number to read the voltage from
//   voltage - A reference to a float variable where the calculated voltage will be stored
// Returns:
//   errorState - ES_OK if the voltage is calculated successfully, ES_OUT_OF_RANGE if the pin is invalid
errorState CalculateVoltage(int pinNumber, float &voltage);

#endif // End of include guard VOLT_H_