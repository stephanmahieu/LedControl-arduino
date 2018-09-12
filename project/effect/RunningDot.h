/*
 * RunningDot.h
 *
 * Created: 30-12-2016 13:53:58
 *  Author: Stephan
 */


#ifndef RUNNINGDOT_H_
#define RUNNINGDOT_H_

#include "Effect.h"

class RunningDot: public Effect {
	private:
		struct CRGB *leds;
		uint16_t whiteLedPos = 0;

	public:
		RunningDot(struct CRGB *pLeds);
		char* name();
		void show();
};



#endif /* RUNNINGDOT_H_ */