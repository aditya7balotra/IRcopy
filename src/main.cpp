#include <Arduino.h>
#include "body.h"
#include <config.h>
#include "ir.h"


uint8_t time;

void setup(){
    Serial.begin(DEFAULT_BAUD_RATE);
    body.begin();
    i.begin();
}

void loop(){
    // checking the button
    time= body.checkButton();

    if (time == 1){
        // send signal
        i.sendSignals();
    } else if (time >= DEFAULT_LONG_PRESS_DURATION){
        // indicates reset
        Serial.println("Reseting...");
        i.resetBuff();
        body.signalRed();
    }

    // receive signals
    i.getSet();
}