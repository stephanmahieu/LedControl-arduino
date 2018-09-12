/*
 * ColorTwinkles.h
 *
 * Created: 01-01-2016 23:24:53
 *  Author: Stephan
 */


#ifndef COLORTWINKLES_H_
#define COLORTWINKLES_H_

#include "..\LEDsetup.h"
#include "Effect.h"


class ColorTwinkles: public Effect {
	private:
		struct CRGB *leds;
		uint8_t thisdelay;
		const int STARTING_BRIGHTNESS = 64;
		const int FADE_IN_SPEED       = 32;
		const int FADE_OUT_SPEED      = 20;
		const int DENSITY             = 255;
		enum {GETTING_DARKER = 0, GETTING_BRIGHTER = 1};

		uint8_t directionFlags[NUM_LEDS];
		CRGBPalette16 palette;

		void twinkle();
		void brightenOrDarkenEachPixel(fract8 fadeUpAmount, fract8 fadeDownAmount);
		CRGB makeBrighter(const CRGB& color, fract8 howMuchBrighter);
		CRGB makeDarker(const CRGB& color, fract8 howMuchDarker);
		bool getPixelDirection(uint16_t i);
		void setPixelDirection(uint16_t i, bool dir);

	public:
		ColorTwinkles(struct CRGB *pLeds);
		char* name();
		void show();
};


#endif /* COLORTWINKLES_H_ */