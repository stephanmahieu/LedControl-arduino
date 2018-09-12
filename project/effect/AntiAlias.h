/*
 * AntiAlias.h
 *
 * Created: 26-12-2016 16:41:05
 *  Author: Stephan
 */

// Anti-aliased light bar example
//   v1.0 is here http://pastebin.com/yAgKs0Ay
//   v1.1 by Mark Kriegsman <kriegsman@tr.org>, April 16, 2013
//   More of a toy than a side-by-side demo...
//   I tore out all the "Integer bar" code, leaving only the anti-aliased bar
//   Also made it slowly rotate through all the hues.

#ifndef ANTIALIAS_H_
#define ANTIALIAS_H_

#include "Effect.h"

class AntiAlias: public Effect {
	private:
	struct CRGB *leds;

	// Initialize variables for sequences
	const   uint8_t thisdelay = 10;  // A delay value for the sequence(s)

	int     F16pos = 0;   // position of the "fraction-based bar"
	int     F16delta = 1; // how many 16ths of a pixel to move the Fractional Bar
	uint16_t Fhue16 = 0;  // color for Fractional Bar
	int Width  = 4;       // width of each light bar, in whole pixels

	void drawFractionalBar( int pos16, int width, uint8_t hue);

	public:
	AntiAlias(struct CRGB *pLeds);
	char* name();
	void show();
};




#endif /* ANTIALIAS_H_ */