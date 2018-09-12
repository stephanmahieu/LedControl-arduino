/*
 * Effect.h
 *
 * Created: 01-01-2016 11:04:08
 *  Author: Stephan
 */ 


#ifndef EFFECT_H_
#define EFFECT_H_

/* Abstract base class for Effects. */
class Effect {

	public:
		virtual void show() = 0;
		virtual char* name() = 0;
};


#endif /* EFFECT_H_ */