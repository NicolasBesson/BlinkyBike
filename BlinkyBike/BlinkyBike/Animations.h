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

#ifndef _ANIMATIONS_H
#define _ANIMATIONS_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "AnimationPlayer.h"

/// Front Step White Color
extern AnimationStepFront stepWhiteFront;

/// Front Step Black Color
extern AnimationStepFront stepBlackFront;

/// Rear Step Orange Color
extern AnimationStepRear stepOrangeRear;

/// Rear Step Black Color
extern AnimationStepRear stepBlackRear;

/// Rear Step Red Color
extern AnimationStepRear stepRedRear;

/// Front Animation Light Off
extern AnimationFront animationFrontOff;

/// Front Animation Light On static
extern AnimationFront animationFrontOn;

/// Front Animation Light On Blinking
extern AnimationFront animationFrontOnBlink;

/// Rear Animation Light Off
extern AnimationRear animationRearOff;

/// Rear Animation Light On (static red)
extern AnimationRear animationRearOn;

/// Rear Animation Light On (blinking red)
extern AnimationRear animationRearOnBlink;

/// Rear Animation Turn
extern AnimationRear animationRearTurn;

#endif // _ANIMATIONS_H
