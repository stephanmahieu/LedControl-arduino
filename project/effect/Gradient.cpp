/*
 * Gradient.cpp
 *
 * Created: 18-12-2016 22:57:04
 *  Author: Stephan
 */ 
#include <Arduino.h>
#include "..\LEDsetup.h"
#include "FastLED.h"
#include "Gradient.h"


Gradient::Gradient(struct CRGB *pLeds) {
	leds = pLeds;
}

char* Gradient::name() {
	return "Gradient";
}

void Gradient::show() {
	blendme();
	FastLED.show();
}

void Gradient::blendme() {
	uint8_t starthue = beatsin8(5, 0, 255);
	uint8_t endhue = beatsin8(12, 0, 255);
	if (starthue < endhue) {
		fill_gradient(leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), FORWARD_HUES);    // If we don't have this, the color fill will flip around
	} else {
		fill_gradient(leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), BACKWARD_HUES);
	}
}
