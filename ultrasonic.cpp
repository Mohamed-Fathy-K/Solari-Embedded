#include <Arduino.h>
#include "ultrasonic.h"
#include "ERROR_STATE.h"

void UltrasonicInit()
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

f32 UltrasonicCalculateDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  u16 duration = pulseIn(ECHO_PIN, HIGH);
  f32 distanceInCm = (duration * 0.0343) / 2;
  if(distanceInCm > 333) // for below 6cm 
  {
    distanceInCm = 0;
  }
  return distanceInCm;
}

void UltrasonicPrintDistance() {
  f32 distance = UltrasonicCalculateDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

