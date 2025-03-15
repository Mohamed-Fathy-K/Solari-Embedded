#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_


errorState servoInitialization(Servo servoObject, u8 servoPin);

errorState servoSetServoAngle(Servo servoObject, s16 servoAngle);

bool servoCheckServoAttached(Servo servoObject);


#endif /* SERVO_INTERFACE_H_ */
