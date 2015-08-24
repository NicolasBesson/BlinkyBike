#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Adafruit_NeoPixel.h>
#include "Timer.h"

#define NUM_LEDS	60
#define DATA_PIN	4

// Start Strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);
Timer timer = Timer();


void timerCallbaclk1()
{
	if (strip.getPixelColor(0))
	{
		strip.setPixelColor(0, 0x00, 0x00, 0x00);
	}
	else
	{
		strip.setPixelColor(0, 0xFF, 0x00, 0x00);
	}

}

void timerCallbaclk2()
{
	if (strip.getPixelColor(1))
	{
		strip.setPixelColor(1, 0x00, 0x00, 0x00);
	}
	else
	{
		strip.setPixelColor(1, 0x00, 0xFF, 0x00);
	}


}

void timerCallbaclk3()
{
	if (strip.getPixelColor(2))
	{
		strip.setPixelColor(2, 0x00, 0x00, 0x00);
	}
	else
	{
		strip.setPixelColor(2, 0x00, 0x00, 0xFF);
	}


}


void setup()
{

	strip.begin();
	strip.show(); // Initialize all pixels to 'off'

	timer.configureTimer(0, 2000, timerCallbaclk1);
	timer.configureTimer(1, 200, timerCallbaclk2);
	timer.configureTimer(2, 500, timerCallbaclk3);

	delay(2 * 1000);
}


void loop()
{
//		strip.setPixelColor(0, 255, 0, 0);


	strip.show();
	timer.run();
}
