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
void SceneManagerClass::init()
{
	// Clear Original status
	sceneStatus = 0;

	// Default state
	currentState = STATE_UNDEFINED;

	// Current displyed LED index
	currentFrontLEDIndex = 0;
	currentRearLEDIndex = 0;

	// Timer duration configuration 
	longPressDebounceTimerDuration = LONG_PRESS_DEBOUNCE_DURATION;
	longPressTimerStart = millis();
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
	const PixelColor *pixel;
	// Front
	// Clear current index light
	pixel = &pixelOff;
	frontStripe->setPixelColor(currentFrontLEDIndex, pixel->Red, pixel->Green, pixel->Blue);

	// Move forward
	currentFrontLEDIndex = (++currentFrontLEDIndex) % LED_STRIPE_FRONT_NUMLED;

	// Update pixels
#if NOT_OPTIMIZED
	for (uint8_t i = 0; i < LED_STRIPE_FRONT_ON; i++)
	{
		pixel = &frontAnimation->animationStep->Pixels[(currentFrontLEDIndex + i) % LED_STRIPE_FRONT_NUMLED];
		frontStripe->setPixelColor((currentFrontLEDIndex + i) % LED_STRIPE_FRONT_NUMLED, pixel->Red, pixel->Green, pixel->Blue);
	}
#else
	pixel = &(frontAnimation->animationStep->Pixels[0]);
	for (uint8_t i = 0; i < LED_STRIPE_FRONT_ON; i++)
	{
		frontStripe->setPixelColor((currentFrontLEDIndex + i) % LED_STRIPE_FRONT_NUMLED, pixel->Red, pixel->Green, pixel->Blue);
	}
#endif

	// Rear Left and Right
	// Clear current index light
	pixel = &pixelOff;
	rearLeftStripe->setPixelColor(currentRearLEDIndex, pixel->Red, pixel->Green, pixel->Blue);
	rearRightStripe->setPixelColor(currentRearLEDIndex, pixel->Red, pixel->Green, pixel->Blue);

	// Move forward
	currentRearLEDIndex = (++currentRearLEDIndex) % LED_STRIPE_REARLEFT_NUMLED;

	// Update pixels for rear left and right
#if NOT_OPTIMIZED
	for (uint8_t i = 0; i < LED_STRIPE_REAR_ON; i++)
	{
		pixel = &rearLeftAnimation->animationStep->Pixels[(currentRearLEDIndex + i) % LED_STRIPE_REARLEFT_NUMLED];
		rearLeftStripe->setPixelColor((currentRearLEDIndex + i) % LED_STRIPE_REARLEFT_NUMLED, pixel->Red, pixel->Green, pixel->Blue);

		pixel = &rearRightAnimation->animationStep->Pixels[(currentRearLEDIndex + i) % LED_STRIPE_REARRIGHT_NUMLED];
		rearRightStripe->setPixelColor((currentRearLEDIndex + i) % LED_STRIPE_REARRIGHT_NUMLED, pixel->Red, pixel->Green, pixel->Blue);
	}
#else
	for (uint8_t i = 0; i < LED_STRIPE_REAR_ON; i++)
	{
		// Left
		pixel = &(rearLeftAnimation->animationStep->Pixels[0]);
		rearLeftStripe->setPixelColor((currentRearLEDIndex + i) % LED_STRIPE_REARLEFT_NUMLED, pixel->Red, pixel->Green, pixel->Blue);
		
		// Right
		pixel = &(rearRightAnimation->animationStep->Pixels[0]);
		rearRightStripe->setPixelColor((currentRearLEDIndex + i) % LED_STRIPE_REARRIGHT_NUMLED, pixel->Red, pixel->Green, pixel->Blue);
	}
#endif
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

	if (currentState == STATE_LIGHT_ON)
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

	if (currentState == STATE_LIGHT_ON)
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
		else if (timer - timerStart > timerDuration)
		{
			newState = STATE_LIGHT_ON;
		}
		break;
	}

	// Stay in current state nothing else to do
	if (currentState == newState) 
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
		// Enable timer
		timerStart = timer;
		timerDuration = STATE_TURN_DURATION;
		// Start turn left animation
		TurnLeft();
		break;

	case STATE_TURN_RIGHT:
	case STATE_LIGHT_AND_TURN_RIGHT:
		// Enable timer
		timerStart = timer;
		timerDuration = STATE_TURN_DURATION;
		// Start turn right animation
		TurnRight();
		break;

	case STATE_LIGHT_ON_LOCK:
	case STATE_LIGHT_ON:
		// Turn light On
		LightOn();
		break;
	}

	currentState = newState;
}

/// <summary>
/// Scene Manager
/// </summary>
SceneManagerClass SceneManager;
