/*
	LedControl
	By: Stephan Mahieu
	Date: Dec, 2015
	Led control using the FastLED library.
*/

#include <Arduino.h>

#include <avr/wdt.h>  // Watchdog timer for resetting the Arduino

#include <FastLED.h>
#include <aJSON.h>
#include <MemoryFree.h>

#include "USBSerial.h"
#include "LEDsetup.h"
#include "Brightness.h"

#include "EffectFactory.h"

/*
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
#include "effect\RunningDot.h"*/

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif


void setup();
void loop ();

void enableProcessing();
void disableProcessing();
void processMessage(char *msg);
aJsonStream serial_stream(&Serial);

void processCmd(char *msg, aJsonObject* command);
void processDebug(char *msg, aJsonObject* command);
void outputStatus();

void processCmdBrightness(char *msg, aJsonObject* command);
void processCmdEffect(char *msg, aJsonObject* command);

void outputLog();

bool isValidJson(char *msg);

// declare reset function @ address 0
void resetArduino();

// Initialize global variables.
struct CRGB leds[NUM_LEDS];  // Initialize the size of our LED array.
bool showDebugInfo = true;

// Initialize the current effect to start with
Effect *currentEffect = effectFactory.getEffect(6, leds);


void setup() {
	Serial.begin(115200);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only.
	}

	usbSerial.initSerial(enableProcessing, disableProcessing, processMessage);

	// built in led off
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS); // Initialize our LED array.
	FastLED.setBrightness(128);                                  // Initial brightness.
	set_max_power_in_volts_and_milliamps(5, 9000);               // FastLED Power management set at 45 Watt (5V, 9000mA).
}


void loop () {
	if (!usbSerial.isBusy()) {
		currentEffect->show();
		FastLED.setBrightness(brightness.getLevel());
	}

	usbSerial.checkInput();
}




void enableProcessing() {
	//LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);
}

void disableProcessing() {
	//LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, 0);
	//sei(); // enable global interrupts
}

/* Process JSON message, must start with {"type":"CMD", ...} */
void processMessage(char *msg) {
	//Serial.print("processMessage: [");
	//Serial.print(msg);
	//Serial.println("]");
	if (strcmp(msg, "\"RESET\"") == 0) {
		resetArduino();
	}

	if (!isValidJson(msg)) {
		usbSerial.reset();
		return;
	}

	aJsonObject* root = aJson.parse(msg);
	if (root == NULL) {
		Serial.print("ERR: not JSON data! ");
		Serial.print(strlen(msg));
		Serial.print(":[");
		Serial.print(msg);
		Serial.println("]");
		usbSerial.reset();
	}
	else {
		aJsonObject* type = aJson.getObjectItem(root, "type");
		if (type == NULL) {
			Serial.print("ERR: no 'type' found in JSON object: ");
			Serial.println(msg);
		}
		else {
			char* typeValue = type->valuestring;

			if (strcmp(typeValue, "CMD") == 0) {
				aJsonObject* command = aJson.getObjectItem(root, "command");
				processCmd(msg, command);
			}
			else if (strcmp(typeValue, "DEBUG") == 0) {
				aJsonObject* debug = aJson.getObjectItem(root, "debug");
				processDebug(msg, debug);
			}
			else if (strcmp(typeValue, "STATUS") == 0) {
				outputStatus();
			}
			else {
				Serial.print("ERR: unknown 'type' found in JSON object: type identified as [");
				Serial.print(typeValue);
				Serial.print("] ");
				Serial.println(msg);
			}
		}
		usbSerial.reset();
		aJson.deleteItem(root);
	}
}

