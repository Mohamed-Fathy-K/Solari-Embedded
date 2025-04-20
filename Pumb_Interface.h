#ifndef PUMP_INTERFACE_H_
#define PUMP_INTERFACE_H_
#include "ERROR_STATE.h"
#include "STD_TYPES.h"
#define PUMP_PIN 4

errorState PumpInitialize(u8 pin_number);
errorState PumpTurnOn(u8 pin_number);
errorState PumpTurnOff(u8 pin_number);

#endif /* PUMP_INTERFACE_H_ */
