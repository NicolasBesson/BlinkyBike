#include <Adafruit_NeoPixel.h> 

#define NUM_LEDS 60
#define DATA_PIN 4

// Start Strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
	strip.begin();
	strip.show(); // Initialize all pixels to 'off'

}

void loop()
{
	colorWipe(strip.Color(0xFF, 0x00, 0x00), 2000);
	colorWipe(strip.Color(0x00, 0xFF, 0x00), 2000);
	colorWipe(strip.Color(0x00, 0x00, 0xFF), 2000);
	// color wipe random RGB
	colorWipe(strip.Color(random(255), random(255), random(255)), 500);
	
}

// Fill the dots one after the other with a color
// Modified from Neopixel sketch to break on button press

void colorWipe(uint32_t c, uint16_t wait) {
	for (uint16_t i = 0; i<strip.numPixels(); i++) {
		strip.setPixelColor(i, c);
	}
	strip.show();
	delay(wait);
}