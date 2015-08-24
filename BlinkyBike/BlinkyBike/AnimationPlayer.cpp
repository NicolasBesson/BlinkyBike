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

const PixelColor pixelOff = COLOR_PIXEL(BLACK);

/// <summary>
/// Light On for Front accessor
/// </summary>
/// <returns>Animation</returns>
const AnimationFront* AnimationPlayer::GetLightOn_Front()
{
	return &animationFrontOnBlink;
}

/// <summary>
/// Light On for Rear Right accessor
/// </summary>
/// <returns>Animation</returns>
const AnimationRear* AnimationPlayer::GetLightOn_RearLeft()
{
	return &animationRearOn;
}

/// <summary>
/// Light On for Rear Right accessor
/// </summary>
/// <returns>Animation</returns>
const AnimationRear* AnimationPlayer::GetLightOn_RearRight()
{
	return &animationRearOn;
}

/// <summary>
/// Light Off for Front accessor
/// </summary>
/// <returns>Animation</returns>
const AnimationFront* AnimationPlayer::GetLightOff_Front()
{
	return &animationFrontOff;
}

/// <summary>
/// Light Off for Rear Left accessor
/// </summary>
/// <returns>Animation</returns>
const AnimationRear* AnimationPlayer::GetLightOff_RearLeft()
{
	return &animationRearOff;
}

/// <summary>
/// Light Off for Rear Right accessor
/// </summary>
/// <returns>Animation</returns>
const AnimationRear* AnimationPlayer::GetLightOff_RearRight()
{
	return &animationRearOff;
}

/// <summary>
/// Light Turn for Rear accessor
/// </summary>
/// <returns>Animation</returns>
const AnimationRear* AnimationPlayer::GetTurn_Rear()
{
	return &animationRearTurn;
}

/// <summary>
/// Light Turn Off for Rear accessor
/// </summary>
/// <returns>Animation</returns>
const AnimationRear* AnimationPlayer::GetTurnOff_Rear()
{
	return &animationRearOff;
}

/// <summary>
/// Light On for Rear accessor
/// </summary>
/// <returns>Animation</returns>
const AnimationRear* AnimationPlayer::GetTurnLightOn_Rear()
{
	return &animationRearOn;
}
