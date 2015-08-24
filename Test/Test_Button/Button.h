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

#ifndef __BUTTON_H__
#define __BUTTON_H__

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
typedef enum ButtonState : uint8_t
{
	RELEASED = 0,
	SHORT_PRESSURE = 1,
	LONG_PRESSURE = 3
};

// Hardware button handling
class Button
{
public:

	Button(uint8_t buttonPin, unsigned long debounceTime, unsigned long holdThreshold, unsigned long stateRemainsThreshold, uint8_t buttonMode = BUTTON_PULLUP);
	ButtonState getButtonState();
	ButtonState clearButtonState();

private:
	// Hardware configuration
	void pullup(uint8_t buttonMode);
	void pulldown();

	// Pressure detections
	bool isPressed();
	bool wasPressed();
	bool heldFor(unsigned int time);
	bool wasHeld();

private:
	// Global state
	uint8_t state;

	// GPIO configuration
	uint8_t pin;

	// Button state
	ButtonState buttonState;

	// Debounce counters
	unsigned long debounceThreshold;
	unsigned long pressedStartTime;
	unsigned long stateStartTime;
	unsigned long holdThreshold;
	unsigned long stateRemainsThreshold;
};

#endif // __BUTTON_H__
