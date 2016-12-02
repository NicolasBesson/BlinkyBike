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

#ifndef _STRIPES_H
#define _STRIPES_H

// LED Stripes configuration
#define LED_STRIPE_FRONT_NUMLED			8
#define LED_STRIPE_REAR_NUMLED			11

// Front Lights
#define LED_STRIPE_FRONT_PIN			4

// Rear Lights
#define LED_STRIPE_REARLEFT_PIN			0
#define LED_STRIPE_REARLEFT_NUMLED		LED_STRIPE_REAR_NUMLED
#define LED_STRIPE_REARRIGHT_PIN		1
#define LED_STRIPE_REARRIGHT_NUMLED		LED_STRIPE_REAR_NUMLED

// Number of LED
#define LED_STRIPE_FRONT_ON				3
#define LED_STRIPE_REAR_ON				6

#endif // _STRIPES_H
