/*
 * SoftTwinkles.h
 *
 * Created: 31-12-2015 16:33:44
 *  Author: Stephan
 */ 


#ifndef SOFTTWINKLES_H_
#define SOFTTWINKLES_H_

#include "Effect.h"


class SoftTwinkles: public Effect {
	private:
		const int DENSITY = 80;
		const uint8_t thisdelay = 20;

		struct CRGB *leds;
		
		void twinkle();
		
		// For this animation to work, the Red component of this
		// color MUST be nonzero, AND must be an EVEN number.
		//CRGB twinkleColor(8,7,1);	
		
	public:
		SoftTwinkles(struct CRGB *pLeds);
		char* name();
		void show();
};


#endif /* SOFTTWINKLES_H_ */