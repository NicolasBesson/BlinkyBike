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

#ifndef _ANNIMATIONPLAYER_H
#define _ANNIMATIONPLAYER_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Stripes.h"

#define BLACK	0x000000
#define	RED		0xFF0000
#define	ORANGE	0xFFA200
#define	BLUE	0x0000FF
#define	WHITE	0xFFFFFF

#define R(x) ((uint8_t)(((uint32_t)x >> 16) & 0xFF))
#define G(x) ((uint8_t)(((uint32_t)x >>  8) & 0xFF))
#define B(x) ((uint8_t)(((uint32_t)x >>  0) & 0xFF))

#define COLOR_PIXEL(colorPixel)  { R(colorPixel), G(colorPixel), B(colorPixel) }

/// <summary>
/// LED Pixel description
/// </summary>
struct PixelColor
{
	uint8_t  Red;	// Red
	uint8_t  Green;	// Green
	uint8_t  Blue;	// Blue
};

/// <summary>
/// Front Step
/// </summary>
struct AnimationStepFront
{
	unsigned long StepDuration;	// Step Duration in ms
	PixelColor Pixels;			// Step Pixels color
};

/// <summary>
/// Rear Step
/// </summary>
struct AnimationStepRear
{
	unsigned long StepDuration;	// Step Duration in ms
	PixelColor Pixels;			// Step Pixels color
};

/// <summary>
/// Front Animation
/// </summary>
struct AnimationFront
{
	AnimationStepFront *animationStep;	// Front Step
	AnimationFront *nextAnimation;		// Next Front animation
};

/// <summary>
/// Rear Animation
/// </summary>
struct AnimationRear
{
	AnimationStepRear *animationStep;	// Rear Step
	AnimationRear *nextAnimation;		// Next Rear animation
};

/// Off Pixel
extern const PixelColor pixelOff;

/// <summary>
/// Animation player
/// </summary>
class AnimationPlayer
{
 public:
	// Light On
	static const AnimationFront* GetLightOn_Front();
	static const AnimationRear* GetLightOn_RearLeft();
	static const AnimationRear* GetLightOn_RearRight();

	// Light Off
	static const AnimationFront* GetLightOff_Front();
	static const AnimationRear* GetLightOff_RearLeft();
	static const AnimationRear* GetLightOff_RearRight();

	// Light Turn
	static const AnimationRear* GetTurn_Rear();
	static const AnimationRear* GetTurnOff_Rear();
	static const AnimationRear* GetTurnLightOn_Rear();
};

#endif // _ANNIMATIONPLAYER_H
