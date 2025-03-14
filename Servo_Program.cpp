#include "ERROR_STATE.h"
#include "STD_TYPES.h"
#include <Servo.h>
#include "Servo_Interface.h"

ES_t Servo_enuInit(Servo copy_objServoMotor, u8 copy_u8ServoPin)
{
  ES_t  Local_enuErrorState = ES_NOK;

  copy_objServoMotor.attach(copy_u8ServoPin);

  if (Servo_boolCheckServoAttached(copy_objServoMotor))
  {
    Local_enuErrorState = ES_OK;
  }

  return Local_enuErrorState;
}



ES_t Servo_enuSetServoAngle(Servo copy_objServoMotor, s16 copy_s16ServoAngle)
{
  ES_t  Local_enuErrorState = ES_NOK;
   copy_objServoMotor.write(copy_s16ServoAngle);
  Local_enuErrorState = ES_OK;

  return Local_enuErrorState;
}


bool Servo_boolCheckServoAttached(Servo copy_objServoMotor)
{
   return copy_objServoMotor.attached();

}
