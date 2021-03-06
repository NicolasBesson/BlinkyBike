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

#include "SceneManager.h"

// For scene animation step update indicator
#define SCENE_FRONT			0
#define SCENE_REAR_RIGHT	1
#define SCENE_REAR_LEFT		2

/// <summary>
/// Initialize the SceneManager
/// </summary>
void SceneManagerClass::begin()
{
	// Clear Original status
	sceneStatus = 0;

	// Default state
	currentState = STATE_UNDEFINED;

	// Current displayed LED index
	currentFrontLEDIndex = 0;
	currentRearLEDIndex = 0;

	// Timer duration configuration 
	longPressDebounceTimerDuration = LONG_PRESS_DEBOUNCE_DURATION;
	longPressTimerStart = millis();

	// Turn off the Light
	LightOff();
}

/// <summary>
/// Check for Front scene update
/// </summary>
/// <returns>true for update</returns>
bool SceneManagerClass::isSceneUpdatedFront()
{
	if (bitRead(sceneStatus, SCENE_FRONT))
	{
		bitWrite(sceneStatus, SCENE_FRONT, false);
		return true;
	}
	
	return false;
}

/// <summary>
/// Check for Rear Left scene update
/// </summary>
/// <returns>true for update</returns>
bool SceneManagerClass::isSceneUpdatedRearLeft()
{
	if (bitRead(sceneStatus, SCENE_REAR_LEFT))
	{
		bitWrite(sceneStatus, SCENE_REAR_LEFT, false);
		return true;
	}

	return false;
}

/// <summary>
/// Check for Rear Right scene update
/// </summary>
/// <returns>true for update</returns>
bool SceneManagerClass::isSceneUpdatedRearRight()
{
	if (bitRead(sceneStatus, SCENE_REAR_RIGHT))
	{
		bitWrite(sceneStatus, SCENE_REAR_RIGHT, false);
		return true;
	}

	return false;
}

/// <summary>
/// Retrieve the next Front step
/// </summary>
void SceneManagerClass::nextSceneStepFront()
{
	frontAnimation = frontAnimation->nextAnimation;
	bitWrite(sceneStatus, SCENE_FRONT, true);
}

/// <summary>
/// Retrieve the next Rear Left step
/// </summary>
void SceneManagerClass::nextSceneStepRearLeft()
{
	rearLeftAnimation = rearLeftAnimation->nextAnimation;
	bitWrite(sceneStatus, SCENE_REAR_LEFT, true);
}

/// <summary>
/// Retrieve the next Rear Right step
/// </summary>
void SceneManagerClass::nextSceneStepRearRight()
{
	rearRightAnimation = rearRightAnimation->nextAnimation;
	bitWrite(sceneStatus, SCENE_REAR_RIGHT, true);
}

/// <summary>
/// Retrieve the Front scene duration
/// </summary>
/// <returns>Scene duration in milliseconds</returns>
unsigned long SceneManagerClass::getSceneStepDurationFront() const
{
	return frontAnimation->animationStep->StepDuration;
}

/// <summary>
/// Retrieve the Rear Left scene duration
/// </summary>
/// <returns>Scene duration in milliseconds</returns>
unsigned long SceneManagerClass::getSceneStepDurationRearLeft() const
{
	return rearLeftAnimation->animationStep->StepDuration;
}

/// <summary>
/// Retrieve the Rear Right scene duration
/// </summary>
/// <returns>Scene duration in milliseconds</returns>
unsigned long SceneManagerClass::getSceneStepDurationRearRight() const
{
	return rearRightAnimation->animationStep->StepDuration;
}

