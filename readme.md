![BlinkyBike Logo](/Pictures/BlinkyBike_logo_small.jpg "Blinky Bike Logo")

When ridding for your commute or for pleasure, being visible on the road is always a nightmare, as either your bike light system in daylight is not visible, or because drivers never know when you turn in night conditions.

The Blinky Bike project is the ultimate solution to add light system to any Bike, (and electric Bike) using a 5V power bank or the onboard bike Battery. It relies on NeoPixel LEDs (WS2812) flexible stripes, for the Front and Rear. The system based on an Atmel ATtiny 85 micro-controller, and allows different light modes that can be selected using two water proof switches (One for the Left hand and one for the Right hand).

## Device Usage
The device Left and Right buttons are the only interface with the system allowing to :

* Turn ON and OFF the light system
* Turn Left and Right indicator

Switches operations are :

| Left Button | Right Button | Action                |
|:-----------:|:------------:|:----------------------|
| Release     | Release      | Nothing               |
| Short       | Release      | Turn Left             |
| Release     | Short        | Turn Right            |
| Long        | Long         | Turn Light ON or OFF  |

![BlinkyBike Left Button](/Pictures/Button_Left1.jpg "Left Button") ![BlinkyBike Right Button](/Pictures/Button_Right1.jpg "Right Button")

## LEDs stripes
The system is based on a Front LED flexible stripe and two Rear LED Flexible Stripe, one for the Left and one for the Right indicator.
The Front and Rear LEDs stripes are composed of a total of 30 LEDs, 8 for the Front and 11 for each Rear stripes.

![BlinkyBike Schematic](/Pictures/FrontBack_Stripes_On.jpg "Front and Rear Stripes")

## Power consideration
The system is designed to be power friendly with the e-Bike battery, as the battery might not be able to provide the full power required to have all the LEDs turned on at the same time. As the NeoPixel RGB LEDs (WS2812) consumes 20 mA per color channel, with a total of 60 mA (3 channels * 20 mA) when the LED is turned full bright White color (Red = 255, Green = 255, Blue = 255). The challenge is to not be over 500 mA (power limit supplied by the Battery on my e-Bike). I have applied a secure level set to 450 mA maximum. Leading then to a limit of 7 LEDs active at a time.
Having only 7 LEDs is really limitating for a bike light system, so the solution is to multiplex the LEDs and ensure that only those 7 LEDs are on, while all the others are off. If the multiplexing switch is performed fast enough, it should be possible to make it not visible for a Human eye. 
Therefore, the ATTiny firmware is taking care of the current limitation by switching on and off the LEDs, remaining only 7 LEDs on at a time, giving a maximum power consumption for the LEDs of 420 mA.

This can be adjusted by editing the [Stripes.h](/BlinkyBike/BlinkyBike/Stripes.h) file :
```c
// Number of LED
#define LED_STRIPE_FRONT_ON   3
#define LED_STRIPE_REAR_ON    2
```

## Light animation
When riding a bike a night, and having fix light color is not the optimal solution to be visible by drivers. Therefore having some flashing, blinking mode for the lights gives more visibility and make your bike more attractive. When light is On, the Front stripe displays a fast blinking animation at a frequency of about 10 Hz.
When turning left or right, the visual animation is orange and blinky.
So having a flexible software architecture is a must have. With AnimationStep and Animation it is fairly simple to describe an animation. 

The types are described as following :
```c
struct AnimationStepFront
{
	unsigned long StepDuration;	// Step Duration in ms
	PixelColor Pixels[1];		// Step Pixels color
};

struct AnimationFront
{
	AnimationStepFront *animationStep;	// Front Step
	AnimationFront *nextAnimation;		// Next Front animation
};
```

And an animation is described as following :
```c
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

/* Animations for Front */
AnimationFront animationFrontOff = { &stepBlackFront, &animationFrontOff };
AnimationFront animationFrontOn = { &stepWhiteFront, &animationFrontOn };

```


# Building the Hardware
The hardware is minimalistic as the Neopixel and ATTiny are embedding all the discrete components that you normally use to drive RGB LED.

![BlinkyBike Schematic](/Hardware/BlinkyBike_schéma.png "Schematic")

The Blinky Bike system is built using the following hardware :

* AtTiny85
* NeoPixel Stripes
 * 1x 8 LEDs
 * 2x 11 LEDs
* 3x 380 Ohms resistor
* 1x 10 kOhms resistor
* 1x 1000 µF capacitor
* 2x water proof switches

You won't find any PCB layout, as I'm using through hole prototyping board, developed with Fritzing software.

![Prototyping board](/Hardware/BlinkyBike_bb.png "Prototyping board")


# Building the Software
The ATTiny 85 is a really cool Micro Controller that have 8 KB of Flash and 512 B of RAM to run any kind of C or C++ software. This gives some space to run a simple software and for this reason some optimization are required.

