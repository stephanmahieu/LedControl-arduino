/*
 * DutchFlag.h
 *
 * Created: 01-01-2016 12:18:21
 *  Author: Stephan
 */


#ifndef DUTCHFLAG_H_
#define DUTCHFLAG_H_

#include "Effect.h"

// Set up a static color palette stored in PROGMEM (flash),
// which is almost always more plentiful than RAM.
// A static PROGMEM palette like this takes up 64 bytes of flash.
const TProgmemPalette16 dutchFlagPalette_p PROGMEM = {
	CRGB::Blue,
	CRGB::Blue,
	CRGB::Gray,
	CRGB::Gray,
	CRGB::Red,
	CRGB::Red,

	CRGB::Black,
	CRGB::DarkOrange,
	CRGB::Black,

	CRGB::Blue,
	CRGB::Blue,
	CRGB::Gray,
	CRGB::Gray,
	CRGB::Red,
	CRGB::Red,
	CRGB::Black
};


class DutchFlag: public Effect {
	private:
		struct CRGB *leds;

		CRGBPalette16 currentPalette;
		TBlendType currentBlending;
		const int thisdelay = 20;

		void FillLEDsFromPaletteColors(struct CRGB *leds, uint8_t colorIndex);

	public:
		DutchFlag(struct CRGB *pLeds);
		char* name();
		void show();
};


#endif /* DUTCHFLAG_H_ */