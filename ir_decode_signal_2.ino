
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


#include "IRLibAll.h"

//Create a receiver object to listen on pin 2
IRrecvPCI myReceiver(2);

//Create a decoder object
IRdecode myDecoder;

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}

void loop() {
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
