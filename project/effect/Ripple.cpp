/*
 * Ripple.cpp
 *
 * Created: 31-12-2016 15:49:01
 *  Author: Stephan
 */
#include <Arduino.h>
#include "..\LEDsetup.h"
#include "FastLED.h"
#include "Ripple.h"


Ripple::Ripple(struct CRGB *pLeds) {
	leds = pLeds;
}

char* Ripple::name() {
	return "Ripple";
}

void Ripple::show() {
	EVERY_N_MILLISECONDS(thisdelay) {
		doRipple();
		FastLED.show();
	}
}


void Ripple::doRipple() {

	if (currentBg == nextBg) {
		nextBg = random(256);
	}
	else if (nextBg > currentBg) {
		currentBg++;
	}
	else {
		currentBg--;
	}
	for(uint16_t l = 0; l < NUM_LEDS; l++) {
		leds[l] = CHSV(currentBg, 255, 50);
	}

	if (step == -1) {
		center = random(NUM_LEDS);
		color = random(256);
		step = 0;
	}

	if (step == 0) {
		leds[center] = CHSV(color, 255, 255);
		step ++;
	}
	else {
		if (step < maxSteps) {
			//Serial.println(pow(fadeRate,step));

			leds[wrap(center + step)] = CHSV(color, 255, pow(fadeRate, step)*255);
			leds[wrap(center - step)] = CHSV(color, 255, pow(fadeRate, step)*255);
			if (step > 3) {
				leds[wrap(center + step - 3)] = CHSV(color, 255, pow(fadeRate, step - 2)*255);
				leds[wrap(center - step + 3)] = CHSV(color, 255, pow(fadeRate, step - 2)*255);
			}
			step ++;
		}
		else {
			step = -1;
		}
	}
}


int Ripple::wrap(int step) {
	if(step < 0) return NUM_LEDS + step;
	if(step > NUM_LEDS - 1) return step - NUM_LEDS;
	return step;
}
