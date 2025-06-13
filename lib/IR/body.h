// this file rests with the body level functioning(those other than IR) of the project
// like works related to button, leds(red, green and blue) etc.

#ifndef BODY_H
#define BODY_H

#include "config.h"
#include <Arduino.h>

class bodySetup{
    private:
        uint8_t ledGreen, ledRed, buttonSignals;
        uint16_t baud;
        uint8_t millisToSec(uint16_t data) const;          // to convert milliseconds to seconds(0s - ~65s)

    public:
        bodySetup(
                const uint16_t baudRate= DEFAULT_BAUD_RATE,
                const uint8_t red= LED_RED,
                const uint8_t green= LED_GREEN,
                const uint8_t btn= BUTTON_SIGNALS
        );                 // some initializations

        void begin();

        
        void signalRed(uint8_t duration= DEFAULT_LED_SIGNAL_DURATION) const;       // to signal the red led

        void signalGreen(uint8_t duration= DEFAULT_LED_SIGNAL_DURATION) const;     // to signal the green led

        uint8_t checkButton() const;                     // check button signals
};  

extern bodySetup body;

#endif