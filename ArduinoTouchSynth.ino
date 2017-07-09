#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "pitches.h"

Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

// notes in the melody:
int melody[] = {
  NOTE_C4//, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  Serial.begin(9600);
  Serial.println("MPR121 Capacitive Touch sensor test"); 

  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
  tone(8,NOTE_C4,250);
  delay(250);
  tone(8,NOTE_C5,250);
  }


void playNote(int note){
  switch(note){
    case 0:
     tone(8,NOTE_C4);
    break;
    case 1:
     tone(8,NOTE_CS4);
    break;
    case 2:
     tone(8,NOTE_D4);
    break;
    case 3:
     tone(8,NOTE_DS4);
    break;
    case 4:
     tone(8,NOTE_E4);
    break;
    case 5:
     tone(8,NOTE_F4);
    break;
    case 6:
     tone(8,NOTE_FS4);
    break;
    case 7:
     tone(8,NOTE_G4);
    break;
    case 8:
     tone(8,NOTE_GS4);
    break;
    case 9:
     tone(8,NOTE_A4);
    break;
    case 10:
     tone(8,NOTE_AS4);
    break;
    case 11:
     tone(8,NOTE_B4);
    break;

    

    default:
     // if nothing else matches, do the default
      // default is not set to anything.
    break;
  }
  
}

void stopNote(){
  noTone(8);
}

void loop() {
    // Get the currently touched pads
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
      playNote(i);
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
      stopNote();
    }
  }

  // reset our state
  lasttouched = currtouched;
  
}
