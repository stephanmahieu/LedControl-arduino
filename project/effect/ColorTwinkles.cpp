/*
 * ColorTwinkles.cpp
 *
 * Created: 01-01-2016 23:25:04
 *  Author: Stephan
 */
 #include <Arduino.h>
 #include "..\LEDsetup.h"
 #include "FastLED.h"
 #include "ColorTwinkles.h"


 ColorTwinkles::ColorTwinkles(struct CRGB *pLeds) {
	leds = pLeds;
	palette = RainbowColors_p;
	thisdelay = 20;
 }

 char* ColorTwinkles::name() {
	return "ColorTwinkles";
 }

 void ColorTwinkles::show() {
	EVERY_N_MILLISECONDS(thisdelay) {
		twinkle();
	}
	FastLED.show();
 }
 
 void ColorTwinkles::twinkle() {
	// Make each pixel brighter or darker, depending on
	// its 'direction' flag.
	brightenOrDarkenEachPixel(FADE_IN_SPEED, FADE_OUT_SPEED);
	
	// Now consider adding a new random twinkle
	if (random8() < DENSITY ) {
		int pos = random16(NUM_LEDS);
		if (!leds[pos]) {
			leds[pos] = ColorFromPalette(palette, random8(), STARTING_BRIGHTNESS, NOBLEND);
			setPixelDirection(pos, GETTING_BRIGHTER);
		}
	}	 
 }
	  
 void ColorTwinkles::brightenOrDarkenEachPixel(fract8 fadeUpAmount, fract8 fadeDownAmount) {
	for (uint16_t i = 0; i < NUM_LEDS; i++) {
		if ( getPixelDirection(i) == GETTING_DARKER) {
			// This pixel is getting darker
			leds[i] = makeDarker(leds[i], fadeDownAmount);
		}
		else {
			// This pixel is getting brighter
			leds[i] = makeBrighter(leds[i], fadeUpAmount);
			// now check to see if we've maxed out the brightness
			if (leds[i].r == 255 || leds[i].g == 255 || leds[i].b == 255) {
				// if so, turn around and start getting darker
				setPixelDirection(i, GETTING_DARKER);
			}
		}
	}
}

 CRGB ColorTwinkles::makeBrighter( const CRGB& color, fract8 howMuchBrighter) {
	CRGB incrementalColor = color;
	incrementalColor.nscale8( howMuchBrighter);
	return color + incrementalColor;
 }

 CRGB ColorTwinkles::makeDarker( const CRGB& color, fract8 howMuchDarker) {
	CRGB newcolor = color;
	newcolor.nscale8( 255 - howMuchDarker);
	return newcolor;
 }



bool ColorTwinkles::getPixelDirection(uint16_t i) {
	return directionFlags[i];
}

void ColorTwinkles::setPixelDirection(uint16_t i, bool dir) {
	directionFlags[i] = dir;
}