The project has been developed in C++ (C++11) in order to reuse and give more flexibility in case of development of new features. It is required to use the VisualMicro extension for Visual Studio 2013 in order to build the project.

AdaFruit is providing a library to drive the Neopixel devices, that you can directly integrate in your Arduino IDE. But this code has been designed to support various modes in order to address major use cases. The source code repository is containing an optimized version that works only with the Neopixels that I have selected and might not work if you choose a different one.

The Neopixel device requires specific timings that can't be reach when using the ATTiny 85 in 4 MHz (its default configuration) and therefore requires to use the 8 Mhz mode. So it is mandatory to burn the correct fuses in the ATTIny before deploying the firmware. This can be done from the Arduino IDE by selecting the ATTiny 85 target and selecting the clock frequency to 8 MHz (internal).

## Tools
Before starting some tools are required :

* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [Visual Studio Community 2013 with Update 5](https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx) or Visual Studio 2015 Community Edition
* [VisualMicro](http://www.visualmicro.com/) a Visual Studio plugin for Arduino development
* USBTinyISP programer

Install Visual Studio 2013/2015, and make sure to select the support for C++ (Visual C++) during installation.

Install the Arduino IDE application, and launch the application. You first need to add the support of the ATtiny familly as by default only Arduino based platforms are supported. From the File menu, select the Preferences submenu, and then find the “Additional Boards Manager URLs” field near the bottom of the dialog. Add the following url : https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json
You can then validate and close the preferences dialog box. Then from the Tools menu you have to :

* Select the Board entry and choose **Board Manager** to add attiny board support.
* Select **ATtiny** as Board
* Select **ATtiny85** as Processor
* Select **8MHz (Internal)** as Clock
* Select **USBtinyISP** as Programmer

Close the **Arduino IDE** application and install the Visual Micro plugin for Visual Studio.
Launch **Visual Studio** and open the BlinkyBike.sln from the project folders.
On first usage of Visual Micro, you have to configure the various parameters of the plugin.

* Select the version of the IDE you select
* Enter the path to the tool installation folder

Then validate the configuration window and access the Visual Studio IDE. From vMicro menu :

* Select **ATtiny w/ ATtiny85** as Board
* Select **8MHz (Internal)** as Option2
* Select **USBtinyISP** as Programmer

The development environment is now ready for building and flashing.

## Compilation
The source code compiles in Visual Studio 2013 and 2015 through the VisualMicro plugin.

## Programming
The ATtiny 85 micro controller can be programmed using the USBTinyISP programmer. THe programmer is visible through a serial com port. You need to identify the associate port index (using Windows Device Manager) in order configure the Visual Micro plugin. 

![USB Tiny ISP](/Pictures/USBtinyISP.jpg "USB Tiny ISP")

You need to wire the programmer as following:

![USB Tiny ISP with ATtiny85](/Pictures/USBtinyISP_attiny85_connection.png "USB Tiny ISP with ATtiny85")

# Assembling
## Left and Right Button
The Left and Right waterproof buttons are the interface for the BlinkyBike Light System management, as described earlier. It is suggested to mount them close to the Grip and Shifter to avoid ridding distractions. So for this reason, I mount them next to the shifter screw, using a stainless and steal pad as illustrated on the first fourth pictures.

![BlinkyBike Left Button](/Pictures/Button_Left1.jpg "Left Button") ![BlinkyBike Right Button](/Pictures/Button_Right1.jpg "Right Button")
![BlinkyBike Left Button](/Pictures/Button_Left2.jpg "Left Button") ![BlinkyBike Right Button](/Pictures/Button_Right2.jpg "Right Button")

## Front and Rear LED Stripes
To ensure a good visibility of the light, I would suggest you to stick the stripes on the Frame of the bike. For the Rear, you can use the rear frame parts that are holding the rear wheel, there is usually 15 to centimeters free, between the brake and the wheel bolt. For the Front, the head tube is the ideal spot, but you have to ensure that no brake cable is hiding even partially the LED stripe.

![Rear Full On](/Pictures/Rear_Stripes_On.png "Rear Full On") ![Rear Blink](/Pictures/Rear_Stripes_Blink.png "Rear Blink")

## System Casing
The PCB is small enough to fit in an aspirin tube, that have hermetic cap. Only four holes are required to get the buttons, LED stripes and power cords to get in. To maintain the packaging hermetic, then you can use hot glue inside the cap.
Once done, and enclosed correctly the tube is small enough to get fixed under the handlebar using plastic ties.

![BlinkyBike PCB](/Pictures/BlinkyBike_PCB.jpg "PCB")
![BlinkyBike Casing](/Pictures/BlinkyBike_Casing.jpg "Casing")

## Battery holder
The device is 5 Volts powered, so a USB Power Bank of 10000 mAh is a perfect solution for 3 weeks of daily commute. You can find small devices at you favorite store.

## Full System
![BlinkyBike Assembled](/Pictures/BlinkyBike_Assembled.jpg "Assembled")


