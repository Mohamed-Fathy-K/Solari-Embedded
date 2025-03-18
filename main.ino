#include "ERROR_STATE.h"
#include "STD_TYPES.h"
#include "LDR.h"
void setup() {
Serial.begin(9600);
Serial.println("Mohameeeeeeed");
LdrInit();
}

void loop() {
Serial.print("Up Left");
LdrPrintPercentage(LDR_UP_LEFT_PIN);
Serial.print("Up Right");
LdrPrintPercentage(LDR_UP_RIGHT_PIN);
Serial.print("Down Left");
LdrPrintPercentage(LDR_DOWN_LEFT_PIN);
Serial.print("Down Right");
LdrPrintPercentage(LDR_DOWN_RIGHT_PIN);
Serial.println("_______________________________");
delay(1000);
}

/*
void loop()
{
  int upLeft = analogRead(LDR_UP_LEFT_PIN); // Top left LDR
  int upRight = analogRead(LDR_UP_RIGHT_PIN); // Top right LDR
  int downLeft = analogRead(LDR_DOWN_LEFT_PIN); // Bottom left LDR
  int downRight = analogRead(LDR_DOWN_RIGHT_PIN); // Bottom right LDR
  int tolerance = 5;    

  int topAverage = (upLeft + upRight) / 2; // Average of top LDRs
  int downAverage = (downLeft + downRight) / 2; // Average of bottom LDRs
  int leftAverage = (upLeft + downLeft) / 2; // Average of left LDRs
  int rightAverage = (upRight + downRight) / 2; // Average of right LDRs

  int verticalDifference = abs(topAverage - downAverage);  // Difference between top and bottom
  int horizontalDifference = abs(leftAverage - rightAverage); // Difference between left and right

   if (verticalDifference > tolerance)
   {
    if(topAverage > downAverage)
    {
      Serial.println("Increase Vertical Servo");
    }
    else
    {
      Serial.println("Decrease Vertical Servo");
    }
   }

   if(horizontalDifference > tolerance)
   {
      if (leftAverage > rightAverage)
      {
        Serial.println("Increase Horizontal Servo");
      }
      else
      {
        Serial.println("Decrease Horizontal Servo");
      }
   }

   Serial.println("_______________________");

   delay(1000);
   
}
*/