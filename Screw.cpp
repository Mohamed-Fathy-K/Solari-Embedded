#include <Arduino.h>


void ScrewInit(){
  pinMode(19,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(17,OUTPUT);
}
void ScrewForward()
{
  digitalWrite(19,1);
  digitalWrite(18,0);
  digitalWrite(5,0);
  digitalWrite(17,1);

}
void ScrewBacword(){
  digitalWrite(19,0);
  digitalWrite(18,1);
  digitalWrite(5,1);
  digitalWrite(17,0);
}
void ScrewStop()
{
  digitalWrite(19,0);
  digitalWrite(18,0);
  digitalWrite(5,0);
  digitalWrite(17,0);
}