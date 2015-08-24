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

#include "MainApp.h"
#include "SceneManager.h"

MainAppClass MainApp;

/// <summary>
/// Front Timer callback function
/// </summary>
void loadSceneFront_callback()
{
	MainApp.loadSceneFrontCallback();
}

/// <summary>
/// Rear Left Timer callback function
/// </summary>
void loadSceneRearLeft_callback()
{
	MainApp.loadSceneRearLeftCallback();
}

/// <summary>
/// Rear Right Timer callback function
/// </summary>
void loadSceneRearRight_callback()
{
	MainApp.loadSceneRearRightCallback();
}

/// <summary>
/// Main application intialization
/// </summary>
void MainAppClass::init()
{
	// Initialize the LED Stripe	
	frontLight.begin();
	rearLeftLight.begin();
	rearRightLight.begin();

	// Initialize the timer
	appTimer.configureTimer(SCENE_TIMER_FRONT, 2 * 1000, loadSceneFront_callback);
	appTimer.configureTimer(SCENE_TIMER_REAR_LEFT, 2 * 1000, loadSceneRearLeft_callback);
	appTimer.configureTimer(SCENE_TIMER_REAR_RIGHT, 2 * 1000, loadSceneRearRight_callback);


	// Clear the LED Stripe
	frontLight.show();
	rearLeftLight.show();
	rearRightLight.show();
}

/// <summary>
/// Main application loop
/// </summary>
void MainAppClass::loop()
{
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

	// Update the Front and Rear LED Stripes
	SceneManager.updateStripes(&frontLight, &rearLeftLight, &rearRightLight);
	
	// Display the LED Stripes
	frontLight.show();
	rearLeftLight.show();
	rearRightLight.show();

	// Update time info
	appTimer.run();
}

/// <summary>
/// Load next Front Scene step
/// </summary>
inline void MainAppClass::loadSceneFrontCallback()
{
	SceneManager.nextSceneStepFront();
}

/// <summary>
/// Load next Rear Left Scene step
/// </summary>
inline void MainAppClass::loadSceneRearLeftCallback()
{
	SceneManager.nextSceneStepRearLeft();
}

/// <summary>
/// Load next Rear Right Scene step
/// </summary>
inline void MainAppClass::loadSceneRearRightCallback()
{
	SceneManager.nextSceneStepRearRight();
}
