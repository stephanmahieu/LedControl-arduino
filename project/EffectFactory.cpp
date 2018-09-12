/*
 * EffectFactory.cpp
 *
 * Created: 31-12-2016 14:07:59
 *  Author: Stephan
 */
#include <FastLED.h>
#include "EffectFactory.h"

#include "effect\Effect.h"

#include "effect\Blank.h"
#include "effect\ColorTwinkles.h"
#include "effect\DutchFlag.h"
#include "effect\RainbowMarch.h"
#include "effect\SoftTwinkles.h"
#include "effect\Cylon.h"
#include "effect\Pride2015demo.h"
#include "effect\DiscoStrobe.h"
#include "effect\Gradient.h"
#include "effect\AntiAlias.h"
#include "effect\Fireworks.h"
#include "effect\RunningDot.h"
#include "effect\Ripple.h"

EffectFactory effectFactory;

EffectFactory::EffectFactory() {
}

Effect* EffectFactory::getEffect(int effectNumber, struct CRGB *leds) {
	switch (effectNumber) {
		case  0: return new Blank(leds);
		case  1: return new RainbowMarch(leds);
		case  2: return new SoftTwinkles(leds);
		case  3: return new ColorTwinkles(leds);
		case  4: return new DutchFlag(leds);
		case  5: return new Cylon(leds);
		case  6: return new Pride2015demo(leds);
		case  7: return new DiscoStrobe(leds);
		case  8: return new Gradient(leds);
		case  9: return new AntiAlias(leds);
		case 10: return new Fireworks(leds);
		case 11: return new RunningDot(leds);
		case 12: return new Ripple(leds);
	}
	return new RainbowMarch(leds);
}