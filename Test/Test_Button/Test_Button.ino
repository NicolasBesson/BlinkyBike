#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Adafruit_NeoPixel.h>
#include "Button.h"

#define NUM_LEDS	60
#define DATA_PIN	4

#define BTN_LEFT_PIN			3
#define BTN_LEFT_DEBOUNCE		10
#define BTN_LEFT_HOLD_TIMEOUT	(2*1000)
#define BTN_LEFT_STATE_TIMEOUT	(2*1000)

#define BTN_RIGHT_PIN			2
#define BTN_RIGHT_DEBOUNCE		10
#define BTN_RIGHT_HOLD_TIMEOUT	(2*1000)
#define BTN_RIGHT_STATE_TIMEOUT	(2*1000)


// Start Strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);
Button buttonLeft = Button(BTN_LEFT_PIN, BTN_LEFT_DEBOUNCE, BTN_LEFT_HOLD_TIMEOUT, BTN_LEFT_STATE_TIMEOUT, BUTTON_PULLUP);
Button buttonRight = Button(BTN_RIGHT_PIN, BTN_RIGHT_DEBOUNCE, BTN_RIGHT_HOLD_TIMEOUT, BTN_RIGHT_STATE_TIMEOUT, BUTTON_PULLUP);

void setup()
{

	strip.begin();
	strip.show(); // Initialize all pixels to 'off'
	//button.setHoldThreshold(2 * 1000);
	delay(2 * 1000);
}


void loop()
{
	switch (buttonLeft.getButtonState())
	{
	case SHORT_PRESSURE:
		strip.setPixelColor(0, 255, 0, 0);
		if (strip.getPixelColor(3) == strip.Color(255, 255, 255))
		{
			strip.setPixelColor(3, 0, 0, 0);
		}
		else
		{
			strip.setPixelColor(3, 255, 255, 255);
		}
		buttonLeft.clearButtonState();
		break;
	case LONG_PRESSURE:
		strip.setPixelColor(0, 0, 255, 0);
		break;
	case RELEASED:
		strip.setPixelColor(0, 0, 0, 255);
		break;
	}

	switch (buttonRight.getButtonState())
	{
	case SHORT_PRESSURE:
		strip.setPixelColor(1, 255, 0, 0);
		break;
	case LONG_PRESSURE:
		strip.setPixelColor(1, 0, 255, 0);
		break;
	case RELEASED:
		strip.setPixelColor(1, 0, 0, 255);
		break;
	}



	strip.show();

}
