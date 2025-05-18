#include "Arduino.h"
#include "ERROR_STATE.h"
#include "STD_TYPES.h"
#include <ESP32Servo.h>
#include "Servo_Interface.h"

Servo verticalServoObject;
Servo horizontalServoObject;

errorState servoInitialization(u8 servoPin)
{
  errorState  errorState = ES_NOK;

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  if (servoPin == HORIZONTAL_SERVO_MOTOR)
  {
    horizontalServoObject.setPeriodHertz(50);    // standard 50 hz servo
    horizontalServoObject.attach(servoPin, 900, 2100);
    errorState = ES_OK;
    Serial.println("Initialization of Horizontal done");
  }
  else if (servoPin == VERTICAL1_MOTOR || servoPin == VERTICAL2_MOTOR)
  {
    verticalServoObject.setPeriodHertz(50);    // standard 50 hz servo
    verticalServoObject.attach(servoPin, 500, 2500);
    errorState = ES_OK;
    Serial.println("Initialization of Vertical done");
  }
  else
  {
    return errorState;
  }

  if (servoCheckServoAttached(servoPin))
  {
    errorState = ES_OK;
  }
  else
  {
    errorState = ES_NOK;
  }

  return errorState;
}



errorState servoSetServoAngle(u8 servoPin, s16 servoAngle)
{
  errorState  errorState = ES_NOK;

  if (servoPin == HORIZONTAL_SERVO_MOTOR)
  {
    horizontalServoObject.write(servoAngle);
    delay(15);
    errorState = ES_OK;
    Serial.println("Movement of Horizontal done");
  }
  else if (servoPin == VERTICAL_SERVO_MOTOR)
  {
    verticalServoObject.write(servoAngle);
    delay(15);
    errorState = ES_OK;
    Serial.println("Movement of VERTICAL done");
  }
  else
  {
    errorState = ES_NOK;
  }

  return errorState;
}


bool static servoCheckServoAttached(u8 servoPin)
{

  bool isAttached = false;
  if (servoPin == HORIZONTAL_SERVO_MOTOR)
  {
    isAttached = horizontalServoObject.attached();
  }
  else
  {
    isAttached = verticalServoObject.attached();
  }
  return isAttached;
}
