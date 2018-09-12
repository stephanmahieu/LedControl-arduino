/*
 * Gradient.h
 *
 * Created: 18-12-2016 22:57:18
 *  Author: Stephan
 */ 


#ifndef GRADIENT_H_
#define GRADIENT_H_

#include "Effect.h"

class Gradient: public Effect {
	private:
	struct CRGB *leds;
	
	void blendme();
	
	public:
	Gradient(struct CRGB *pLeds);
	char* name();
	void show();
};

#endif /* GRADIENT_H_ */