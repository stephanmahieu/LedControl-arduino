/*
 * Fireworks.cpp
 *
 * Created: 27-12-2016 16:45:52
 *  Author: Stephan
 */
#include <Arduino.h>
#include "..\LEDsetup.h"
#include "FastLED.h"
#include "Fireworks.h"

Fireworks::Fireworks(struct CRGB *pLeds) {
	leds = pLeds;

	currentPalette = PartyColors_p;
	//currentPalette = OceanColors_p;
	//currentPalette = CloudColors_p;
	//currentPalette = LavaColors_p;
	//currentPalette = ForestColors_p;

	for (int i = 0; i < MAX_ROCKETS; i++) {
		rocket[i].startTime = 0;
	}
}

char* Fireworks::name() {
	return "Fireworks";
}

void Fireworks::show() {
	// launch a new rocket every n secs
	EVERY_N_MILLISECONDS(LAUNCH_DELAY) {
		launch(random16(50,NUM_LEDS), random8(5,30), random8());
	}

	// handle all launched rockets
	runner();

	// dim whole strip for nice fade effect
	EVERY_N_MILLISECONDS(2) {
		for (int j=0; j<NUM_LEDS; j++) {
			leds[j].nscale8(250);
		}
	}

	FastLED.show();
}

// process the explosions
// over time a single explosion goes through states
// fly -> blast -> sparcle -> done
void Fireworks::runner() {
	for (int i=0; i<MAX_ROCKETS; i++) {
		if (rocket[i].startTime > 0) {
			int shellEvent = millis() - rocket[i].startTime;
			if (shellEvent < FLIGHT_DURATION) {
				fly(i);
			}
			else if (shellEvent < FLIGHT_DURATION + BLAST_DURATION) {
				blast(i);
			}
			else if (shellEvent < FLIGHT_DURATION + BLAST_DURATION + SPARCLE_DURATION) {
				sparcle(i);
			}
			else {
				done(i);
			}
		}
	}
}

// display an explosion at given coordinate
void Fireworks::launch(int pos, int size, int color) {
	rocket[rocketIndex].pos = pos;
	rocket[rocketIndex].size = size;
	rocket[rocketIndex].startTime = millis() + 1;
	rocket[rocketIndex].color = ColorFromPalette( currentPalette, color, 0xff, BLEND_MODE);
	rocketIndex++;
	if (rocketIndex == MAX_ROCKETS) {
		rocketIndex = 0;
	}
}

void Fireworks::fly(int index) {
	int flightAge = millis() - rocket[index].startTime;
	int flightPos = (float)flightAge / (float)FLIGHT_DURATION * rocket[index].pos;
	if ((flightPos >= 0) && (flightPos < NUM_LEDS)) {
		leds[flightPos] += CRGB(0x05,0x04,0x02);
	}
}

void Fireworks::blast(int index) {
	int blastAge = millis() - rocket[index].startTime - FLIGHT_DURATION;
	int blastSize = (float)blastAge / (float)BLAST_DURATION * (float) rocket[index].size;
	for (int i=0; i<blastSize*2; i++) {
		int blastPoint = rocket[index].pos - blastSize + i;
		if ((blastPoint >= 0) && (blastPoint < NUM_LEDS)) {
			leds[blastPoint] += rocket[index].color;
		}
	}
}

void Fireworks::sparcle(int index) {
	int sparcleAge = millis() - rocket[index].startTime - FLIGHT_DURATION - BLAST_DURATION;
	int sparcleTTL = SPARCLE_DURATION - sparcleAge;
	int sparcleProb = (float) sparcleTTL / (float) SPARCLE_DURATION * 100;

	if (random8(0, 101-sparcleProb) == 0) {
		int sparcleSize = (float)sparcleAge / (float)SPARCLE_DURATION * (float)rocket[index].size + (float)rocket[index].size;
		int sparclePix = random8(sparcleSize);
		int sparclePoint = rocket[index].pos-sparcleSize / 2 - sparclePix-sparcleAge / 50;
		if ((sparclePoint >= 0) && (sparclePoint < NUM_LEDS)) {
			leds[sparclePoint] += rocket[index].color;
		}
		sparclePoint = rocket[index].pos+sparcleSize/2+sparclePix-sparcleAge/50;
		if ((sparclePoint >= 0) && (sparclePoint < NUM_LEDS)) {
			leds[sparclePoint] += rocket[index].color;
		}
	}
}

void Fireworks::done(int index) {
	rocket[index].startTime = 0;
}