#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include <Arduino.h>

void Temperature_PrintSystemTemp();

void Temperature_SendSystemTempOverMQTT();

#endif // TEMPERATURE_H_
