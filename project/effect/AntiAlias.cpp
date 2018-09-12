/*
 * AntiAlias.cpp
 *
 * Created: 26-12-2016 16:40:51
 *  Author: Stephan
 */ 
#include <Arduino.h>
#include "..\LEDsetup.h"
#include "FastLED.h"
#include "AntiAlias.h"


AntiAlias::AntiAlias(struct CRGB *pLeds) {
	leds = pLeds;
}

char* AntiAlias::name() {
	return "AntiAlias";
}

void AntiAlias::show() {
	EVERY_N_MILLISECONDS(thisdelay) {
		// Update the "Fraction Bar" by 1/16th pixel every time
		F16pos += F16delta;
  
		// wrap around at end
		// remember that F16pos contains position in "16ths of a pixel"
		// so the 'end of the strip' is (NUM_LEDS * 16)
		if (F16pos >= (NUM_LEDS * 16)) {
			F16pos -= (NUM_LEDS * 16);
		}
  
		// Draw everything:
		// clear the pixel buffer
		memset8(leds, 0, NUM_LEDS * sizeof(CRGB));
  
		// advance to the next hue
		Fhue16 = Fhue16 + 19;
  
		// draw the Fractional Bar, length=4px
		drawFractionalBar(F16pos, Width, Fhue16 / 256);
  	}
	
	FastLED.show();
}


// Draw a "Fractional Bar" of light starting at position 'pos16', which is counted in
// sixteenths of a pixel from the start of the strip.  Fractional positions are
// rendered using 'anti-aliasing' of pixel brightness.
// The bar width is specified in whole pixels.
// Arguably, this is the interesting code.
void AntiAlias::drawFractionalBar(int pos16, int width, uint8_t hue) {
	int i = pos16 / 16;          // convert from pos to raw pixel number
	uint8_t frac = pos16 & 0x0F; // extract the 'factional' part of the position
	
	// brightness of the first pixel in the bar is 1.0 - (fractional part of position)
	// e.g., if the light bar starts drawing at pixel "57.9", then
	// pixel #57 should only be lit at 10% brightness, because only 1/10th of it
	// is "in" the light bar:
	//
	//                       57.9 . . . . . . . . . . . . . . . . . 61.9
	//                        v                                      v
	//  ---+---56----+---57----+---58----+---59----+---60----+---61----+---62---->
	//     |         |        X|XXXXXXXXX|XXXXXXXXX|XXXXXXXXX|XXXXXXXX |
	//  ---+---------+---------+---------+---------+---------+---------+--------->
	//                   10%       100%      100%      100%      90%
	//
	// the fraction we get is in 16ths and needs to be converted to 256ths,
	// so we multiply by 16.  We subtract from 255 because we want a high
	// fraction (e.g. 0.9) to turn into a low brightness (e.g. 0.1)
	uint8_t firstpixelbrightness = 255 - (frac * 16);
	
	// if the bar is of integer length, the last pixel's brightness is the
	// reverse of the first pixel's; see illustration above.
	uint8_t lastpixelbrightness  = 255 - firstpixelbrightness;
	
	// For a bar of width "N", the code has to consider "N+1" pixel positions,
	// which is why the "<= width" below instead of "< width".
	
	uint8_t bright;
	for (int n = 0; n <= width; n++) {
		if (n == 0) {
			// first pixel in the bar
			bright = firstpixelbrightness;
		} else if (n == width ) {
			// last pixel in the bar
			bright = lastpixelbrightness;
		} else {
			// middle pixels
			bright = 255;
		}
		
		leds[i] += CHSV(hue, 255, bright);
		i++;
		if (i == NUM_LEDS) {
			i = 0; // wrap around
		}
	}
}