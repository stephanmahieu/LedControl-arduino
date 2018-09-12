/*
 * Brightness.h
 *
 * Created: 28-12-2015 16:37:13
 *  Author: Stephan
 */ 


#ifndef BRIGHTNESS_H_
#define BRIGHTNESS_H_

// Analog pin 0 for an LDR
const int LDR_ANALOG = 0;

class Brightness {
	private:
		String brightnessLevel;
	
	public:
		Brightness();
		void setLevel(char* level);
		int getLevel();
		bool isAutomaticLevel();
};

extern Brightness brightness;

#endif /* BRIGHTNESS_H_ */