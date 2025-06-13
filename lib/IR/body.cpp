#include <body.h>
#include <Arduino.h>
#include "limits.h"
#include "config.h"

bodySetup::bodySetup(
    const uint16_t baudRate,
    const uint8_t red,
    const uint8_t green,
    const uint8_t btn
){

    // setting up the pin modes and other initializations
    this->baud= baudRate;
    this->ledRed= red;
    this->ledGreen= green;
    this->buttonSignals= btn;

}

void bodySetup::begin(){
    pinMode(this->ledRed, OUTPUT);
    pinMode(this->ledGreen, OUTPUT);
    pinMode(this->buttonSignals, INPUT_PULLUP);
}

uint8_t bodySetup::millisToSec(uint16_t data) const{
    // to convert millis to seconds
    // 16 unsigned bits means max of 65535 millis or ~65secs
    
    uint8_t seconds= data/1000;
    if (data > 0 && seconds == 0){
        // this indicates a small press thus needs to be representable
        seconds++;
    }
    return seconds;
}

void bodySetup::signalGreen(uint8_t duration) const{
    // this method will turn the green led on for the given seconds
    digitalWrite(LED_GREEN, HIGH);
    delay(duration*1000);
    digitalWrite(LED_GREEN, LOW);
}

void bodySetup::signalRed(uint8_t duration) const{
    // this method will turn on the red led for the given seconds
    digitalWrite(LED_RED, HIGH);
    delay(duration*1000);
    digitalWrite(LED_RED, LOW);
}

uint8_t bodySetup::checkButton() const{
    // returns the time in seconds for how long the button is pressed
    static bool wasPressed= false;     // indicating the press status of the button: default= false
    static unsigned long time= 0;      // to record time
    uint16_t pressDuration= 0;          // to return

    if(digitalRead(this->buttonSignals) == LOW && wasPressed == false){
        // if the button was never on and is newly pressed
        time= millis();
        wasPressed= true;
    }

    if(digitalRead(this->buttonSignals) == HIGH && wasPressed == true){
        // if the button was pressed and is recently put off

        if((millis() - time) > UINT16_MAX_){
            // handling the case of overflow
            pressDuration= UINT16_MAX_;
        } else{
            pressDuration= millis() - time;
        }

        time= 0;
        wasPressed= false;
    }

    // converting to seconds and returning
    return this->millisToSec(pressDuration);

}

bodySetup body;