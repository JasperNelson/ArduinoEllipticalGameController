#include<Keyboard.h>

int potnum;
int val;
int encoder0PinA = 4;
int encoder0PinB = 3;
int encoder0Pos = 0;
int encoder0PinALast = LOW; // Low voltage value
int n = LOW;
const int potpin = 2; // digital pin connected to switch output
void setup() {
  Keyboard.begin();
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
}
void loop() {
  potnum = analogRead(potpin) - 511;  //halfway of potentiometer
  char a = 'a';
  char d = 'd';
  int i=0;
  bool abort = false;
  while (abort == false) { //insurance loop for the controller

    // Rotary encoder handling ("w" and "s").
    n = digitalRead(encoder0PinA);
    if (n == HIGH) {
      if (digitalRead(encoder0PinB) == LOW) {
        encoder0Pos--;
        Keyboard.press('s');        
      } else {
        encoder0Pos++;
        Keyboard.press('w');          
      }
    }

    // Potentiometer handling ("a" and "d").
    potnum = analogRead(potpin) - 511;
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
    encoder0PinALast = n;
    i++;
    if (i >= 110) {
      Keyboard.release('s');
      Keyboard.release('w');
    }
  }
}
