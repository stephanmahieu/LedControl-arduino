/*
 * Ripple.h
 *
 * Created: 31-12-2016 15:49:15
 *  Author: Stephan
 */


#ifndef RIPPLE_H_
#define RIPPLE_H_

#include "Effect.h"


class Ripple: public Effect {
	private:
		struct CRGB *leds;

		const int thisdelay = 25;

		int color;
		int center = 0;
		int step = -1;
		int maxSteps = 16;
		float fadeRate = 0.8;
		int diff;

		//background color
		uint32_t currentBg = random(256);
		uint32_t nextBg = currentBg;

		void doRipple();
		int wrap(int step);

	public:
		Ripple(struct CRGB *pLeds);
		char* name();
		void show();
};




#endif /* RIPPLE_H_ */