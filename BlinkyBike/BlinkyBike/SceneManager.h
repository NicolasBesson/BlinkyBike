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

#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Adafruit_NeoPixel.h"
#include "Button.h"
#include "AnimationPlayer.h"

/// <summary>
/// Scene Manager State Machine states
/// </summary>
enum SceneState : uint8_t
{
	STATE_LIGHT_OFF = 0,				// Light OFF
	STATE_LIGHT_OFF_LOCK = 30,			// Light OFF but Lock to avoid flickering
	STATE_TURN_LEFT = 1,				// Turning Left
	STATE_TURN_RIGHT = 2,				// Turning Right
	STATE_LIGHT_ON = 10,				// Light ON
	STATE_LIGHT_ON_LOCK = 40,			// Light ON but Lock to avoid flickering
	STATE_LIGHT_AND_TURN_LEFT = 11,		// Turning Left with Light ON
	STATE_LIGHT_AND_TURN_RIGHT = 12,	// Turning Righ with Light OFF
	STATE_UNDEFINED = 255				// Undefined state
};

#define LONG_PRESS_DEBOUNCE_DURATION	( 3 * 1000)
#define STATE_TURN_DURATION				(10 * 1000)

/// <summary>
/// Scene Manager
/// </summary>
class SceneManagerClass
{
 private:
	 enum SceneState currentState = STATE_UNDEFINED;	// Current State
	 enum SceneState newState = STATE_UNDEFINED;		// New Reached State
	 unsigned long timerStart = 0;						// Timer
	 unsigned long timerDuration = 0;					// Timer Duration
	 unsigned long longPressTimerStart = 0;				// Long pressure Timer
	 unsigned long longPressDebounceTimerDuration = 0;	// Long pressure Timer Duration
	 uint8_t sceneStatus = 0;							// Internal Scene status for stripes updates detections

	 const AnimationFront *frontAnimation = NULL;		// Front animation
	 const AnimationRear *rearLeftAnimation = NULL;		// Rear Left animation
	 const AnimationRear *rearRightAnimation = NULL;	// Rear Right animation
	 
	 uint8_t currentFrontLEDIndex = 0;					// Led Index for Front animation
	 uint8_t currentRearLEDIndex = 0;					// Led Index for Rear animation


 public:
	 /// <summary>
	 /// Initialize the SceneManager
	 /// </summary>
	void begin();

	/// <summary>
	/// Update the Scene based on button ButtonState
	/// </summary>
	/// <param name="leftButton">Left Button current state</param>
	/// <param name="rightButton">Right Button current state</param>
	void updateScene(ButtonState leftButton, ButtonState rightButton);
	
	/// <summary>
	/// Check for Front scene update
	/// </summary>
	/// <returns>true for update</returns>
	bool isSceneUpdatedFront();
	
	/// <summary>
	/// Check for Rear Left scene update
	/// </summary>
	/// <returns>true for update</returns>
	bool isSceneUpdatedRearLeft();
	
	/// <summary>
	/// Check for Rear Right scene update
	/// </summary>
	/// <returns>true for update</returns>
	bool isSceneUpdatedRearRight();

	/// <summary>
	/// Retrieve the next Front step
	/// </summary>
	void nextSceneStepFront();
	
	/// <summary>
	/// Retrieve the next Rear Left step
	/// </summary>
	void nextSceneStepRearLeft();
	
	/// <summary>
	/// Retrieve the next Rear Right step
	/// </summary>
	void nextSceneStepRearRight();

	/// <summary>
	/// Retrieve the Front scene duration
	/// </summary>
	/// <returns>Scene duration in milliseconds</returns>
	unsigned long getSceneStepDurationFront() const;

	/// <summary>
	/// Retrieve the Rear Left scene duration
	/// </summary>
	/// <returns>Scene duration in milliseconds</returns>
	unsigned long getSceneStepDurationRearLeft() const;

	/// <summary>
	/// Retrieve the Rear Right scene duration
	/// </summary>
	/// <returns>Scene duration in milliseconds</returns>
	unsigned long getSceneStepDurationRearRight() const;

	/// <summary>
	/// Update the LED Stripes based on the current scene
	/// </summary>
	/// <param name="frontStripe">Front LED stripe</param>
	/// <param name="rearLeftStripe">Rear Left LED stripe</param>
	/// <param name="rearRightStripe">Rear Right LED stripe</param>
	void updateStripes(Adafruit_NeoPixel *frontStripe, Adafruit_NeoPixel *rearLeftStripe, Adafruit_NeoPixel *rearRightStripe);

 private:
	/// <summary>
	/// Light ON Scene
	/// </summary>
	void LightOn();
	
	/// <summary>
	/// Light OFF Scene
	/// </summary>
	void LightOff();
	
	/// <summary>
	/// Turn Left Scene
	/// </summary>
	void TurnLeft();
	
	/// /// <summary>
	/// Turn Right Scene
	/// </summary>
	void TurnRight();
};

extern SceneManagerClass SceneManager;

#endif // _SCENEMANAGER_H
