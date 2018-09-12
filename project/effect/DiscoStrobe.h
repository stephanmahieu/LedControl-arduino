/*
 * DiscoStrobe.h
 *
 * Created: 18-12-2016 21:51:35
 *  Author: Stephan
 */


#ifndef DISCOSTROBE_H_
#define DISCOSTROBE_H_

#include "Effect.h"


class DiscoStrobe: public Effect {
	private:
	struct CRGB *leds;
	uint8_t thisdelay;
	uint8_t zoomBPM;

	TBlendType currentBlending;
	CRGBPalette16 gCurrentPalette;

	void doStrobe();
	void discoWorker(uint8_t dashperiod, uint8_t dashwidth, int8_t  dashmotionspeed, uint8_t stroberepeats,	uint8_t huedelta);
	void drawRainbowDashes(uint8_t startpos, uint16_t lastpos, uint8_t period, uint8_t width, uint8_t huestart, uint8_t huedelta, uint8_t saturation, uint8_t value);

	public:
	DiscoStrobe(struct CRGB *pLeds);
	char* name();
	void show();
};



#endif /* DISCOSTROBE_H_ */