/// <summary>
/// Update the LED Stripes based on the current scene
/// </summary>
/// <param name="frontStripe">Front LED stripe</param>
/// <param name="rearLeftStripe">Rear Left LED stripe</param>
/// <param name="rearRightStripe">Rear Right LED stripe</param>
void SceneManagerClass::updateStripes(Adafruit_NeoPixel *frontStripe, Adafruit_NeoPixel *rearLeftStripe, Adafruit_NeoPixel *rearRightStripe)
{
	volatile const PixelColor *pixelTemp1 = NULL;
	volatile const PixelColor *pixelTemp2 = NULL;

	// Clear current index light
	pixelTemp1 = &pixelOff;

	frontStripe->setPixelColor(currentFrontLEDIndex, pixelTemp1->Red, pixelTemp1->Green, pixelTemp1->Blue);
	rearLeftStripe->setPixelColor(currentRearLEDIndex, pixelTemp1->Red, pixelTemp1->Green, pixelTemp1->Blue);
	rearRightStripe->setPixelColor(currentRearLEDIndex, pixelTemp1->Red, pixelTemp1->Green, pixelTemp1->Blue);

	// Move forward pixel index
	currentFrontLEDIndex = (currentFrontLEDIndex + 1) % LED_STRIPE_FRONT_NUMLED;
	currentRearLEDIndex = (currentRearLEDIndex + 1) % LED_STRIPE_REARLEFT_NUMLED;

	// Update pixels
	pixelTemp1 = &(frontAnimation->animationStep->Pixels);
	for (uint8_t i = 0; i < LED_STRIPE_FRONT_ON; i++)
	{
		frontStripe->setPixelColor((currentFrontLEDIndex + i) % LED_STRIPE_FRONT_NUMLED, pixelTemp1->Red, pixelTemp1->Green, pixelTemp1->Blue);
	}

	// Update pixels for rear left and right
	pixelTemp1 = &(rearLeftAnimation->animationStep->Pixels);
	pixelTemp2 = &(rearRightAnimation->animationStep->Pixels);
	for (uint8_t i = 0; i < LED_STRIPE_REAR_ON; i++)
	{
		// Left
		rearLeftStripe->setPixelColor((currentRearLEDIndex + i) % LED_STRIPE_REARLEFT_NUMLED, pixelTemp1->Red, pixelTemp1->Green, pixelTemp1->Blue);
		
		// Right
		rearRightStripe->setPixelColor((currentRearLEDIndex + i) % LED_STRIPE_REARRIGHT_NUMLED, pixelTemp2->Red, pixelTemp2->Green, pixelTemp2->Blue);
	}
}

/// <summary>
/// Light ON Scene
/// </summary>
inline void SceneManagerClass::LightOn()
{
	frontAnimation = AnimationPlayer::GetLightOn_Front();
	rearLeftAnimation = AnimationPlayer::GetLightOn_RearLeft();
	rearRightAnimation = AnimationPlayer::GetLightOn_RearRight();

	bitWrite(sceneStatus, SCENE_FRONT, true);
	bitWrite(sceneStatus, SCENE_REAR_LEFT, true);
	bitWrite(sceneStatus, SCENE_REAR_RIGHT, true);

}

/// <summary>
/// Light OFF Scene
/// </summary>
inline void SceneManagerClass::LightOff()
{
	frontAnimation = AnimationPlayer::GetLightOff_Front();
	rearLeftAnimation = AnimationPlayer::GetLightOff_RearLeft();
	rearRightAnimation = AnimationPlayer::GetLightOff_RearRight();

	bitWrite(sceneStatus, SCENE_FRONT, true);
	bitWrite(sceneStatus, SCENE_REAR_LEFT, true);
	bitWrite(sceneStatus, SCENE_REAR_RIGHT, true);
}

/// <summary>
/// Turn Left Scene
/// </summary>
inline void SceneManagerClass::TurnLeft()
{
	rearLeftAnimation = AnimationPlayer::GetTurn_Rear();

	// Enable Rear Right animation for light mode
	if (currentState == STATE_LIGHT_ON ||
		currentState == STATE_LIGHT_AND_TURN_RIGHT)
	{
		rearRightAnimation = AnimationPlayer::GetTurnLightOn_Rear();
	}
	else
	{
		rearRightAnimation = AnimationPlayer::GetTurnOff_Rear();
	}

	bitWrite(sceneStatus, SCENE_REAR_LEFT, true);
	bitWrite(sceneStatus, SCENE_REAR_RIGHT, true);
}

/// <summary>
/// Turn Right Scene
/// </summary>
inline void SceneManagerClass::TurnRight()
{
	rearRightAnimation = AnimationPlayer::GetTurn_Rear();

	// Enable Rear Left animation for light mode
	if (currentState == STATE_LIGHT_ON ||
		currentState == STATE_LIGHT_AND_TURN_LEFT)
	{
		rearLeftAnimation = AnimationPlayer::GetTurnLightOn_Rear();
	}
	else
	{
		rearLeftAnimation = AnimationPlayer::GetTurnOff_Rear();
	}

	bitWrite(sceneStatus, SCENE_REAR_LEFT, true);
	bitWrite(sceneStatus, SCENE_REAR_RIGHT, true);
}

