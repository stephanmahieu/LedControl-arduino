/*
 * DutchFlag.cpp
 *
 * Created: 01-01-2016 12:18:05
 *  Author: Stephan
 */
#include <Arduino.h>
#include "..\LEDsetup.h"
#include "FastLED.h"
#include "DutchFlag.h"


 DutchFlag::DutchFlag(struct CRGB *pLeds) {
	leds = pLeds;
	currentPalette = dutchFlagPalette_p;
	currentBlending = NOBLEND;
 }

 char* DutchFlag::name() {
	return "DutchFlag";
 }

 void DutchFlag::show() {
	EVERY_N_MILLISECONDS(thisdelay) {
		static uint8_t startIndex = 0;
		startIndex = startIndex + 1; /* motion speed */

		FillLEDsFromPaletteColors(leds, startIndex);
	}
    FastLED.show();
}

void DutchFlag::FillLEDsFromPaletteColors(struct CRGB *leds, uint8_t colorIndex) {
	uint8_t brightness = 255;
	
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
		colorIndex += 3;
	}
}
