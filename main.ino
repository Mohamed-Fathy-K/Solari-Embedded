#include <ESP32Servo.h>
#include "Timer.h"
#include "Screw.h"
Servo myServo;
int servoPin = 13; // PWM-capable GPIO pin

void setup() {
  Serial.begin(115200);
  ScrewInit();
 initializeTimer1();
}

void loop() {
 
}
