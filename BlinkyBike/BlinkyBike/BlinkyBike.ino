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

/******************************************************************************
 *              ____  _ _       _            ____  _ _        
 *             |  _ \| (_)     | |          |  _ \(_) |
 *             | |_) | |_ _ __ | | ___   _  | |_) |_| | _____
 *             |  _ <| | | '_ \| |/ / | | | |  _ <| | |/ / _ \
 *             | |_) | | | | | |   <| |_| | | |_) | |   <  __/
 *             |____/|_|_|_| |_|_|\_\\__, | |____/|_|_|\_\___|
 *                                    __/ |  Version 1.2      
 *                                   |___/                    
 *
 *****************************************************************************/

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Adafruit_NeoPixel.h"
#include "Timer.h"
#include "Button.h"
#include "Stripes.h"
#include "SceneManager.h"

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


// LED Stripes
Adafruit_NeoPixel frontLight		= Adafruit_NeoPixel(LED_STRIPE_FRONT_NUMLED,		LED_STRIPE_FRONT_PIN,		NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rearLeftLight		= Adafruit_NeoPixel(LED_STRIPE_REARLEFT_NUMLED,		LED_STRIPE_REARLEFT_PIN,	NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rearRightLight	= Adafruit_NeoPixel(LED_STRIPE_REARRIGHT_NUMLED,	LED_STRIPE_REARRIGHT_PIN,	NEO_GRB + NEO_KHZ800);

// Buttons
Button leftButton = Button(BUTTON_LEFT_PIN, BUTTON_DEBOUNCE_TIMEOUT, BUTTON_HOLD_TIMEOUT, BUTTON_STATE_TIMEOUT, BUTTON_PULLUP);
Button rightButton = Button(BUTTON_RIGHT_PIN, BUTTON_DEBOUNCE_TIMEOUT, BUTTON_HOLD_TIMEOUT, BUTTON_STATE_TIMEOUT, BUTTON_PULLUP);

// Timers
Timer appTimer = Timer();

// CPU Frequency checking
// The system requires that CPU frequency must be greater or equal to 8Mhz (suggested
// to 16Mhz) in order to handle correctly the WS2812 RGB Leds and avoid visual 
// flickering due to LED multiplexing to reduce the overal power consumption
#if (F_CPU < 8000000UL)
	#error CPU Frequency should be equal or greater than 8Mhz
#elif (F_CPU < 16000000UL)
	#warning CPU Frequency could be increased to 16Mhz for better visual rendering
#endif

/// <summary>
/// Front Timer callback function
/// </summary>
void loadSceneFront_callback()
{
	SceneManager.nextSceneStepFront();
}

/// <summary>
/// Rear Left Timer callback function
/// </summary>
void loadSceneRearLeft_callback()
{
	SceneManager.nextSceneStepRearLeft();
}

/// <summary>
/// Rear Right Timer callback function
/// </summary>
void loadSceneRearRight_callback()
{
	SceneManager.nextSceneStepRearRight();
}

// the setup function runs once when you press reset or power the board
void setup() {
	// Initialize the LED Stripes	
	frontLight.begin();
	rearLeftLight.begin();
	rearRightLight.begin();

	// Initialize the timer
	appTimer.configureTimer(SCENE_TIMER_FRONT, 2 * 1000, loadSceneFront_callback);
	appTimer.configureTimer(SCENE_TIMER_REAR_LEFT, 2 * 1000, loadSceneRearLeft_callback);
	appTimer.configureTimer(SCENE_TIMER_REAR_RIGHT, 2 * 1000, loadSceneRearRight_callback);

	// Clear the LED Stripes
	frontLight.show();
	rearLeftLight.show();
	rearRightLight.show();

	// Initialize the SceneManager
	SceneManager.begin();
}

// the loop function runs over and over again until power down or reset
void loop() {
	// Update the button state
	ButtonState leftButtonState = leftButton.getButtonState();
	ButtonState rightButtonState = rightButton.getButtonState();

	// Update the scene based on button state
	SceneManager.updateScene(leftButtonState, rightButtonState);

	// Reset short press state
	leftButton.clearButtonState();
	rightButton.clearButtonState();

	// Handle scene updates
	// Updates occurs on Timer elapsed and call to updateScene
	// Front
	if (SceneManager.isSceneUpdatedFront() == true)
	{
		// update the timer for current step duration
		appTimer.updateTimer(SCENE_TIMER_FRONT, SceneManager.getSceneStepDurationFront());
	}

	// Rear Left
	if (SceneManager.isSceneUpdatedRearLeft() == true)
	{
		// update the timer for current step duration
		appTimer.updateTimer(SCENE_TIMER_REAR_LEFT, SceneManager.getSceneStepDurationRearLeft());
	}

	// Rear Right
	if (SceneManager.isSceneUpdatedRearRight() == true)
	{
		// update the timer for current step duration
		appTimer.updateTimer(SCENE_TIMER_REAR_RIGHT, SceneManager.getSceneStepDurationRearRight());
	}

	// Update the LED Stripes
	SceneManager.updateStripes(&frontLight, &rearLeftLight, &rearRightLight);
	
	// Display the LED Stripes
	frontLight.show();
	rearLeftLight.show();
	rearRightLight.show();

	// Update timer info
	appTimer.run();
}
