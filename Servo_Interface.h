#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_


ES_t Servo_enuInit(Servo copy_objServoMotor, u8 copy_u8ServoPin);

ES_t Servo_enuSetServoAngle(Servo copy_objServoMotor, s16 copy_s16ServoAngle);

bool Servo_boolCheckServoAttached(Servo copy_objServoMotor);


#endif /* SERVO_INTERFACE_H_ */