/// <summary>
/// Update the Scene based on button ButtonState
/// </summary>
/// <param name="leftButton">Left Button current state</param>
/// <param name="rightButton">Right Button current state</param>
void SceneManagerClass::updateScene(ButtonState leftButton, ButtonState rightButton)
{
	unsigned long timer = millis();
	bool extendState = false;

	// Check transition candidates based on the Button pressed
	switch (currentState)
	{
	case STATE_UNDEFINED:
		newState = STATE_LIGHT_OFF;
		break;

	case STATE_LIGHT_OFF_LOCK:
		if (leftButton == RELEASED && rightButton == RELEASED)
		{
			// Check the debounce timer to avoid ON/OFF Flickering
			if (timer - longPressTimerStart > longPressDebounceTimerDuration)
			{
				// Turn On the light
				newState = STATE_LIGHT_OFF;
			}
		}
		break;

	case STATE_LIGHT_OFF:
		if (leftButton == LONG_PRESSURE && rightButton == LONG_PRESSURE)
		{
			// Start the timer
			longPressTimerStart = timer;
			
			// Turn On the light
			newState = STATE_LIGHT_ON_LOCK;
		}
		else if (leftButton == SHORT_PRESSURE && rightButton == RELEASED)
		{
			newState = STATE_TURN_LEFT;
		}
		else if (leftButton == RELEASED && rightButton == SHORT_PRESSURE)
		{
			newState = STATE_TURN_RIGHT;
		}
		break;

	case STATE_TURN_LEFT:
		if (leftButton == RELEASED && rightButton == SHORT_PRESSURE)
		{
			newState = STATE_TURN_RIGHT;
		}
		else if (leftButton == SHORT_PRESSURE && rightButton == RELEASED)
		{
			extendState = true;
		}
		else if (timer - timerStart > timerDuration)
		{
			newState = STATE_LIGHT_OFF;
		}
		break;

	case STATE_TURN_RIGHT:
		if (leftButton == SHORT_PRESSURE && rightButton == RELEASED)
		{
			newState = STATE_TURN_LEFT;
		}
		else if (leftButton == RELEASED && rightButton == SHORT_PRESSURE)
		{
			extendState = true;
		}
		else if (timer - timerStart > timerDuration)
		{
			newState = STATE_LIGHT_OFF;
		}
		break;


	case STATE_LIGHT_ON_LOCK:
		if (leftButton == RELEASED && rightButton == RELEASED)
		{
			// Check the debounce timer to avoid ON/OFF Flickering
			if (timer - longPressTimerStart > longPressDebounceTimerDuration)
			{
				// Turn On the light
				newState = STATE_LIGHT_ON;
			}
		}
		break;

	case STATE_LIGHT_ON:
		if (leftButton == LONG_PRESSURE && rightButton == LONG_PRESSURE)
		{
			// Start the timer
			longPressTimerStart = timer;

			// Turn On the light
			newState = STATE_LIGHT_OFF_LOCK;
		}
		else if (leftButton == SHORT_PRESSURE && rightButton == RELEASED)
		{
			newState = STATE_LIGHT_AND_TURN_LEFT;
		}
		else if (leftButton == RELEASED && rightButton == SHORT_PRESSURE)
		{
			newState = STATE_LIGHT_AND_TURN_RIGHT;
		}
		break;

	case STATE_LIGHT_AND_TURN_LEFT:
		if (leftButton == RELEASED && rightButton == SHORT_PRESSURE)
		{
			newState = STATE_LIGHT_AND_TURN_RIGHT;
		}
		else if (leftButton == SHORT_PRESSURE && rightButton == RELEASED)
		{
			extendState = true;
		}
		else if (timer - timerStart > timerDuration)
		{
			newState = STATE_LIGHT_ON;
		}
		break;

	case STATE_LIGHT_AND_TURN_RIGHT:
		if (leftButton == SHORT_PRESSURE && rightButton == RELEASED)
		{
			newState = STATE_LIGHT_AND_TURN_LEFT;
		}
		else if (leftButton == RELEASED && rightButton == SHORT_PRESSURE)
		{
			extendState = true;
		}
		else if (timer - timerStart > timerDuration)
		{
			newState = STATE_LIGHT_ON;
		}
		break;
	}

	// Stay in current state nothing else to do
	if (currentState == newState &&
		extendState == false) 
	{
		return;
	}

	// Switch to that state
	switch (newState)
	{
	case STATE_LIGHT_OFF_LOCK:
	case STATE_LIGHT_OFF:
		timerDuration = 0;
		// Turn light Off
		LightOff();
		break;

	case STATE_TURN_LEFT:
	case STATE_LIGHT_AND_TURN_LEFT:
		// Enable timer and extend timer on extendState
		timerStart = timer;
		timerDuration = STATE_TURN_DURATION;
		// Start turn left animation only if required
		if (extendState == false)
		{
			TurnLeft();
		}
		break;

	case STATE_TURN_RIGHT:
	case STATE_LIGHT_AND_TURN_RIGHT:
		// Enable timer and extend timer on extendState
		timerStart = timer;
		timerDuration = STATE_TURN_DURATION;
		// Start turn right animation only if required
		if (extendState == false)
		{
			TurnRight();
		}
		break;

	case STATE_LIGHT_ON_LOCK:
	case STATE_LIGHT_ON:
		// Turn light On
		LightOn();
		break;

	case STATE_UNDEFINED:
		// Leave empty for compiler complaints
		break;
	}

	currentState = newState;
}

/// <summary>
/// Scene Manager
/// </summary>
SceneManagerClass SceneManager;
