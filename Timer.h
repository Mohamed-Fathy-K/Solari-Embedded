#include <Arduino.h>
#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif
void initializeTimer1() ;
void initialize_Cleaning_Timer2() ;
void IRAM_ATTR onTimer();
void startEsp32Timer(uint64_t timerIntervalUs, void (*callback)());

#ifdef __cplusplus
}
#endif

#endif // TIMER_H
