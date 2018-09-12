/*
 * Fireworks.h
 *
 * Created: 27-12-2016 16:46:10
 *  Author: Stephan
 */


#ifndef FIREWORKS_H_
#define FIREWORKS_H_


#include "Effect.h"

class Fireworks: public Effect {
	private:
		struct CRGB *leds;

		// Initialize variables for sequences
		static const int MAX_ROCKETS      =   10;
		static const int FLIGHT_DURATION  = 3000; // durations for explosions: flight time
		static const int BLAST_DURATION   =  200; // explosion time
		static const int SPARCLE_DURATION = 3000; // sparcle time
		static const int LAUNCH_DELAY     = 2000; // time between each launch

		static const TBlendType BLEND_MODE = LINEARBLEND; // default blending mode

		CRGBPalette16 currentPalette; // currently running color palette

		int rocketIndex = 0; // keeping track of launched rockets

		typedef struct {
			int pos;
			int size;
			long startTime;
			CRGB color;
		} rocket_s;
		rocket_s rocket[MAX_ROCKETS];

		void launch(int pos, int size, int color);
		void fly(int index);
		void blast(int index);
		void sparcle(int index);
		void done(int index);
		void runner();

	public:
		Fireworks(struct CRGB *pLeds);
		char* name();
		void show();
};





#endif /* FIREWORKS_H_ */