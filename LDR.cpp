#include <Arduino.h>
#include "ERROR_STATE.h"
#include "LDR.h"



void LdrInit()
{
	pinMode(LDR_UP_LEFT_PIN, INPUT);
	pinMode(LDR_UP_RIGHT_PIN, INPUT);
	pinMode(LDR_DOWN_LEFT_PIN, INPUT);
	pinMode(LDR_DOWN_RIGHT_PIN, INPUT);
}
errorState LdrCalculatePercentage(u8 ldrPin, u32* ldrPercentage) {
 errorState  errorState = ES_NOK;
 if(
	ldrPin == LDR_UP_LEFT_PIN  	||
	ldrPin == LDR_UP_RIGHT_PIN 	||
	ldrPin == LDR_DOWN_LEFT_PIN	||
	ldrPin == LDR_DOWN_RIGHT_PIN
	)
	{
		if(ldrPercentage != NULL)
		{
			//*ldrPercentage = (analogRead(ldrPin)*100)/ADC_RESOLUTION; 
      *ldrPercentage = analogRead(ldrPin);
      *ldrPercentage *=100;
      *ldrPercentage /=1023;
			errorState = ES_OK;
		}
		else
		{
			errorState = ES_NULL_POINTER;
		}
	}
	else
	{
		errorState = ES_OUT_OF_RANGE;
	}
 
  return errorState;
}

errorState LdrPrintPercentage(u8 ldrPin)
{
	errorState  errorState = ES_NOK;
	u32 ldrPercentage;
	errorState = LdrCalculatePercentage(ldrPin, &ldrPercentage);
    Serial.print("Percentage: ");
    Serial.println(ldrPercentage);   
	return errorState;
}
