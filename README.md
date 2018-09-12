# LedControl-arduino

Control my ledstrip using the FastLED library.

The program listens on the serial port, using the java webclient you can change the lighting effect.

I started this project december 2015. A new ledstrip should replace the current lightstrip (which has a few broken lightbulbs)
that was on the house when we bought it.

Current status: _**Work In Progress**_

Everything is functional. I can run the java webclient on a Raspberry Pi and change the lighting effect from my phone or tablet
_(the webinterface on the RasPi is accessible on the home network via WiFi)_. 

Still to do:
* Mount the ledstrip to the house
* Using 2 or 3 power adapters I have to add extra cables along the ledstrip to power each individual strip
* Make a box for the poweradapters and the Raspberry Pi
* Enhance the webclient (automatic mode to change effects on special dates like christmas or halloween).
* Enhance the arduino module
* Use a smaller Arduino? (using the Mega is probably overkill)

The main program/starting point: **LedControl.cpp** 


## My ledstrips

**LEDSTRIP WS2801:**

    #define LED_TYPE    WS2801
    #define COLOR_ORDER RBG
    #define NUM_LEDS    160

**LEDSTRIP WS2812B:**

    #define LED_TYPE    WS2812B
    #define LED_DT      6    
    #define COLOR_ORDER GRB
    #define NUM_LEDS    315

SPI is an acronym for “Serial Peripheral Interface”.  
It is a synchronous serial data bus – data can travel in both directions at the same time, as opposed to (for example) the I2C bus that cannot do so.  
To allow synchronous data transmission, the SPI bus uses four wires. They are called:

    MOSI – Master-out, Slave-in. This line carries data from our Arduino to the SPI-controlled device(s);
    MISO – Master-in, Slave out. This line carries data from the SPI-controlled device(s) back to the Arduino;
    SS   – Slave-select. This line tells the device on the bus we wish to communicate with it. Each SPI device needs a unique SS line back to the Arduino;
    SCK  – Serial clock.

**Arduino Mega (2560):**

    MISO is 50, 
    MOSI is 51,
    SCK  is 52,
    SS   is 53

**Arduino Mega SPI 6-pins connector:**

    MISO (50) - 1  X  X  2 - Vcc
    SCK  (52) - 3  X  X  4 - MOSI (51)
    Reset     - 5  X  X  6 - GND

**Wiring WS2812B:**

    GND   Zwart - 
    V+    Rood  -
    Data  Groen - 6 Digital pin

**Wiring WS2801:**

    GND   Blauw - 
    V+    Zwart -
    Clock Groen - 52 SCK
    Data  Rood  - 51 MOSI
    
## Links
* https://www.arduino.cc/en/Reference/HomePage  
* http://tronixstuff.com/2011/05/13/tutorial-arduino-and-the-spi-bus/  
* https://www.arduino.cc/en/Hacking/PinMapping2560  
* https://www.arduino.cc/en/uploads/Hacking/PinMap2560big.png  

## Atmel Studio

External tool: Send to atmega2560 COM5:

    command  : C:\_winapps\develop\arduino-1.8.0\hardware\tools\avr\bin\avrdude.exe
    arguments: -CC:\_winapps\develop\arduino-1.8.0/hardware/tools/avr/etc/avrdude.conf -v -v -patmega2560 -cwiring -PCOM5 -b115200 -D -Uflash:w:"$(BinDir)\$(TargetName).hex":i
    
  
External tool: Port monitor COM5:

    command  : C:\_winapps\tools\RealTerm\realterm.exe
    arguments: baud=115200 port=5 data=8N1 tab=Send half cr,cr lf,lf  colors=RLYRYK


To include FastLED libs:
* First backup LedControl.cppproj !!! (C:\Users\Stephan\Documents\Atmel Studio\7.0\LedControl\LedControl\)
* IDE: delete all libs from solution explorer: include\FastLED\*.*
* delete all files from C:\Users\Stephan\Documents\Atmel Studio\7.0\LedControl\LedControl\include\FastLED
* add new FastLED files from external source including lib8tion and platforms subdirectories
* IDE: add existing items (only choose *.cpp and *.h files from FastLED root directory)
* IDE: Project -> LedControl properties (Alt-F7):
  * Choose ToolChain -> AVR/GNU C Compiler -> Directories
    * Add Item: browse/select path (Relative Path = true)
	* Save (Ctrl+S)
	* idem for ToolChain -> AVR/GNU C++ Compiler -> Directories
* Done?