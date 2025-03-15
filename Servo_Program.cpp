#include "Arduino.h"
#include "ERROR_STATE.h"
#include "STD_TYPES.h"
#include <Servo.h>
#include "Servo_Interface.h"

errorState servoInitialization(Servo servoObject, u8 servoPin)
{
  errorState  errorState = ES_NOK;

  servoObject.attach(servoPin);

  if (servoCheckServoAttached(servoObject))
  {
    errorState = ES_OK;
  }

  return errorState;
}



errorState servoSetServoAngle(Servo servoObject, s16 servoAngle)
{
  errorState  errorState = ES_NOK;
   servoObject.write(servoAngle);
  errorState = ES_OK;

  return errorState;
}


bool static servoCheckServoAttached(Servo servoObject)
{
   return servoObject.attached();
}
