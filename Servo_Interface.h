#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_


#define  HORIZONTAL_SERVO_MOTOR   12
#define  VERTICAL_SERVO_MOTOR     13


errorState servoInitialization(u8 servoPin);

errorState servoSetServoAngle(u8 servoPin, s16 servoAngle);

bool static servoCheckServoAttached(u8 servoPin);


#endif /* SERVO_INTERFACE_H_ */