/* Process JSON message like: {"type":"CMD","command":{"name":"brightness","param":["255"]}} */
void processCmd(char *msg, aJsonObject* command) {
	if (command == NULL) {
		Serial.print("ERR: command object not provided for CMD type in JSON object: ");
		Serial.println(msg);
	}

	aJsonObject* name = aJson.getObjectItem(command, "name");
	char* nameValue = name->valuestring;

	if (strcmp(nameValue, "brightness") == 0) {
		processCmdBrightness(msg, command);
		return;
	}
	if (strcmp(nameValue, "effect") == 0) {
		processCmdEffect(msg, command);
		return;
	}

	Serial.print("echo: found command: ");
	Serial.println(nameValue);

	aJsonObject* paramArray = aJson.getObjectItem(command, "param");
	if (paramArray) {
		//unsigned char size = aJson.getArraySize(paramArray);
		aJsonObject *child = paramArray->child;
		while (child) {
			char* paramValue = child->valuestring;

			Serial.print("      parameter: ");
			Serial.println(paramValue);

			child = child->next;
		}
	}
}

/* Process  JSON message like: {"type":"DEBUG", "debug":{"debugOn":true}} */
void processDebug(char *msg, aJsonObject* debug) {
	if (debug == NULL) {
		Serial.print("ERR: debug object not provided for DEBUG type in JSON object: ");
		Serial.println(msg);
	}

	aJsonObject* debugOn = aJson.getObjectItem(debug, "debugOn");
	if (debugOn) {
		showDebugInfo = debugOn->valuebool;

		Serial.print("echo: showDebugInfo set to: ");
		Serial.println(showDebugInfo);
	}

}

void processCmdBrightness(char *msg, aJsonObject* command) {
	aJsonObject *paramArray = aJson.getObjectItem(command, "param");
	char* level = paramArray->child->valuestring;

	brightness.setLevel(level);

	Serial.print("echo: setting brightness to: ");
	Serial.println(level);
}

void processCmdEffect(char *msg, aJsonObject* command) {
	aJsonObject *paramArray = aJson.getObjectItem(command, "param");
	char* effect = paramArray->child->valuestring;

	// reset leds to all black first
	//FastLED.clear();
	fill_solid(leds, NUM_LEDS, CRGB::Black);
	FastLED.show();

	// select the new effect
	delete currentEffect;
	currentEffect = effectFactory.getEffect(atoi(effect), leds);

	Serial.print("echo: setting effect to: ");
	Serial.println(currentEffect->name());
}

void outputStatus() {
	Serial.println("echo: received status request");

	aJsonObject *msg, *status;

	msg = aJson.createObject();
	aJson.addItemToObject(msg, "type", aJson.createItem("STATUS"));
	aJson.addItemToObject(msg, "status", status = aJson.createObject());
	aJson.addStringToObject(status,  "effect",         currentEffect->name());
	aJson.addNumberToObject(status,  "brightness",     brightness.getLevel());
	aJson.addBooleanToObject(status, "autoBrightness", brightness.isAutomaticLevel());
	aJson.addNumberToObject(status,  "noOfLeds",       (int)NUM_LEDS);
	aJson.addNumberToObject(status,  "fps",            (int)FastLED.getFPS());
	aJson.addNumberToObject(status,  "freeMemory",     (int)freeMemory());
	aJson.addBooleanToObject(status, "debugOn",        showDebugInfo);

	aJson.print(msg, &serial_stream);
	Serial.println();

	aJson.deleteItem(msg);
}

void outputLog() {
	aJsonObject *msg, *loggingInfo;

	msg = aJson.createObject();
	aJson.addItemToObject(msg, "type", aJson.createItem("LOG"));
	aJson.addItemToObject(msg, "loggingInfo", loggingInfo = aJson.createObject());
	aJson.addItemToObject(loggingInfo, "info", aJson.createItem("And perhaps we can use a very long line of text in output as well?"));

	aJson.print(msg, &serial_stream);
	Serial.println(); /* Add newline. */

	aJson.deleteItem(msg);
}

bool isValidJson(char *msg) {
	if (strlen(msg) < 3) {
		return false;
	}

	// matching opening and closing braces?
	int countBraces = 0;
	for (int i=0; i<strlen(msg); i++) {
		if (msg[i] == '{') {
			countBraces++;
		}
		else if (msg[i] == '}') {
			countBraces--;
		}
	}
	return (countBraces == 0);
}

void resetArduino() {
	cli();                 // Clear interrupts
	wdt_enable(WDTO_15MS); // Set Watchdog to 15ms
	while(1);              // Wait for the reset to happen
}