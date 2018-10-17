
/*
  https://learn.adafruit.com/using-an-infrared-library/hardware-needed
  #define UNKNOWN 0
  #define NEC 1
  #define SONY 2
  #define RC5 3
  #define RC6 4
  #define PANASONIC_OLD 5
  #define JVC 6
  #define NECX 7
  #define SAMSUNG36 8
  #define GICABLE 9
  #define DIRECTV 10
  #define RCMM 11
*/


// recibir
#include "IRLibAll.h"
//Create a receiver object to listen on pin 2
IRrecvPCI myReceiver(2);
//Create a decoder object
IRdecode myDecoder;


// enviar
#include <IRLibSendBase.h> 
#include <IRLib_P01_NEC.h>
#include <IRLib_P02_Sony.h>
#include <IRLibCombo.h>    
// enviar por pin 3
IRsend mySender;


void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Every time you press a key is a serial monitor we will send."));
  Serial.println(F("Ready to receive IR signals"));
}

void loop() {

  if (Serial.read() != -1) {
    // mySender.send(SONY, 0xa8bca, 20); //Sony DVD power A8BCA, 20 bits
    // mySender.send(NEC,0x61a0f00f,0);//NEC TV power button=0x61a0f00f
    mySender.send(NEC, 0xff02fd, 0); // mando keyes ok
    Serial.println(F("Sent signal."));
  }



  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    myDecoder.dumpResults(true);  //Now print results. Use false for less detail

    if (myDecoder.protocolNum == NEC) {
      switch (myDecoder.value) {
        case 0xff02fd:  //Ok
          Serial.println(F("Recibido OK"));
          break;
        case 0xff42bd:  //Play/Pause
          Serial.println(F("Recibido *"));
          break;
      }
    }

    myReceiver.enableIRIn();      //Restart receiver
  }
}
