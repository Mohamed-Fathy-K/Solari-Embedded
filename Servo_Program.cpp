#include "Arduino.h"
#include "ERROR_STATE.h"
#include "STD_TYPES.h"
#include <ESP32Servo.h>
#include "Servo_Interface.h"

Servo servoObject;

errorState servoInitialization(u8 servoPin)
{
  errorState  errorState = ES_NOK;

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servoObject.setPeriodHertz(50);    // standard 50 hz servo
  servoObject.attach(servoPin, 500, 2400);

  if (servoCheckServoAttached())
  {
    errorState = ES_OK;
  }

  return errorState;
}



errorState servoSetServoAngle(s16 servoAngle)
{
  errorState  errorState = ES_NOK;
  servoObject.write(servoAngle);
  delay(15);
  errorState = ES_OK;

  return errorState;
}


bool static servoCheckServoAttached()
{
  return servoObject.attached();
}
