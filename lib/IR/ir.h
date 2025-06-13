// this file handles the IR working of the project

#ifndef IR_H
#define IR_H

#include <config.h>
#include "body.h"
#include <Arduino.h>

class ir{
    private:
        bodySetup* irBody;
        uint8_t recvPin, sendPin;           // send and receive pins
        uint16_t buffers[2][RECV_SINGALS_BUFFER_SIZE] = {};    // buffer storing received signals, defautl value is 0
        bool bufferStatus[2]= {false, false};       // represents the status of both buffers: true: filled false: vacant
        uint8_t sendStatus= 0;                      // max valid value can be lenght of total buffers - 1, work as index to keep track of which signal to send
        uint16_t bufferLen[2]= {};                  // stores the rawlen of each corresponding buffer in buffers variable
        void tickToMs(unsigned int* rawBufferPtr, int size);   // to convert ticks data form rawbuf[] to microseconds so to send it using .sendRaw()


    public:
        ir(bodySetup* irbody, uint8_t rcvpin= IR_RECV, uint8_t sndPin= LED_IR);    // basic initialization
        void begin();
        void getSet();         // to receive signal and set it if any buffer index is vacant
        void resetBuff();                     // to resest the buffer storage
        void sendSignals();                   // will send ir signals from the buffer as per the sendStatus index variable
};

extern ir i;

#endif