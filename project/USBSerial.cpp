/*
 * USBSerial.cpp
 *
 * Created: 31-12-2015 09:12:30
 *  Author: Stephan
 */
#include <Arduino.h>
#include "USBSerial.h"

USBSerial usbSerial;


USBSerial::USBSerial() {
}

void USBSerial::initSerial(
		enableProcessingType enableProcessing_callback,
		disableProcessingType disableProcessing_callback,
		processMessageType processMessage_callback) {

	_enableProcessing = enableProcessing_callback;
	_disableProcessing = disableProcessing_callback;
	_processMessage = processMessage_callback;

	counter = 0;
	isCommunicating = false;
}

bool USBSerial::isBusy() {
	return isCommunicating;
}

void USBSerial::checkInput() {
//	static uint8_t counter = 0;
//	static char serialInputString[MAX_SERIAL_MSG_SIZE+2];

	if (Serial.available() > 0)	{

		char inByte = Serial.read();

		if (counter > MAX_SERIAL_MSG_SIZE) {
			// Buffer overflow
			counter = 0;
			isCommunicating = false;
		}
		else {

			if (inByte == 1) {
				// SOH received, request for reliable communication time slot

				// disable LED processing
				isCommunicating = true;
				_disableProcessing();
			}
			else {
				// Add received char to input buffer
				serialInputString[counter++] = inByte;
			}

			if (inByte == 10) {
				// End of line received, process data

				// Replace newline with end of string character
				serialInputString[--counter] = '\0';

				// Process the received command
				if (counter > 0) {
					//Serial.print("echo: ");
					//Serial.println(serialInputString);

					_processMessage(serialInputString);
				}

				// Reset counter value
				counter = 0;

				// re-enable LED processing
				_enableProcessing();
				isCommunicating = false;
			}
		}

	}
}

void USBSerial::reset() {
	while (Serial.available() > 0)	{
		Serial.read();
	}
	counter = 0;
	isCommunicating = false;
	_enableProcessing();
}