#ifndef Pumb_INTERFACE_H_
#define Pumb_INTERFACE_H_

#define    PUMBPIN      4

errorState pumpInitialization(u8 pinNumber);
errorState pumpTurnOnPumb(u8 pinNumber);
errorState pumpTurnOffPumb(u8 pinNumber);

#endif /* Pumb_INTERFACE_H_ */
