#include "Arduino.h"
#include "ERROR_STATE.h"
#include "STD_TYPES.h"
#include "Pumb_Interface.h"

errorState pumpInitialization(u8 pinNumber)
{
  errorState  errorState = ES_NOK;

  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, LOW);

  errorState = ES_OK;
}


errorState pumpTurnOnPumb(u8 pinNumber)
{

  errorState  errorState = ES_NOK;

  digitalWrite(pinNumber, HIGH);

  errorState = ES_OK;
}

errorState pumpTurnOffPumb(u8 pinNumber)
{

  errorState  errorState = ES_NOK;

  digitalWrite(pinNumber, LOW);
  
  errorState = ES_OK;
}
