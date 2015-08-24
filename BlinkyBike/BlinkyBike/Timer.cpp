/////////////////////////////////   License  //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Copyright 2015 Nicolas BESSON - BeeAtHome
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
///////////////////////////////////////////////////////////////////////////////

#include "Timer.h"

/// <summary>
/// Configure time initial duration and callback
/// </summary>
/// <param name="timerIndex">Timer index</param>
/// <param name="timerDelay">Timer delay</param>
/// <param name="callback">Timer callback function</param>
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

/// <summary>
/// Set new timer delay
/// </summary>
/// <param name="timerIndex">Timer index</param>
/// <param name="timerDelay">Timer delay</param>
void Timer::updateTimer(uint8_t timerIndex, unsigned long timerDelay)
{
	timerStart[timerIndex] = millis();
	timerDuration[timerIndex] = timerDelay;	
}

/// <summary>
/// Update the timer and launch callback on time elapsed
/// </summary>
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
