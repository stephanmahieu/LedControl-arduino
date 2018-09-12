/*
 * Brightness.cpp
 *
 * Created: 28-12-2015 16:36:46
 *  Author: Stephan
 */
#include <Arduino.h>
#include "Brightness.h"


Brightness brightness;

/* Constructor */
Brightness::Brightness() {
	brightnessLevel = "auto";
}


void Brightness::setLevel(char* level) {
	if (strcmp(level, "auto") == 0) {
		brightnessLevel = "auto";
	}
	else {
		brightnessLevel = String(level);
	}
}

bool Brightness::isAutomaticLevel() {
	return brightnessLevel.equals("auto");
}

int Brightness::getLevel() {
	int brightness;

	if (brightnessLevel == "auto") {
		// get the ambient brightness from the LDR
		//  10 = ambient very bright
		// 530 = ambient very dark (max 900)
		brightness = analogRead(LDR_ANALOG);

		// scale to 0 - 255
		brightness = (brightness - 10.0) * 255.0 / 400.0;
		if (brightness > 255) {
			brightness = 255;
		}

		// led brightness is inverse of ambient brightness
		brightness = 255 - brightness;

		// led should never be off (minimum brightness 5)
		if (brightness <= 5) {
			brightness = 5;
		}
		else if (brightness > 255) {
			brightness = 255;
		}

		//Serial.println(brightness, DEC);
	}
	else {
		brightness = brightnessLevel.toInt();
	}

	return brightness;
}
