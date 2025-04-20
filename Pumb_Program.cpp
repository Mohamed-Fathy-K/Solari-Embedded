#include "Arduino.h"
#include "ERROR_STATE.h"
#include "STD_TYPES.h"
#include "Pumb_Interface.h"

errorState PumpInitialize(u8 pin_number)
{
  errorState error_state = ES_NOK;

  pinMode(pin_number, OUTPUT);
  digitalWrite(pin_number, LOW);

  error_state = ES_OK;
  return error_state;
}

errorState PumpTurnOn(u8 pin_number)
{
  errorState error_state = ES_NOK;

  digitalWrite(pin_number, HIGH);

  error_state = ES_OK;
  return error_state;
}

errorState PumpTurnOff(u8 pin_number)
{
  errorState error_state = ES_NOK;

  digitalWrite(pin_number, LOW);

  error_state = ES_OK;
  return error_state;
}
