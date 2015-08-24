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

#include "Button.h"

// Global State bits
#define CURRENT		0
#define PREVIOUS	1
#define CHANGED		2
#define HOLD		3
#define DEBOUNCE	4
#define MODE		5

/// <summary>
/// Constructor
/// </summary>
/// <param name="buttonPin">Pin used for Button</param>
/// <param name="debounceTime">Hardware debounce duration</param>
/// <param name="holdTime">Duration for long press</param>
/// <param name="stateRemains">Long press state remain duration</param>
/// <param name="buttonMode">Harware Pull up mode</param>
Button::Button(uint8_t buttonPin, unsigned long debounceTime, unsigned long holdTime, unsigned long stateRemains, uint8_t buttonMode) :  
state(0), 
pin(buttonPin), 
buttonState(RELEASED), 
debounceThreshold(debounceTime), 
pressedStartTime(-1), 
stateStartTime(-1), 
holdThreshold(holdTime),
stateRemainsThreshold(stateRemains)
{
	// Configure GPIO mode as Input
	pinMode(pin, INPUT);
	bitWrite(state, MODE, (buttonMode == BUTTON_PULLUP));

	// Get the current status of the pin
	if (digitalRead(pin) == bitRead(state, MODE))
	{
		//currently the button is not pressed
		bitWrite(state, CURRENT, false);
	}
	else
	{
		//currently the button is pressed
		bitWrite(state, CURRENT, true);
	}
}

/// <summary>
/// Current button state
/// </summary>
/// <returns>The Button state</returns>
ButtonState Button::getButtonState()
{
	if (heldFor(holdThreshold))
	{
		buttonState = LONG_PRESSURE;
		stateStartTime = millis();
	}
	// Has been release and wasn't hold
	else if (wasPressed() && !wasHeld())
	{
		buttonState = SHORT_PRESSURE;
		stateStartTime = millis();
	}
	// Released
	else
	{
	}

	if (stateStartTime != -1)
	{
		if (millis() - stateStartTime > stateRemainsThreshold)
		{
			buttonState = RELEASED;
			stateStartTime = -1;
		}
	}

	return buttonState;
}

/// <summary>
/// Clear the Button state for Short Pressure
/// </summary>
/// <returns></returns>
void Button::clearButtonState()
{
	if (buttonState == SHORT_PRESSURE)
	{
		buttonState = RELEASED;
		stateStartTime = -1;
	}
}

/// <summary>
/// Retrive the press state
/// </summary>
/// <returns>true when pressed</returns>
bool Button::isPressed(void)
{
	// Debouncing enabled
	if (bitRead(state, DEBOUNCE) == true)
	{
		if ((millis() - pressedStartTime > debounceThreshold))
		{
			bitWrite(state, DEBOUNCE, false);
		}
		else
		{
			// currently the button is not pressed
			return false;
		}
	}

	// save the previous value
	bitWrite(state, PREVIOUS, bitRead(state, CURRENT));

	//get the current status of the pin
	if (digitalRead(pin) == bitRead(state, MODE))
	{
		//currently the button is not pressed
		bitWrite(state, CURRENT, false);
	}
	else
	{
		//currently the button is pressed
		bitWrite(state, CURRENT, true);
	}

	//handle state changes
	if (bitRead(state, CURRENT) != bitRead(state, PREVIOUS))
	{
		//the state changed to PRESSED
		if (bitRead(state, CURRENT) == true)
		{
			pressedStartTime = millis();             //start timing
			bitWrite(state, DEBOUNCE, true);

			//note that the state changed
			bitWrite(state, CHANGED, false);

			//note that the state changed
			bitWrite(state, HOLD, false);

			// keep unpressed
			return false;
		}
		else //the state changed to RELEASED
		{
			//reset states (for timing and for event triggering)
			pressedStartTime = -1;
			bitWrite(state, DEBOUNCE, false);

			//note that the state changed
			bitWrite(state, CHANGED, true);
		}

	}
	else
	{
		//note that the state did not change
		bitWrite(state, CHANGED, false);
		//should we trigger a onHold event?
		if (pressedStartTime != -1 && (bitRead(state, HOLD) == false))
		{
			if (millis() - pressedStartTime > holdThreshold)
			{
				// Set hold bit
				bitWrite(state, HOLD, true);
			}
		}
	}
	return bitRead(state, CURRENT);
}

/// <summary>
/// Identify when button is released if was previously pressed
/// </summary>
/// <returns>true when button was pressed</returns>
inline bool Button::wasPressed(void) const
{
	// Need a current state released and previous state pressed
	return (bitRead(state, CURRENT) == false) && (bitRead(state, PREVIOUS) == true);
}

/// <summary>
/// Identify for pressure for duration
/// </summary>
/// <param name="time">Pressure duration</param>
/// <returns>true when press for at least duration</returns>
bool Button::heldFor(unsigned int time)
{
	if (isPressed())
	{
		if (millis() - pressedStartTime > time)
		{
			return true;
		}
	}
	return false;
}

/// <summary>
/// Identify when button is released if was previously held
/// </summary>
/// <returns>true when held</returns>
bool Button::wasHeld()
{
	if (bitRead(state, HOLD))
	{
		// Clear hold bit
		bitWrite(state, HOLD, false);
		return true;
	}

	return false;
}
