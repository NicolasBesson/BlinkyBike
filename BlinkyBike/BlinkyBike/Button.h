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

#ifndef _BUTTON_H
#define _BUTTON_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <stdint.h>

// Supported Pin Modes
#define BUTTON_PULLUP HIGH
#define BUTTON_PULLDOWN LOW

// Button State enumeration
enum ButtonState : uint8_t
{
	RELEASED = 0,			// Button Release
	SHORT_PRESSURE = 1,		// Button Short Pressure
	LONG_PRESSURE = 3		// Button Long Pressure
};

/// <summary>
/// Hardware Button
/// </summary>
class Button
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="buttonPin">Pin used for Button</param>
	/// <param name="debounceTime">Hardware debounce duration</param>
	/// <param name="holdTime">Duration for long press</param>
	/// <param name="stateRemains">Long press state remain duration</param>
	/// <param name="buttonMode">Harware Pull up mode</param>
	Button(uint8_t buttonPin, unsigned long debounceTime, unsigned long holdThreshold, unsigned long stateRemainsThreshold, uint8_t buttonMode = BUTTON_PULLUP);
	
	/// <summary>
	/// Current button state
	/// </summary>
	/// <returns>The Button state</returns>
	ButtonState getButtonState();
	
	/// <summary>
	/// Clear the Button state for Short Pressure
	/// </summary>
	/// <returns></returns>
	void clearButtonState();

private:
	/// <summary>
	/// Retrive the press state
	/// </summary>
	/// <returns>true when pressed</returns>
	bool isPressed();

	/// <summary>
	/// Identify when button is released if was previously pressed
	/// </summary>
	/// <returns>true when button was pressed</returns>
	bool wasPressed() const;

	/// <summary>
	/// Identify for pressure for duration
	/// </summary>
	/// <param name="time">Pressure duration</param>
	/// <returns>true when press for at least duration</returns>
	bool heldFor(unsigned int time);

	/// <summary>
	/// Identify when button is released if was previously held
	/// </summary>
	/// <returns>true when held</returns>
	bool wasHeld();

private:
	uint8_t state;							// Global state
	uint8_t pin;							// Hardware GPIO configuration
	ButtonState buttonState;				// Current Button state
	unsigned long debounceThreshold;		// Hardware Debounce duration
	unsigned long pressedStartTime;			// Pressure start Time
	unsigned long stateStartTime;			//
	unsigned long holdThreshold;			// 
	unsigned long stateRemainsThreshold;	// Long pressure state remains duration
};

#endif // _BUTTON_H
