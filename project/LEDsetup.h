/*
 * LEDsetup.h
 *
 * Created: 29-12-2015 13:22:50
 *  Author: Stephan
 */ 


#ifndef LEDSETUP_H_
#define LEDSETUP_H_

// Fixed definitions, cannot be changed dynamically.
#define LED_TYPE WS2812B               // The LED strip I am using
#define COLOR_ORDER GRB                // WS2812B is using GRB
#define LED_DT 6                       // Data pin to connect to the strip.
// #define LED_CK 11                   // WS2812B does not need a separate clock pin

//#define NUM_LEDS (5 * 30) + 15       // Number of LED's
#define NUM_LEDS 315                   // Number of LED's (5 * 30) + 15 + 150



#endif /* LEDSETUP_H_ */