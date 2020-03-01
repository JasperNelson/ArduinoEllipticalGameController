#include<Keyboard.h>

// Quadrature enccoder setup
int potnum;
int val;
const int encoderPinA = 4;
const int encoderPinB = 3;

int encoderPosition = 0;
int previousEncoderPinA = LOW; // Low voltage value
int currentEncoderPinA = LOW;

// whenever current repeats charachter is not zero than you need to repeat not echoing to they keyboard until it reaches zero. 
int currentRepeats = 0;

// charachter that is going to be repeated or not repeated by the state of the encoder. 
char currentRepeatsChar = '\0';


const int quadratureEncoderRepeats = 5;

// Potentiometer setup
const int potpin = 2; // digital pin connected to switch output

void setup() {
  Keyboard.begin();
  pinMode (encoderPinA, INPUT);
  pinMode (encoderPinB, INPUT);
}

void loop() {
  
  char a = 'a';
  char d = 'd';
  int i=0;
  bool abort = false;
  while (abort == false) { //insurance loop for the controller

    // Rotary encoder handling ("w" and "s").
    
    currentEncoderPinA = digitalRead(encoderPinA);
    if (previousEncoderPinA == LOW && currentEncoderPinA == HIGH) {
      // We've detected a pulse change.  Read the next pin to find the pulse direction.      
      if (digitalRead(encoderPinB) == LOW) {
        encoderPosition--;

        // If we were repeating something, stop that first.
        if (currentRepeatsChar != '\0') {
          Keyboard.release(currentRepeatsChar);
        }
        
        currentRepeatsChar = 's';
      } else {
        encoderPosition++;

        // If we were repeating something, stop that first.
        if (currentRepeatsChar != '\0') {
          Keyboard.release(currentRepeatsChar);
        }
       
        currentRepeatsChar = 'w';
      }
    }
    previousEncoderPinA = currentEncoderPinA;

    // Handle repeat mode.
    if (currentRepeatsChar != '\0') {
      Keyboard.press(currentRepeatsChar);
      currentRepeats++;
      if (currentRepeats == quadratureEncoderRepeats) {
        // done with repeat mode
        Keyboard.release(currentRepeatsChar);
        currentRepeatsChar = '\0';
        currentRepeats=0;       
      }
    }

    // Potentiometer handling ("a" and "d").
    
    potnum = analogRead(potpin) - 511;  //halfway of potentiometer
    
    if (abs(potnum) >= 100 ) {   //if the potentiometer is slid out of the negligible zone.
      if(potnum >= 0) {   //if potentiometer is slid to left than it will trigger the a key.
        Keyboard.press('a');
      } else {    //if potentiometer is slid to right than it will trigger the d key.
        Keyboard.press('d');
      }
    } else {
      Keyboard.release('a');
      Keyboard.release('d');      
    }
    //    i++;
    //    if (i >= 110) {
    //      Keyboard.release('s');
    //      Keyboard.release('w');
    //    }
  }
}
