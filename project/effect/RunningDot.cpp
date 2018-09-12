/*
 * RunningDot.cpp
 *
 * Created: 30-12-2016 13:53:41
 *  Author: Stephan
 */
#include <Arduino.h>
#include "..\LEDsetup.h"
#include "FastLED.h"
#include "RunningDot.h"

RunningDot::RunningDot(struct CRGB *pLeds) {
	leds = pLeds;
}

char* RunningDot::name() {
	return "RunningDot";
}

void RunningDot::show() {
	// Turn our current led on to white, then show the leds
	leds[whiteLedPos] = CRGB::White;

	// Show the leds (only one of which is set to white, from above)
	FastLED.show();

	// Turn our current led back to black for the next loop around
	leds[whiteLedPos++] = CRGB::Black;

	if (whiteLedPos >= NUM_LEDS) {
		whiteLedPos = 0;
	}
 }