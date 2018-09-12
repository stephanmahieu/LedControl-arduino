/*
 * Pride2015demo.h
 *
 * Created: 18-12-2016 21:34:04
 *  Author: Stephan
 */ 


#ifndef PRIDE2015DEMO_H_
#define PRIDE2015DEMO_H_

#include "Effect.h"

class Pride2015demo: public Effect {
	private:
	struct CRGB *leds;
	void pride();
	
	public:
	Pride2015demo(struct CRGB *pLeds);
	char* name();
	void show();
};


#endif /* PRIDE2015DEMO_H_ */