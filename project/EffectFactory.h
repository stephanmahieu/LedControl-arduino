/*
 * EffectFactory.h
 *
 * Created: 31-12-2016 14:07:44
 *  Author: Stephan
 */


#ifndef EFFECTFACTORY_H_
#define EFFECTFACTORY_H_

#include "effect\Effect.h"


class EffectFactory {
	private:

	public:
		EffectFactory();
		static Effect* getEffect(int effectNumber, struct CRGB *leds);
};

extern EffectFactory effectFactory;


#endif /* EFFECTFACTORY_H_ */