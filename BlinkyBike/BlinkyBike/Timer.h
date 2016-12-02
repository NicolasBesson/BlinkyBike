/////////////////////////////////   License  //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Copyright 2015 - 2017 Nicolas BESSON - BeeAtHome
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

#ifndef _TIMER_H
#define _TIMER_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define MAX_TIMER	3

/// <summary>
/// Timer callback function
/// </summary>
typedef void(*pfnTimerCallback)(void);

/// <summary>
/// Timer Management class
/// </summary>
class Timer
{
private:
	unsigned long 		timerStart[MAX_TIMER] = {0};		// Timer start time
	unsigned long 		timerDuration[MAX_TIMER] = {0};		// Timer duration/delay
	pfnTimerCallback  	timerCallback[MAX_TIMER] = {NULL};	// Timer callback function
	
public:
	/// <summary>
	/// Configure time initial duration and callback
	/// </summary>
	/// <param name="timerIndex">Timer index</param>
	/// <param name="timerDelay">Timer delay</param>
	/// <param name="callback">Timer callback function</param>
	void configureTimer(uint8_t timerIndex, unsigned long timerDelay, pfnTimerCallback callback);

	/// <summary>
	/// Set new timer delay
	/// </summary>
	/// <param name="timerIndex">Timer index</param>
	/// <param name="timerDelay">Timer delay</param>
	void updateTimer(uint8_t timerIndex, unsigned long timerDelay);

	/// <summary>
	/// Update the timer and launch callback on time elapsed
	/// </summary>
	void run();
};

#endif // _TIMER_H
