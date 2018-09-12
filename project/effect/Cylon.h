/*
 * Cylon.h
 *
 * Created: 18-12-2016 15:56:27
 *  Author: Stephan
 */


#ifndef CYLON_H_
#define CYLON_H_

#include "Effect.h"

class Cylon: public Effect {
	private:
	struct CRGB *leds;

	const int thisdelay = 10;
	uint8_t hue = 0;
	int direction = 1;
	int index = 0;

	void fadeall();

	public:
	Cylon(struct CRGB *pLeds);
	char* name();
	void show();
};

#endif /* CYLON_H_ */