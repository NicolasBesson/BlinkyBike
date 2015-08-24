#ifndef _TIMER_H
#define _TIMER_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define MAX_TIMER	3

typedef void(*pfnTimerCallback)(void);

class Timer
{

private:
	unsigned long 		timerStart[MAX_TIMER] = {0};
	unsigned long 		timerDuration[MAX_TIMER] = {0};
	pfnTimerCallback  	timerCallback[MAX_TIMER] = {NULL};
	
	
public:
	void configureTimer(uint8_t timerIndex, unsigned long timerDelay, pfnTimerCallback callback);
	void updateTimer(uint8_t timerIndex, unsigned long timerDelay);
	void run();
};

#endif // _TIMER_H