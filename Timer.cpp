#include <Arduino.h>
#include "esp32-hal-timer.h"
#include "Screw.h"
#include "Timer.h"

hw_timer_t *timer1 = NULL;
hw_timer_t *timer2 = NULL;
volatile bool ledState = false;
volatile uint32_t tickCount = 0;
static uint32_t  msCount = 0;
const uint32_t ticksPerSecond = 1000000;          // 1 tick = 1 µs, 1 second = 1,000,000 ticks
 uint32_t secondsIn3Days = 60;  // 259200 seconds
const uint64_t alarmTicks = 1000;                 // Fire every 1000 ticks (1 ms)

void IRAM_ATTR onTimer1() {
  
  msCount++;
  if (msCount >= 1000) { // 1000 ms = 1 second
    msCount = 0;
    tickCount++;
    if (tickCount >= secondsIn3Days) {
      tickCount = 0;
      initialize_Cleaning_Timer2();
      Serial.println("LED toggled after 3 days");
    }
  }
}
 bool state=true;
void IRAM_ATTR onTimer2() {
  static uint32_t msCount2 = 0;
  msCount2++;
 
  if(msCount2 %5000==0)
  {
    if (state ==true)
    {
        ScrewForward();
        Serial.println("FOR");
        state =false;
    }
    else{
        ScrewBacword();
        state =true;
        Serial.println("Back");
    }

  }
 

  if (msCount2 >= 30000) { // 1000 ms = 1 second
      Serial.println("timer2");
       msCount2=0;
       timerEnd(timer2);
       if(state ==true)
       {
         ScrewForward();
         delay(5000);
       }
       else
       {
         ScrewBacword();
         delay(5000);
       }
    }
    ScrewStop();
  }



void initialize_Cleaning_Timer2() {
  timer2 = timerBegin(1000000);
  timerAttachInterrupt(timer2, onTimer2);
  timerAlarm(timer2, 1000, true, 0); // 1 ms
  timerStart(timer2);
 
  
}
void initializeTimer1() {
  timer1 = timerBegin(1000000);  // 1 MHz frequency (1 tick = 1 μs)

  // Attach the interrupt service routine (ISR)
  timerAttachInterrupt(timer1, onTimer1);

  // Set alarm to fire every 1000 ticks (1 ms), with auto-reload
  uint64_t alarmTicks = 1000;
  timerAlarm(timer1, alarmTicks, true, 0);

  // Start the timer
  timerStart(timer1);

}

