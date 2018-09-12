/*
 * Blank.h
 *
 * Created: 01-01-2016 11:58:27
 *  Author: Stephan
 */ 


#ifndef BLANK_H_
#define BLANK_H_

#include "Effect.h"


class Blank: public Effect {
	private:
		struct CRGB *leds;
		
	public:
		Blank(struct CRGB *pLeds);
		char* name();
		void show();
};


#endif /* BLANK_H_ */