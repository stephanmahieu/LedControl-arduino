/*
 * RainbowMarch.h
 *
 * Created: 29-12-2015 13:05:30
 *  Author: Stephan
 */


#ifndef RAINBOWMARCH_H_
#define RAINBOWMARCH_H_

#include "Effect.h"

class RainbowMarch: public Effect {
	private:
		struct CRGB *leds;
		
		// Initialize variables for sequences
		const uint8_t thisdelay = 5;  // A delay value for the sequence(s)
		const uint8_t deltahue = 10;  // Hue change between pixels.
		uint8_t thishue = 0;          // Starting hue value.
	
	public:
		RainbowMarch(struct CRGB *pLeds);
		char* name();
		void show();
};


#endif /* RAINBOWMARCH_H_ */