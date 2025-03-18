#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_


errorState servoInitialization(u8 servoPin);

errorState servoSetServoAngle(s16 servoAngle);

bool static servoCheckServoAttached();


#endif /* SERVO_INTERFACE_H_ */
