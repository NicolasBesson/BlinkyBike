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

#include "AnimationPlayer.h"
#include "Animations.h"

/* Animations for Front */
AnimationFront animationFrontOff = { &stepBlackFront, &animationFrontOff };
AnimationFront animationFrontOn = { &stepWhiteFront, &animationFrontOn };
AnimationFront animatonFrontOnBlinkOff = { &stepBlackFront, &animationFrontOnBlink };
AnimationFront animationFrontOnBlink = { &stepWhiteFront, &animatonFrontOnBlinkOff };

/* Animations for Rear */
AnimationRear animationRearOff = { &stepBlackRear, &animationRearOff };
AnimationRear animationRearOn = { &stepRedRear, &animationRearOn };
AnimationRear animatonRearOnBlinkOff = { &stepBlackRear, &animationRearOnBlink };
AnimationRear animationRearOnBlink = { &stepRedRear, &animatonRearOnBlinkOff };
AnimationRear animatonRearTurnOff = { &stepBlackRear, &animationRearTurn };
AnimationRear animationRearTurn = { &stepOrangeRear, &animatonRearTurnOff };

/*
 * Animations Steps
 */
AnimationStepFront stepWhiteFront = { 150,
{ 
	COLOR_PIXEL(WHITE) 
}
};

AnimationStepFront stepBlackFront = { 50,
{ 
	COLOR_PIXEL(BLACK) 
}
};

AnimationStepRear stepOrangeRear = { 1000,
{ 
	COLOR_PIXEL(ORANGE)
}
};

AnimationStepRear stepBlackRear = { 1000,
{ 
	COLOR_PIXEL(BLACK)
}
};

AnimationStepRear stepRedRear = { 1000,
{ 
	COLOR_PIXEL(RED)
}
};
