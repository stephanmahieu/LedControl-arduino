/*
 * USBSerial.h
 *
 * Created: 31-12-2015 09:12:11
 *  Author: Stephan
 */


#ifndef USBSERIAL_H_
#define USBSERIAL_H_

#define MAX_SERIAL_MSG_SIZE 2048

typedef void (*enableProcessingType)();
typedef void (*disableProcessingType)();
typedef void (*processMessageType)(char *message);

static enableProcessingType _enableProcessing;
static disableProcessingType _disableProcessing;
static processMessageType _processMessage;

static char serialInputString[MAX_SERIAL_MSG_SIZE+2];
static uint16_t counter;
static bool isCommunicating;


class USBSerial {
	private:

	public:
		USBSerial();
		static void initSerial(
			enableProcessingType enableProcessing_callback,
			disableProcessingType disableProcessing_callback,
			processMessageType processMessage_callback);
		static void checkInput();
		static bool isBusy();
		static void reset();
};

extern USBSerial usbSerial;


#endif /* USBSERIAL_H_ */