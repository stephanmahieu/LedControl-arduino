/*
 * RainbowMarch.cpp
 *
 * Created: 29-12-2015 13:05:44
 *  Author: Stephan
 */
#include <Arduino.h>
#include "..\LEDsetup.h"
#include "FastLED.h"
#include "RainbowMarch.h"


RainbowMarch::RainbowMarch(struct CRGB *pLeds) {
	leds = pLeds;
}

char* RainbowMarch::name() {
	return "Rainbowmarch";
}

void RainbowMarch::show() {
	EVERY_N_MILLISECONDS(thisdelay) {
		thishue++;                                        // Increment the starting hue.
		fill_rainbow(leds, NUM_LEDS, thishue, deltahue);  // Use FastLED's fill_rainbow routine.
	}
	//show_at_max_brightness_for_power();
	FastLED.show();
}