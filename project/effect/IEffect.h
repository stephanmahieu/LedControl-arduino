/*
 * IEffect.h
 *
 * Created: 01-01-2016 10:52:37
 *  Author: Stephan
 */ 


#ifndef IEFFECT_H_
#define IEFFECT_H_

class IEffect {

	public:
		virtual ~IEffect() {}
		virtual void show(struct CRGB *leds) = 0;
};


#endif /* IEFFECT_H_ */