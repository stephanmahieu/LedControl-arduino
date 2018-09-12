/*
 * Blank.cpp
 *
 * Created: 01-01-2016 11:58:05
 *  Author: Stephan
 */
#include <Arduino.h>
#include "..\LEDsetup.h"
#include "FastLED.h"
#include "Blank.h"


Blank::Blank(struct CRGB *pLeds) {
	leds = pLeds;
}

char* Blank::name() {
	return "Black";
}

void Blank::show() {
	fill_solid(leds, NUM_LEDS, CRGB::Black);
	show_at_max_brightness_for_power();
}