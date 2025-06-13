#include "ir.h"
#include <Arduino.h>
#include <config.h>
#include <limits.h>
#include <IRremote.h>
#include "body.h"

ir::ir(bodySetup* irbody, uint8_t rcvPin, uint8_t sndPin){
    // basic initializations
    this->irBody= irbody;
    this->recvPin= rcvPin;
    this->sendPin= sndPin;
}

void ir::begin(){
    IrReceiver.begin(this->recvPin, ENABLE_LED_FEEDBACK);
    IrSender.begin(this->sendPin);
}


void ir::getSet(){
    // this method deals with working of receiving the signals
    // plus saving them to the buffer after processing if space is avaibale

    if (IrReceiver.decode()){
        
        if ((IrReceiver.decodedIRData.rawDataPtr->rawlen) > ACCEPT_RAW_SIGNAL_MIN_LENGTH){
            // hoping to be a valid signal
            unsigned int* rawData= &IrReceiver.decodedIRData.rawDataPtr->rawbuf[1];

            // filtering the rawData
            this->tickToMs(rawData, IrReceiver.decodedIRData.rawDataPtr->rawlen - 1);

            // setting up the index of the buffer: where to store the signal
            uint8_t indBuff;
            // check if the signal should be stored or not
            if (this->bufferStatus[0] && this->bufferStatus[1]){
                // if both the status are true: ie both the buffers are full
                IrReceiver.resume();
                Serial.println("buffer reasons");
                return;

            } else{
                // if either or both is false
                if (this->bufferStatus[0] == false){
                    indBuff= 0;
                } else{
                    indBuff= 1;
                }
            }


            for(int i= 0; i< (IrReceiver.decodedIRData.rawDataPtr->rawlen - 1); i++){
                // coping
                this->buffers[indBuff][i]= *(rawData + i);
            }
            // updating the bufferLen
            this->bufferLen[indBuff]= IrReceiver.decodedIRData.rawDataPtr->rawlen-1;

            // updating the status
            this->bufferStatus[indBuff]= true;

            // signaling
            this->irBody->signalGreen();
        }
        IrReceiver.resume();
    }
}

void ir::resetBuff(){
    // resetting
    memset(this->buffers, BUFFER_DEFALUT_VALUE, sizeof(this->buffers));
    this->bufferStatus[0]= false;
    this->bufferStatus[1]= false;
    this->sendStatus= 0;
}

void ir::sendSignals(){
    // this method will be sending alternative ir signal if available
    if (this->bufferStatus[this->sendStatus]){
        // if proper signal is available
        
        // sending the signal
        IrSender.sendRaw(this->buffers[this->sendStatus], this->bufferLen[this->sendStatus], FREQ);

        // updating the sendStatus
        switch (this->sendStatus){
            case 0:
                this->sendStatus++;
                break;
            case 1:
                this->sendStatus= 0;
                break;
        }

        // signaling
        this->irBody->signalGreen();

    } else{
        // signaling red to indicate empty buffer
        this->irBody->signalRed();
    }
}


void ir::tickToMs(unsigned int* rawBufferPtr, int size){
    // this method will interpret the raw signals and filter them so to be able to send valid signals
    // convert ticks to microseconds: x50
    for (int i= 0; i< size; i++){
        *(rawBufferPtr + i)= *(rawBufferPtr + i) * 50;
    }

}


ir i(&body);
