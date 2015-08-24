#include "Timer.h"


void Timer::configureTimer(uint8_t timerIndex, unsigned long timerDelay, pfnTimerCallback callback)
{
	if (timerIndex >= MAX_TIMER)
	{
		return;
	}
	
	// Register timer configuration
	timerStart[timerIndex] = millis();
	timerDuration[timerIndex] = timerDelay;
	timerCallback[timerIndex] = callback;
}

void Timer::updateTimer(uint8_t timerIndex, unsigned long timerDelay)
{
	timerStart[timerIndex] = millis();
	timerDuration[timerIndex] = timerDelay;	
}

void Timer::run()
{
	// Retrieve current timer value
	unsigned long timerValue = millis();
	
	for (uint8_t timerIndex = 0 ; timerIndex < MAX_TIMER ; timerIndex++)
	{
	
		if (timerValue - timerStart[timerIndex] >= timerDuration[timerIndex])
		{
		
			// Call the timer callback function
			if (timerCallback[timerIndex] != NULL)
			{
				timerCallback[timerIndex]();
			}
		
			// Update current timer start reference
			timerStart[timerIndex] = timerValue;
		}
	}
}

static Timer TimerClass;