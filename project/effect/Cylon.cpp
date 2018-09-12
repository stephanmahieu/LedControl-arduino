/*
 * Cylon.cpp
 *
 * Created: 18-12-2016 15:55:36
 *  Author: Stephan
 */ 
#include <Arduino.h>
#include "..\LEDsetup.h"
#include "FastLED.h"
#include "Cylon.h"


Cylon::Cylon(struct CRGB *pLeds) {
	leds = pLeds;
}

char* Cylon::name() {
	return "Cylon";
}

void Cylon::show() {
	EVERY_N_MILLISECONDS(thisdelay) {
		fadeall();
		
		index += direction;
		
		if (index > (NUM_LEDS-1)) {
			index = NUM_LEDS-1;
			direction = -1;
		} else if (index <= 0) {
			index = 0;
			direction = 1;
		}
		
		// Set the index'th led to red
		leds[index] = CHSV(hue++, 255, 255);
	}
	FastLED.show();
}

void  Cylon::fadeall() {
	for(int i = 0; i < NUM_LEDS; i++) {
		leds[i].nscale8(250);
	}
}
