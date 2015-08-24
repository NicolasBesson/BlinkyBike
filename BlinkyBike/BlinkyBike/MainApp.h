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

#ifndef _MAINAPP_H
#define _MAINAPP_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Adafruit_NeoPixel.h"
#include "Timer.h"
#include "Button.h"
#include "Stripes.h"

// LED Stripes configuration
// See Stripes.h

// Buttons configuration
#define BUTTON_LEFT_PIN					3
#define BUTTON_RIGHT_PIN				2

#define BUTTON_DEBOUNCE_TIMEOUT			10
#define BUTTON_STATE_TIMEOUT			200
#define BUTTON_HOLD_TIMEOUT				(1 * 1000)

// Scenes timer index
#define SCENE_TIMER_FRONT			0
#define SCENE_TIMER_REAR_LEFT		1
#define SCENE_TIMER_REAR_RIGHT		2

class MainAppClass
{
private:
	// Front LED Stripe
	Adafruit_NeoPixel frontLight		= Adafruit_NeoPixel(LED_STRIPE_FRONT_NUMLED,		LED_STRIPE_FRONT_PIN,		NEO_GRB + NEO_KHZ800);
	
	// Rear Left LED Stripe
	Adafruit_NeoPixel rearLeftLight		= Adafruit_NeoPixel(LED_STRIPE_REARLEFT_NUMLED,		LED_STRIPE_REARLEFT_PIN,	NEO_GRB + NEO_KHZ800);
	
	// Rear Right LED Stripe
	Adafruit_NeoPixel rearRightLight	= Adafruit_NeoPixel(LED_STRIPE_REARRIGHT_NUMLED,	LED_STRIPE_REARRIGHT_PIN,	NEO_GRB + NEO_KHZ800);

	// Left Button
	Button leftButton = Button(BUTTON_LEFT_PIN, BUTTON_DEBOUNCE_TIMEOUT, BUTTON_HOLD_TIMEOUT, BUTTON_STATE_TIMEOUT, BUTTON_PULLUP);
	
	// Right Button
	Button rightButton = Button(BUTTON_RIGHT_PIN, BUTTON_DEBOUNCE_TIMEOUT, BUTTON_HOLD_TIMEOUT, BUTTON_STATE_TIMEOUT, BUTTON_PULLUP);
	
	// Time list
	Timer appTimer = Timer();

public:
	/// <summary>
	/// Main application intialization
	/// </summary>
	void init();

	/// <summary>
	/// Main application loop
	/// </summary>
	void loop();

	/// <summary>
	/// Load next Front Scene step
	/// </summary>
	static void loadSceneFrontCallback();

	/// <summary>
	/// Load next Rear Left Scene step
	/// </summary>
	static void loadSceneRearLeftCallback();

	/// <summary>
	/// Load next Rear Right Scene step
	/// </summary>
	static void loadSceneRearRightCallback();
};

extern MainAppClass MainApp;

#endif // _MAINAPP_H
